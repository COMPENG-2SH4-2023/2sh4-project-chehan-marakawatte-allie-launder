#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

//bool exitFlag;
objPos border[100];
GameMechs* myGM;
Player* myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    int i,j, index=0;
    //objPos border[56]; initalized globally
    myGM = new GameMechs(30, 15); //fixme , are these real dimension?
    myPlayer = new Player(myGM);

    for (i=0;i<myGM->getBoardSizeY();i++) { //fixme replace 10 with boardsizeX maybe?
        for (j=0;j<myGM->getBoardSizeX();j++) { 
            if ((i==0) || (i==(myGM->getBoardSizeY()-1)) || (j==0) || (j==(myGM->getBoardSizeX()-1))) {
                border[index].setObjPos(j, i, '#'); //border[index] = objPos{j, i, '#'};
                index++;
            }
        }
    }
}

void GetInput(void)
{
    //myGM.setInput(MacUILib_getChar());
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);
    int i, j, k=0;
    for (i=0;i<myGM->getBoardSizeY();i++) {
        for (j=0;j<myGM->getBoardSizeX();j++) { 
            for(k=0; k<(2*myGM->getBoardSizeY()+2*myGM->getBoardSizeX()-4); k++) {
                if (border[k].x==j && border[k].y==i) {
                    MacUILib_printf("%c", border[k].getSymbol()); // add conversion specifier with MacUILib!!!! or else it won't work
                    break;                   
                }
            }
            if (i!=0 && i!=(myGM->getBoardSizeY()-1)) {
                if (j!=0 && j!=(myGM->getBoardSizeX()-1)) {
                    objPos foundPlayer;
                    myPlayer->getPlayerPos(foundPlayer);
                    if (i==foundPlayer.y && j==foundPlayer.x) {
                        MacUILib_printf("%c", foundPlayer.getSymbol());
                    }
                    else {
                        MacUILib_printf(" ");
                    }
                }
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Board Size: %dx%d, Player Position: <%d,%d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempPos.x, tempPos.y, tempPos.symbol);

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
