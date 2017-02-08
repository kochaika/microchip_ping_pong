#include "Definitions.h"                // Подключение файла с определениями

unsigned char EEPROM_Read (unsigned char Address)
{
    EEADR = Address;
    
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;
    
    return EEDATA;
}

void EEPROM_Write (unsigned char Address, unsigned char Datum)
{
    EEADR = Address;
    EEDATA = Datum;
    
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    
    INTCONbits.GIE = 0;
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    
    while (!PIR2bits.EEIF) { ; }
    
    INTCONbits.GIE = 1;
    
    EECON1bits.WREN = 0;
}
