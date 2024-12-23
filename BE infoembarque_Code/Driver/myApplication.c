#include "myApplication.h"


int8_t batterylevel = 0;

void Battery_init(){ //initialisation des paramètres de lecture du niveau de batterie 
	
	MyGPIO_Struct_TypeDef battery;
	battery.GPIO = GPIOA;
  battery.GPIO_Pin = 7;
  battery.GPIO_Conf = In_Analog;
  MyGPIO_Init(&battery);
  configadc(7); // PA7 est sur le canal 7 de ADC1
	convert_cont();//convertion continu
}

void RTC_init(DS1307_TimeDate *timeDate){ //initialisation du RTC avec la fonction de mise à jour du temps au cas ou 
//	  DS1307_TimeDate MARC =(*timeDate); // pour mettre à jour le temps
//	   // Définition des valeurs
//    MARC.seconds = 25;       // 30 secondes
//    MARC.minutes = 29;       // 45 minutes
//    MARC.hours = 15;         // 14 heures (2:00 PM en format 24h)
//    MARC.day_of_week = 4;    // Jeudi (1 = Dimanche, 7 = Samedi)
//    MARC.date = 12;          // 12 du mois
//    MARC.month = 12;         // Décembre 
//    MARC.year = 24; 
    DS1307_Init(I2C2);
//	  DS1307_SetTime(I2C2,&MARC);
}

void Roulis_init(){ // initialisation des paramètres pour communiquer via SPI et déterminer les coordonnées qui permettent de calculer l'angle de roulis 
		
		MySPI_Init(SPI2);
		MySPI_Clear_NSS();
		MySPI_Send(0x2D);
		MySPI_Send(0x08);
		MySPI_Set_NSS();
		MySPI_Clear_NSS();
		MySPI_Send(0x2C);
		MySPI_Send(0x0A);
		MySPI_Set_NSS();
		MySPI_Clear_NSS();
		MySPI_Send(0x31);
		MySPI_Send(0x0B);
		MySPI_Set_NSS();
}

void Index_init(MyGPIO_Struct_TypeDef * index){ //initialisation des paramètres de lecture du niveau de l'index z de l'encodeur 
	   
	  // Initialisation de la LED sur PA5 (output push-pull)
    index->GPIO = GPIOA;
    index->GPIO_Pin = 4;
    index->GPIO_Conf = In_Floating;
    MyGPIO_Init(index);

}

void Index_test(MyGPIO_Struct_TypeDef * index){
		//Lire le signal de référence de l'encodeur
		int zi = MyGPIO_Read(index->GPIO, index->GPIO_Pin);
		if(zi == 1){
			MyTimer_Encoder_Reset(); //EXTI et/ou AFIO a faire apres
		}
}

void Servo_init(MyTimer_Struct_TypeDef * tim_SV){ //initialisation de l'objet servomoteur 
		MyGPIO_Struct_TypeDef Consigne_S;//On met notre consigne du servo moteur sur B0 vu quon utilise TIM3
    Consigne_S.GPIO = GPIOB;
    Consigne_S.GPIO_Pin = 0;
    Consigne_S.GPIO_Conf = AltOut_Ppull;
    MyGPIO_Init(&Consigne_S);
		
	  tim_SV->Timer = TIM3;
		tim_SV->ARR = 1999;
	  tim_SV->PSC = 719;
	  MyTimer_Base_Init(tim_SV);
		
		MyTimer_PWM(tim_SV->Timer, 3);//On met en marche la PWM
		MyTimer_Base_Start(TIM3);
}

float Demande_message(){ //récupération des coordonées et calcul l'angle de roulis
	  
	  unsigned char Demande = 0xF2;
	  unsigned char Message[6];
	  int16_t x;
		int16_t y;
		int16_t z;
		MySPI_Clear_NSS();
		MySPI_Send(Demande);
		
		for(int i=0; i<6;i++){
			Message[i] = MySPI_Read();
		}
		MySPI_Set_NSS();
		x = ((uint16_t)Message[1]<<8) + (uint16_t)Message[0];
		y = ((uint16_t)Message[3]<<8) + (uint16_t)Message[2];//messge 2et 4 info utile
		z = ((uint16_t)Message[5]<<8) + (uint16_t)Message[4];
		//angle_roulis=360*atanf((float)z/(float)y)/(2*3.1415)+90; //angle de roulis
		return 360*atanf((float)z/(float)y)/(2*3.1415)+90;
}

void Servo_update(MyTimer_Struct_TypeDef * tim_SV, float angle_roulis) { // définition de l'angle de rotation du servomoteur à partir de l'angle de la girouette (lié à l'encodeur)
	  // Lire la position de l'encodeur
    int encoder_position = MyTimer_Encoder_Read(TIM2);
		int alpha = (encoder_position/4); // angle du servomoteur
		int Teta; //angle des voiles
		if (alpha >180){
			alpha = 360-alpha;
		}
				
		if (alpha >=0 & alpha<=45){
			Teta = 180;
		}
		if (alpha >=45 & alpha<=180){
			Teta = 240-180*alpha/135;
		}
				
		if(angle_roulis>=40){
			Teta = 0;
		}
		
		MyTimer_SetDutyCycle(tim_SV->Timer, 3, (Teta/36)+5);
}

void Send_Data(DS1307_TimeDate *MARC, float angle_roulis){ //  permet d'envoyer les données heure,direction,niveau de batterie,angle de roulis
		DS1307_GetTime(I2C2,MARC);
		int8_t timeh = MARC->hours;
		int8_t timem = MARC->minutes;
		int8_t times = MARC->seconds;
		batterylevel = ((ADC1->DR - 353) * 100.0) / (474 - 353);
	  if(batterylevel<0){
			batterylevel = 0;
		}
		else if(batterylevel>100){
			batterylevel = 100;
		}
		int direction = MyGPIO_Read(GPIOA, 6);
    // Envoyer les données toutes les 100 ms
    UART1_SendData(timeh, timem, times, direction, batterylevel, angle_roulis);
    for (volatile int i = 0; i < 5000000; i++){  // Temporisation d'environ 100 ms
    }
}
