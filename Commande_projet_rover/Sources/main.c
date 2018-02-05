#include "Commande_projet_rover.h"
void MCU_init(void); /* Device initialization function declaration */



void main(void) {
 	MCU_init();	/* call Device Initialization */
	ADC_init();
	SCI_init();
	PTDPE_PTDPE2=1; // Resistance de Tirage W1
	PTAPE_PTAPE3=1;  // Resistance de tirage W2 
	for(;;) {
		Command();
	}
}
