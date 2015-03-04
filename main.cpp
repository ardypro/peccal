/*
    PEC calculator for MLX90614 SMBus

    ver 1.0

    by Jack Zhong (mails2me@yeah.net)

    This tool borrowed crc8 class from John Fitter's MLX90614 library for Arduino
*/

#include <iostream>
#include "Crc8.h"
#include "cstdio"
#include "conio.h"
#include <windows.h>



#define MLX90614_CRC8POLY       7

using namespace std;

uint8_t lowByte(uint16_t data)
{
    uint16_t ret ;
    ret=data;
    ret &=0xFF;


    cout << "    low byte of  0x" << hex << uppercase << data << " is \t0x" <<  uppercase <<hex << (uint16_t)ret <<endl;

    return ret;
}

uint8_t highByte(uint16_t data)
{
    uint8_t ret = data >>8;

    cout <<"    high byte of 0x" << hex << uppercase << data << " is \t0x" <<hex << uppercase << (uint16_t) ret << endl;

    return ret;
}


int main()
{
    char option='c';

    uint16_t     sa = 0x0;
    uint16_t     data =0xBE5A;
    uint16_t     reg = 0x0E;
    uint16_t     _crc;



    while ((option =='c' )|| (option=='C')||(option=='\n') || (option=='\r'))
    {
        cout << "PEC Calculator for Melexis SMBus sensors\r\n" << endl;
        printf("    >input sa in hex: \t0x");
        scanf("%X",&sa);


        printf("    >input reg in hex: \t0x");
        scanf("%X", &reg);

        printf("    >input data in hex: 0x");
        scanf("%X",&data);
        printf("\r\n\r\n");

        sa &= 0x00FF;
        reg |= 0x20;
        CRC8 crc(MLX90614_CRC8POLY);
        crc.crc8(sa<<1);
        crc.crc8(reg);
        crc.crc8(lowByte(data));
        _crc = crc.crc8(highByte(data));

        printf("\r\n    ");
        cout << "PEC value is: \t\t0x" << hex  << uppercase << (uint16_t) _crc << endl;

        printf("\r\nPress c, C or Enter key to continue, otherwise to exit.");
        option = getch();

        system("cls");
    }


    return 0;
}


