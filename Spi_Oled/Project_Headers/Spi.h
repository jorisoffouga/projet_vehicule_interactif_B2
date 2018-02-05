/*
 * Spi.h
 *
 *  Created on: Mar 13, 2017
 *      Author: JorisJunior
 */

#include "Cpu.h"
#include "Events.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

void SPI_init(void);
char SPI_Write(char);
