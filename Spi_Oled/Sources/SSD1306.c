/*
 * SSD1306.c
 *
 *  Created on: Mar 20, 2017
 *      Author: Joris
 */
#include "SSD1306.h"
#include "estei.h"
#include "font.h"



static char SSD1306_Command(char );
const unsigned char *Rover="Rover";
const unsigned char *Val_batterie_Rover="100% ";
const unsigned char *Val_batterie_Telecommande="100%";
const unsigned char *Telecommande="Telecommande";
unsigned int OLED_Timer=10;
union{
	unsigned char OLED_State_Machine_Byte;
	struct {		
		unsigned char init		:1;
		unsigned char clear		:1;
		unsigned char init2		:1;
		unsigned char clear2	:1;
		unsigned char text_rov	:1;
		unsigned char text_tel	:1;
		unsigned char bat_rov	:1;
		unsigned char bat_tel	:1;
		unsigned char suite		:1;
	}OLED_State_machine_bit;
}OLED_State_machine;

/*Commande d'affichage pour l'écran*/
const unsigned char print[]={0xB0,0x00,0x10};

/*Tableau d'initialisation de SSD1306*/
const unsigned char init_SSD1306[]={
		0xA8,0x27,	//Set MUX Ratio A8h, 3Fh
		0xD3,0x00,	//Set Display Offset D3h, 00h
		0x40,		//Set Display Start Line 40h
		0xA0,		//Set Segment re-map A0h/A1h
		0xC0,		//Set COM Output Scan Direction C0h/C8h
		0x81,0xff,	//Set Contrast Control 81h, 7Fh
		0x8D,0x14,	//Enable charge pump regulator 8Dh, 14h
		0xA4,		//Disable Entire Display On A4h
		0xA6,		//Set Normal Display A6h
		0xAF		//Display On AFh
};

/*Gestionnaire de tache de l'afficheur*/
void OLED_Manager(void){
	char state_ssd1306=0;
	switch(OLED_State_machine.OLED_State_Machine_Byte){
	case 0:
		OLED_init();
		break;
	case 1:
		Clear_Screen();
		break;
	case 3:
		if (OLED_Timer==0) {
			OLED_State_machine.OLED_State_machine_bit.init2=1;
			OLED_Timer=10;
		}
		else{
			Display_Picture(estei);
		}
		break;
	case 7:
		if (OLED_Timer==0) {
			OLED_State_machine.OLED_State_machine_bit.clear2=1;
		}
		else{
			Clear_Screen();
		}
		break;
	case 15:
		while (state_ssd1306!=1) {
			state_ssd1306=Display(&Rover,0xB0,0x00,0x10);
		}
		OLED_State_machine.OLED_State_machine_bit.text_rov=1;
		break;
	case 31:
		while (state_ssd1306!=1) {
			state_ssd1306=Display(&Telecommande,0xB2,0x00,0x10);
		}
		OLED_State_machine.OLED_State_machine_bit.text_tel=1;
		break;
	case 63:
		while (state_ssd1306!=1) {
			state_ssd1306=Display(&Val_batterie_Rover,0xB0,0x07,0x1D);
		}
		OLED_State_machine.OLED_State_machine_bit.bat_rov=1;
		break;
	case 127: 
		while (state_ssd1306!=1) {
			state_ssd1306=Display(&Val_batterie_Telecommande,0xB2,0x07,0x1D);
		}
		OLED_State_machine.OLED_State_machine_bit.suite=1;
		break;
	default:
		break;
	}
	return;
}


/* Fonction permettant l'envoie de commande unique vers l'écran */ 
static char SSD1306_Command(char data){
	if(SPI_Write(data)){
		return 1;
	}
	return 0;
}

/* Fonction permettant l'envoie de data vers l'écran */ 
char OLED_Data(char data){
	DC_1;
	if(SPI_Write(data)){
		DC_0;
		return 1;
	}
	DC_0;
	return 0;
}

/* Fonction d'initilasition de l'écran*/ 
void OLED_init(void){
	static const unsigned char *init_data=&init_SSD1306[0];
	if(SSD1306_Command(*init_data)){
		if(++init_data==(&init_SSD1306[0]+sizeof(init_SSD1306))){
			OLED_State_machine.OLED_State_machine_bit.init=1;
		}
	}
	return;
}


