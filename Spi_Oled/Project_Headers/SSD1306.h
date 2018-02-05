/*
 * SSD1306.h
 *
 *  Created on: Mar 20, 2017
 *      Author: JorisJunior
 */

#ifndef SSD1306_H_
#define SSD1306_H_
#include "Spi.h"


#define OLED_RST_0	PTDD_PTDD0=0
#define OLED_RST_1	PTDD_PTDD0=1
#define DC_0	PTAD_PTAD0=0
#define DC_1	PTAD_PTAD0=1

void OLED_init(void);
char OLED_Data(char);
char Display(const unsigned char **, unsigned char ,unsigned char, unsigned char );
void Display_Picture(const unsigned char );
void Clear_Screen(void);
void delai(unsigned int);
void OLED_Manager(void);

#endif /* SSD1306_H_ */
