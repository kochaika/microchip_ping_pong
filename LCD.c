#include "Definitions.h"       // Подключение файла с определениями
#include "FONT_8x11.h"              // Подключение файла с пользовательскими шрифтами
#include "Encode.h"


void Disp_Pic (const far rom unsigned char *Img, unsigned int X, unsigned int Y)
{
    unsigned char j;
    unsigned int  i, Width, Height;
    unsigned int  Addr = 0;    
    
    __MID(Width) = Img[Addr++];
    __LOW(Width) = Img[Addr++];
    
    __MID(Height) = Img[Addr++];
    __LOW(Height) = Img[Addr++];
    
    Address_set (X, Y, X+Width-1, Y+Height-1);
    
    LCD_RS = 1;
    LCD_CS = 0;
        
    for (i=Height; i>0; i--)
    {
        for (j=Width; j>0; j--)
        {
            LCD_DataPortL = Img[Addr++];
            LCD_WR = 0;
            LCD_DataPortH = Img[Addr++];
            LCD_WR = 1;
        }
    }
    
    LCD_CS = 1;
}


void Disp_Line (unsigned int X_Start, unsigned int Y_Start, unsigned int X_End, unsigned int Y_End, unsigned int Color)
{
    int dX, dY, dir_X, dir_Y;
    unsigned int X, Y;
    unsigned int Distance, i;

    dX = (int) X_End - X_Start;                     // Расстояние по оси X от начала до конца отрезка
    dY = (int) Y_End - Y_Start;                     // Расстояние по оси Y от начала до конца отрезка

    if      (dX > 0)  { dir_X = 1; }                // Напрявление шага по оси X
    else if (dX == 0) { dir_X = 0; }
    else              { dir_X = -1; }

    if      (dY > 0)  { dir_Y = 1; }                // Напрявление шага по оси Y
    else if (dY == 0) { dir_Y = 0; }
    else              { dir_Y = -1; }

    dX = dX > 0 ? dX : dX * (-1);                   // Абсолютная составляющая длины отрезка по X
    dY = dY > 0 ? dY : dY * (-1);                   // Абсолютная составляющая длины отрезка по Y

    Distance = dX >= dY ? dX : dY;                  // За длину отрезка выбирается наибольшее из расстояний

    for (i=0, X=0, Y=0; i<=Distance+1; i++)
    {
        Lcd_Write_Com_Data (0x004e, X_Start);
        Lcd_Write_Com_Data (0x004f, Y_Start);
        Lcd_Write_Com (0x0022);
        Lcd_Write_Data (Color);
        
        X += dX; Y += dY;

        if (X > Distance)
        {
            X -= Distance;
            X_Start += dir_X;
        }

        if (Y > Distance)
        {
            Y -= Distance;
            Y_Start += dir_Y;
        }
    }

	return;
}


void Disp_Text (unsigned char X, unsigned int Y, char * Line, int Pic_Col, int Bckgr_Col)
{
    unsigned char Char_Num, i, j, k;
    unsigned int Byte = 0;
    
    Char_Num = strlen (Line);
    
    Address_set (X,Y,X+(Char_Num*8)-1,Y+10);
    
    for (i=0; i<11; i++)
    for (j=0; j<Char_Num; j++)
    {
        Byte = (unsigned char) Line[j] - 0x20;
        Byte = Encode[Byte];
        Byte = FONT_8x11[Byte][i];
        
        for (k=0; k<8; k++)
        {
                if (Byte & (1<<(7-k))) { Lcd_Write_Data (Pic_Col);   }
                else                   { Lcd_Write_Data (Bckgr_Col); }
        }
    }
}