/*Fonctionn permettant l'affichage d'une image sur l'écran */
void Display_Picture(const unsigned char tab[]){
	static unsigned char i=0,j=0;
	static unsigned char *p_cmd=&print[0];
	static unsigned char sequence=0;
	switch(sequence){
	case 0:	// ligne i
		if(SSD1306_Command(*p_cmd|i)) {
			if(++i>5){
				i=0;
				j=0;
				sequence=0;
				p_cmd=&print[0];		
			}
			p_cmd++;
			sequence=1;
		}
		break;
	case 1:
		if(SSD1306_Command(*p_cmd)) {
			if(++p_cmd==(&print_[0]+sizeof(print))){
				p_cmd=&print[0];
				j=0;
				sequence=2;
			}
		}
		break;
	case 2: // colonne j
		if(OLED_Data(tab[(i-1)*0x60+j])){
			if(++j>95){
				sequence=0;
			}
		}
		break;
	default :
		break;
	} 

}



/* Fonction permettant le nettoyage de l'écran */ 
void Clear_Screen(void){
	static unsigned char i=0,j=0;
	static unsigned char *p_cmd=&print_[0];
	static unsigned char sequence=0;
	switch(sequence){
	case 0:	// ligne i
		if(SSD1306_Command(*p_cmd|i)) {
			if(++i==6){
				i=0;
				OLED_State_machine.OLED_State_machine_bit.clear=1;
			}
			p_cmd++;
			sequence=1;
		}
		break;
	case 1:
		if(SSD1306_Command(*p_cmd)) {
			if(++p_cmd==(&print_[0]+sizeof(print_))){
				p_cmd=&print_[0];
				j=0;
				sequence=2;
			}
		}
		break;
	case 2: // colonne j
		if(OLED_Data(0x00)){
			if(++j==128){
				sequence=0;
			}
		}
		break;
	default :
		break;
	}
}

/* Fonction delai */ 
void delai(unsigned int delai_value){
	if (OLED_Timer==0) {
		OLED_Timer=delai_value;
	}
	return;
}

/*Fonctionn permettant l'affichage d'une chaine de caractère sur l'écran */
char Display(const unsigned char **charactere, unsigned char X, unsigned char Y1,unsigned char Y2){
	static unsigned char i=0,j=0;
	static unsigned char index_caractere=0;
	static unsigned char sequence=0;
	static unsigned char print[3]={0x00,0x00,0x00}; //ligne,colonne,0x40}
	static unsigned char *cmd=&print[0];
	print[0]=X;
	print[1]=Y1;
	print[2]=Y2;
	switch (sequence) {
	case 0:
		if(SSD1306_Command(*cmd|i)){
			if(++i==6){
				i=0;
				j=0;
				sequence=0;
				cmd=&print[0];		
			}
			cmd++;
			sequence=1;
		}
		break;
	case 1:
		if(SSD1306_Command(*cmd)) {
			if(++cmd==(&print[0]+sizeof(print))){
				cmd=&print[0];
				j=0;
				sequence=3;
			}
		}
		break;
	case 3: // colonne j
		if(OLED_Data((unsigned char)Courrier[((**charactere)-0x20)].tab[index_caractere])){
			if(++index_caractere==Courrier[((**charactere)-0x20)].wide){
				if(OLED_Data(0x00)){
					if(*(++(*charactere))=='\0'){
						return 1;
					}
					index_caractere=0;
				}
			}
		}
		if(++j>100){
			sequence=0;
		}
		break;
	default :
		break;
	} 
}





/*
       Commande SSD1306 

	     0xAE // Oled off
	     0xA8 // valeur registre mémoire en RAM accessible
	     0x3F // valeur taille mémoire en RAM accessible
	     0xD3 // valeur registre Point de départ image
	     0x00 // valeur du Point de départ image
	     0x40 // valeur registre + valeur lecture ligne (b7=0,b6=1 b5-b0=valeur )valeur =0
	     0xA0 // sens lecture image (b0=0) sens image 0->127 , b0=1 127->0
	     0xC0 // Set COM Output Scan Direction
	     0xDA,OxO2 // Set COM Pins hardware configuration
	     0x81 // Set contrast control
	     0x7F //7F=128 contrast moyen
	     0xDB // Set Vcomh deselect level
	     0x30 // 0.83*VDD 
	     0xA4 rafraichissement image (b0=0 on / b0=1 off )
             0xA6 // Affichage sens non inversé (b0=0 normal / b0=1 inversé)  // Mode adressage horizontal
	     0xD9,Ox11 // temps de précharge 
	     0x20,0x00// Reglage mode adressage 
	     0xD5 //  Define clock 
	     0x80 // 80 valeur par défaut, fr = 100 khz 
	     0x8D // charge pump regulator
	     0x14 // disable charge pump regulator
	     0xAF // display on 
}
 */
