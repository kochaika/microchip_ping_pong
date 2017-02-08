#ifndef __LCD_H
#define __LCD_H


/*struct _COL_VAL
{
    unsigned Blu : 5;
    unsigned Grn : 6;
    unsigned Red : 5;
};*/

/* -=- Объявление прототипов функций -=- */
void LCD_Init (void);
void ClrScr (void);
void Lcd_Write_Com (int DH);
void lcd_write_color (char hh,char ll);
void Lcd_Write_Data (int DH);
void Lcd_Write_Com_Data (int com1, int dat1);
void Address_set (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void Pant (unsigned int color);
void Disp_Line (unsigned int X_Start, unsigned int Y_Start, unsigned int X_End, unsigned int Y_End, unsigned int Color);
//void Rainbow (void);
void Disp_Pic (const far rom unsigned char *Img, unsigned int X, unsigned int Y);
void Disp_Pic_RAM (char *Img, unsigned int X, unsigned int Y);
void Disp_Text (unsigned char X, unsigned int Y, char * Line, int Pic_Col, int Bckgr_Col);
void delayms (int count);					 

/* -=- Директивы препроцессора -=- */
#define LCD_DataPortH       PORTD
#define LCD_DataPortL       PORTC
#define LCD_CS              PORTAbits.RA0
#define LCD_RS              PORTAbits.RA1
#define LCD_WR              PORTAbits.RA2
#define LCD_RD              PORTAbits.RA3
#define LCD_REST            PORTEbits.RE0

#define CONV_RGB()          ((int) Color.Red << 11) | ((int) Color.Grn << 5) | (int) Color.Blu
#define __HIGH(x)           *(((unsigned char*) &x)+2)
#define __MID(x)            *(((unsigned char*) &x)+1)
#define __LOW(x)            *(((unsigned char*) &x)+0)


#endif