void LCD_Init (void)
{
    LCD_REST = 1;
    delayms (5);	
	LCD_REST = 0;
	delayms (10);
	LCD_REST = 1;
	LCD_CS = 1;
	LCD_RD = 1;
	LCD_WR = 1;
	delayms (20);

    Lcd_Write_Com_Data(0x0000,0x0001);    delayms(1);  //ґтїЄѕ§Хс
    Lcd_Write_Com_Data(0x0003,0xA8A4);    delayms(1);   //0xA8A4
    Lcd_Write_Com_Data(0x000C,0x0000);    delayms(1);   
    Lcd_Write_Com_Data(0x000D,0x080C);    delayms(1);   
    Lcd_Write_Com_Data(0x000E,0x2B00);    delayms(1);   
    Lcd_Write_Com_Data(0x001E,0x00B0);    delayms(1);   
    Lcd_Write_Com_Data(0x0001,0x2B3F);    delayms(1);   //Зэ¶ЇКдіцїШЦЖ320*240  0x6B3F
    Lcd_Write_Com_Data(0x0002,0x0600);    delayms(1);
    Lcd_Write_Com_Data(0x0010,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0011,0x6070);    delayms(1);        //0x4030           //¶ЁТеКэѕЭёсКЅ  16О»Й« 
    Lcd_Write_Com_Data(0x0005,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0006,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0016,0xEF1C);    delayms(1);
    Lcd_Write_Com_Data(0x0017,0x0003);    delayms(1);
    Lcd_Write_Com_Data(0x0007,0x0233);    delayms(1);        //0x0233       
    Lcd_Write_Com_Data(0x000B,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x000F,0x0000);    delayms(1);        //ЙЁГиїЄКјµШЦ·
    Lcd_Write_Com_Data(0x0041,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0042,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0048,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0049,0x013F);    delayms(1);
    Lcd_Write_Com_Data(0x004A,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x004B,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0044,0xEF00);    delayms(1);
    Lcd_Write_Com_Data(0x0045,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0046,0x013F);    delayms(1);
    Lcd_Write_Com_Data(0x0030,0x0707);    delayms(1);
    Lcd_Write_Com_Data(0x0031,0x0204);    delayms(1);
    Lcd_Write_Com_Data(0x0032,0x0204);    delayms(1);
    Lcd_Write_Com_Data(0x0033,0x0502);    delayms(1);
    Lcd_Write_Com_Data(0x0034,0x0507);    delayms(1);
    Lcd_Write_Com_Data(0x0035,0x0204);    delayms(1);
    Lcd_Write_Com_Data(0x0036,0x0204);    delayms(1);
    Lcd_Write_Com_Data(0x0037,0x0502);    delayms(1);
    Lcd_Write_Com_Data(0x003A,0x0302);    delayms(1);
    Lcd_Write_Com_Data(0x003B,0x0302);    delayms(1);
    Lcd_Write_Com_Data(0x0023,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0024,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0025,0x8000);    delayms(1);
    Lcd_Write_Com_Data(0x004f,0);
    Lcd_Write_Com_Data(0x004e,0);
	Lcd_Write_Com(0x0022);
	
	ClrScr ();
}


void ClrScr (void)
{
    unsigned long i;
    
    LCD_RS = 1;
	LCD_CS = 0;
	
    for (i=76800; i>0; i--)
    {
        LCD_DataPortH = 0xFF;	
	    LCD_DataPortL = 0xFF;
	    LCD_WR = 0;
	    LCD_WR = 1;
    }
    LCD_CS = 1;
}

void Lcd_Write_Com (int DH)
{	
    LCD_RS = 0;
	LCD_CS = 0;	 
	LCD_DataPortH = DH>>8;	
	LCD_DataPortL = DH;
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;	
}
void lcd_write_color (char hh,char ll)
{
    LCD_RS = 1;
	LCD_CS = 0;	  				
	LCD_DataPortH = hh;	
	LCD_DataPortL = ll;
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;	
}

void Lcd_Write_Data (int DH)
{
    LCD_RS = 1;
	LCD_CS = 0;	  				
	LCD_DataPortH = DH>>8;	
	LCD_DataPortL = DH;
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;	
}


void Lcd_Write_Com_Data (int com1, int dat1)
{
   Lcd_Write_Com (com1);
   Lcd_Write_Data (dat1);
}


void Address_set (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{ 
	Lcd_Write_Com_Data (0x0044, (x2<<8)+x1);
	Lcd_Write_Com_Data (0x0045, y1);
	Lcd_Write_Com_Data (0x0046, y2);
	Lcd_Write_Com_Data (0x004e, x1);
	Lcd_Write_Com_Data (0x004f, y1);
    Lcd_Write_Com (0x0022);	   	    	
}


void Pant (unsigned int color)
{
    int i,j;
	
    Address_set (0,0,239,319);

    for (i=0;i<320;i++)
    {
        for (j=0;j<240;j++)
        {
            Lcd_Write_Data (color);
        }
    }		
}


void delayms (int count)
{
    int i,j;
    
    for (i=0; i<count; i++) { Delay10TCYx (1); }
} 


/*void Rainbow (void)
{
    unsigned int i;
    unsigned char j, RED, GRN, BLU;
    
    Address_set (0, 0, 216, 255);
    RED = 0b11111; 
    GRN = 0;
    BLU = 0;
    
    for (i=0; i<255; i++)
    {
        if (i<31)            { if (GRN<0b111111) { GRN += 2; } }
        if (i>=31  && i<62)  { if (RED)          { RED--; } }
        if (i>=62  && i<93)  { if (BLU<0b11111)  { BLU++; } }
        if (i>=93  && i<124) { if (GRN)          { GRN -= 2; } }
        if (i>=124 && i<155) { if (RED<0b11111)  { RED++; } }
        if (i>=155)          { if (GRN<0b111111) { GRN += 2; } }
        
        Color.Red = RED;
        Color.Grn = GRN;
        Color.Blu = BLU;
        	
        for (j=0; j<217; j++)
        {
            Lcd_Write_Data (CONV_RGB());
            
	  		if (j<31)            { if (Color.Grn < GRN)  { Color.Grn += 2; } }
            if (j>=31  && j<62)  { if (Color.Red)        { Color.Red--; }    }
            if (j>=62  && j<93)  { if (Color.Blu < BLU)  { Color.Blu++; }    }
            if (j>=93  && j<124) { if (Color.Grn)        { Color.Grn -= 2; } }
            if (j>=124 && j<155) { if (Color.Red < RED)  { Color.Red++; }    }
            if (j>=155)          { if (Color.Grn < GRN)  { Color.Grn++; }    }
        }
    }
}*/
