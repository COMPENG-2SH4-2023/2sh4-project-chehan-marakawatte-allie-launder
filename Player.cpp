#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos((mainGameMechsRef->getBoardSizeX())/2,(mainGameMechsRef->getBoardSizeY())/2,'*'); 

    // more actions to be included
    //no heap member yet, will have heap members in iteration 3...use destructor THEN probably
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos array list
}

void Player::updatePlayerDir()
{

    char input = mainGameMechsRef->getInput();
    // PPA3 input processing logic   
    switch(input) { //switch out input with game mechanics (iteration 1b), 25:00 in vid, fixme
        case ' ':  // exit
            mainGameMechsRef->setExitTrue();
            break;
        case 'a':
            if (myDir != RIGHT) {
                myDir = LEFT;
            }
            break;
        case 'd':
            if (myDir != LEFT) {
                myDir = RIGHT;
            }
            break;
        case 's':
            if (myDir != UP) {
                myDir = DOWN;
            }
            break;
        case 'w':
            if (myDir != DOWN) {
                myDir = UP;
            }
        default:
            break;

    }     
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    if (myDir == RIGHT) {
        playerPos.x = playerPos.x+1;
        if (playerPos.x == mainGameMechsRef->getBoardSizeX()-1) {
            playerPos.x = 1;
        }
    }
    else if (myDir == LEFT) {
        playerPos.x = playerPos.x-1;
        if (playerPos.x == 0) {
            playerPos.x = mainGameMechsRef->getBoardSizeX()-2;
        }
    }
    else if (myDir == UP) {
        playerPos.y = playerPos.y-1;
        if (playerPos.y == 0) {
            playerPos.y = mainGameMechsRef->getBoardSizeY()-2;
        }
    }
    else if (myDir == DOWN) {
        playerPos.y = playerPos.y+1;
        if (playerPos.y == mainGameMechsRef->getBoardSizeY()-1) {
            playerPos.y = 1;
        }
    }
}

