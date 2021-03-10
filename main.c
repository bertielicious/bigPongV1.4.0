/*
 * File:   main.c
 * Author: Phil Glazzard
 *
 * Created on 02 March 2021, 21:21
 */


#include <xc.h>
#include "config.h"
#include "configOsc.h"
#include "configSPI.h"
#include "init1_max7219.h"
#include "init2Max7219.h"
#include "configTMR0.h"
#include "configPorts.h"
#include "configUsart.h"
#include "putch.h"
#include "arrays.h"
#include "drawPaddle.h"
#include "movePaddle.h"
#include "writeMatrix.h"
void main(void) 
{
    bool paddle[8] = {0,0,0,1,1,1,0,0};
    static uchar paddlePositionL = 0;
    uchar row;
    configPorts();
    configOsc();
    configSPI();
    configTMR0();
    init1_max7219();
    init2Max7219();
    configUsart();
    printf("hello Phil\n");
    PORTAbits.RA5 = LO;
    PORTAbits.RA4 = LO;
    PORTBbits.RB5 = LO;
    writeMatrix(0,7,0,15);  // clear the LED matrix of garbage data
    drawPaddle(paddle,0);   // draw the paddle possition to gameArray[row][col]
    writeMatrix(0,7,0,1);   // display the paddle on the LED matrix at col 0
   
    while(1)
    {
        if(RPB1 == LO && gameArray[0][0] == LO)
        {
            while(RPB1 == LO);
            movePaddle(paddle,UP);
            if(gameArray[0][0] && boundary[0] == HI)
            {
                continue;
            }
        }
        if(LPB1 == LO && gameArray[7][0] == LO) 
        {
            while(LPB1 == LO);
            movePaddle(paddle,DOWN);
            if(gameArray[0][7] && boundary[9] == HI)
            {
                continue;
            }
        }
        if(RPB2 == LO)
        {
            for(row = 0; row<8; row++)
            {
               
                printf("  boundary[%d] %d   gameArray[%d][0] %d\n", row, boundary[row], row, gameArray[row][0]);
            }
            printf("\n");
        }
        
        writeMatrix(0,7,0,0);
    }
    return;
}
