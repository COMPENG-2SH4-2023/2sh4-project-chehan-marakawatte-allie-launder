#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs() //constructor
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 20; //deafult board size
    boardSizeY = 10;

    foodPos.setObjPos(-1, -1, 'o'); //initializes food position outside of gameboard
}

GameMechs::GameMechs(int boardX, int boardY) //constructor
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX; //specialized board size
    boardSizeY = boardY;

    foodPos.setObjPos(-1, -1, 'o'); //initializes food position outside of gameboard

}

GameMechs::~GameMechs() //destructor
{

}

bool GameMechs::getExitFlagStatus() 
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}


char GameMechs::getInput()
{
    if(MacUILib_hasChar()) {
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setLoseTrue()
{
    loseFlag = true;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore() 
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    //generate random x and y coord and make sure they are not border or blockOff position
    //check x and y against 0 and borderSize / Y
    //use isPosEqual() method from objPos class
    bool flag;
    srand(time(NULL));
    do {
        int xCoord = rand() % (getBoardSizeX()-2)+1; //generates random x coordinate within border size
        int yCoord = rand() % (getBoardSizeY()-2)+1; //generates random y coordinate within border size
        foodPos.setObjPos(xCoord, yCoord, 'o'); //sets food object random coordinates and symbol
        for (int i = 0; i < blockOff->getSize(); i++)
        {
            objPos temp;
            blockOff->getElement(temp, i);
            flag = foodPos.isPosEqual(&temp); //checks food position against player position
            if (flag == true)
            {
                break;
            }
        }
    } while (flag); //repeat until randomly generated food doesn't have same position as player

}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}


