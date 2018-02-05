/*
 * Commande_projet_rover.h
 *
 *  Created on: Feb 24, 2017
 *      Author: JorisJunior
 */
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

void Command(void);
void ADC_init(void);
char ADC(char);
void SCI_init(void);
void SCI_Send(char octet);



