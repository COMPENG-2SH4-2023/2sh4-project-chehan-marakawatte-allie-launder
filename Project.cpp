#include <iostream>
#include <ctime>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

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

    while(myGM->getExitFlagStatus() == false) //checks exit flag method
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

    myGM = new GameMechs(30, 15); //game board initialization
    myPlayer = new Player(myGM); //player object initialization
    objPosArrayList* playerBody = myPlayer->getPlayerPos(); //player position stored in type objPosArrayList
    myGM->generateFood(playerBody); //generates food randomly on gameboard

}

void GetInput(void)
{
    if (MacUILib_hasChar() != 0) {
        myGM->setInput(MacUILib_getChar()); //records input into myGM
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir(); //updates player movement direction
    myPlayer->movePlayer(); //moves the player in updated direction
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn; //ensures an extra space is not printed when player is in a row

    objPosArrayList* playerBody = myPlayer->getPlayerPos(); //player position stored in type objPosArrayList
    objPos tempBody; //temporary variable holding snake body with type 'objPos'



    objPos tempFood;
    myGM->getFoodPos(tempFood);

    int i, j, k=0;
    for (i=0;i<myGM->getBoardSizeY();i++) {

        for (j=0;j<myGM->getBoardSizeX();j++) {

            drawn = false; 

            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if (tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol); //prints player symbol if the index being iterated through equals player index
                    drawn = true;
                    break;
                }
            }

            if (drawn) continue;
            
            if (i!=0 && i!=(myGM->getBoardSizeY()-1)) { //if statement prints entire border and food symbol
                if (j!=0 && j!=(myGM->getBoardSizeX()-1)) {
                    if (i==tempFood.y && j==tempFood.x) {
                        MacUILib_printf("%c", tempFood.getSymbol()); //prints the food symbol if its position doesn't overlap with border
                    }
                    else {
                        MacUILib_printf(" ");
                    }
                }
                else {
                    MacUILib_printf("#");
                }
            }
            else {
                MacUILib_printf("#");
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d", myGM->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    if (myGM->getLoseFlagStatus()) //this flag is different from exit flag and only is processed when suicide occurs
    {
        cout << "YOU LOSE!!!!" << endl; 
    }

    MacUILib_uninit();
}