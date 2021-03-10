#include "config.h"
#include "arrays.h"
void movePaddle(bool array[], bool direction)
{
    uchar row;
    bool temp;
    for(row = 0; row<8; row++)
    {
        gameArray[row][0] = 0;  // clear paddle so that unwanted bits are erased from LED matrix
    }
    if(direction == HI)
    {
        // move up code
        temp = array[0];
        for(row = 0; row < 7; row++)
        {
            array[row] = array[row + 1];
            gameArray[row][0] = gameArray[row][0] | array[row];
        }
        array[7] = temp;
        gameArray[7][0] = gameArray[7][0] | array[7];
    }
    if(direction == LO)
    {
        //move down code
        temp = array[7];
        for(row = 7; row >0; row--)
        {
            array[row] = array[row - 1];
            gameArray[row][0] = gameArray[row][0] | array[row];
        }
        array[0] = temp;  
        gameArray[0][0] = gameArray[0][0] | array[0];
    }  
}
 