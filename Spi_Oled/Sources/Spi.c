/*
 * Spi.c
 *
 *  Created on: Mar 13, 2017
 *      Author: JorisJunior
 */

#include "Spi.h"

void SPI_init(void){
	SPIBR=0x00; //vitesse de communication :  fr�quence de bus du �C
	SPIC2=0x00; // Chip Select (SS/) mode automatique
	SPIC1=0x5E; // CPOL=1,CPHA=1,MSB first,�C en maitre
	PTADD_PTADD0=1; // Mise en sortie du briche 0 du port A - Broche DC
	PTAPE_PTAPE0=1;	// Active r�sistance pull up sur DC
	PTDDD_PTDDD0=1; // Mise en sortie de la broche 0 du port D - Broche RES
	PTDPE_PTDPE0=1; // Active r�sistance pull up sur RES
	return;
}


char SPI_Write(char data){
	if(SPIS_SPTEF==1){	// Si la donn�e pr�c�dente a �t� envoy�e
		SPID=data;	// Envoi de la nouvelle donn�e
		asm{
			NOP
		};
		return 1;  	// Renvoi 1
	}
	return 0;		// Si la pr�c�dente donn�e n'a pas �t� envoy� , je renvoie 0
}




