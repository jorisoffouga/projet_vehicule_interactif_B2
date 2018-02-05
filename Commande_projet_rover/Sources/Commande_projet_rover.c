/*
 * Commande_projet_rover.c
 *
 *  Created on: Apr 10, 2017
 *      Author: JorisJunior
 */
#include "Commande_projet_rover.h"

#define W2 PTAD_PTAD3 
#define W1 PTDD_PTDD2
#define Haut 150
#define Bas  100
#define joyX 0x03
#define joyY 0x02
#define Fbus 4194304.0
#define Baudrate 9600

/*Tableau de déplacement du rover*/
const unsigned char motion_control[]={
		0x00, // Pas de déplacement 
		0x80, // Translation horizontale vers la droite 
		0x90, // Translation diagonale vers la droite (+45°)
		0xA0, // Translation verticale vers le haut 
		0xB0, // Translation diagonale vers la gauche (+45°)
		0xC0, // Translation horizontale vers la gauche 
		0xD0, // Translation diagonale vers la gauche (-45°)
		0xE0, // Translation verticale vers le bas
		0xF0, // Translation diagonale vers la droite (-45°)
		0x04, // Rotation Gauche 
		0x08, // Rotation Droite
};

void ADC_init(void){
	ADCCFG_ADICLK=0x00; // Fréquence d’échantillonnage=Fbus
	ADCCFG_ADIV=0x06;// Fréquence d’échantillonnage= Fbus/8
	ADCSC1_ADCO=0x01; // Activation ADC
	return;
}

void SCI_init(void){
	SCIBD=(unsigned int)((Fbus/(16.0*(float)Baudrate))+0.5); // Calcul du Baudrate 
	SCIC1=0x00;	// Format de trame 8N1 
	SCIC2=0x0C; // Activation SCI 
	return;
}

void SCI_Send(char octet){
	if(SCIS1_TC){
		SCID=octet;
		return;
	}
}

/*Partie ADC*/
char ADC(char Channel){
	ADCSC1_ADCH=Channel; // Sélectionne la voie à convertir 
	while(!ADCSC1_COCO);
	return ADCRL;  // Retourne le résultat de la conversion
}

/*Command Joystick au Rover */
void Command(void){
	unsigned char X,Y=0;
	X=ADC(joyX);
	Y=ADC(joyY);
	if (W1==0){
		SCI_Send(motion_control[9]);  //Rotation Gauche 
		return;
	}
	if (W2==0) {
		SCI_Send(motion_control[10]); // Rotation Droite
		return;
	}
	if(X>=Bas && X<=Haut && Y>=Bas && Y<=Haut){
		SCI_Send(motion_control[0]);// Pas de déplacement 
	}
	else if(X>Haut && Y>Bas && Y<Haut){
		SCI_Send(motion_control[1]);// Translation horizontale vers la droite 
	}
	else if(X>Haut && Y>Haut){
		SCI_Send(motion_control[2]);//Translation diagonale vers la droite (+45°)
	}
	else if(Y>Haut && X>Bas && X<Haut){
		SCI_Send(motion_control[3]);// Translation verticale vers le haut 
	}
	else if(Y>Haut && X<Bas){
		SCI_Send(motion_control[4]);//Translation diagonale vers la gauche (+45°)
	}
	else if(X<Bas && Y>Bas && Y<Haut){
		SCI_Send(motion_control[5]);// // Translation horizontale vers la gauche 
	}
	else if(X<Bas&& Y<Bas){
		SCI_Send(motion_control[6]);// Translation diagonale vers la gauche (-45°)
	}
	else if(X>Bas && X<Haut && Y<Bas){
		SCI_Send(motion_control[7]);//Translation verticale vers le bas
	}
	else if(X>Haut && Y<Bas){
		SCI_Send(motion_control[8]);//Translation diagonale vers la droite (-45°)
	}
}

