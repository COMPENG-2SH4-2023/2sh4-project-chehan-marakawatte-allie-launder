#include "Player.h"
#include "objPosArrayList.h"
#include "objPos.h"


Player::Player(GameMechs* thisGMRef) //constructor
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP; //ensures the player is not moving when the game starts

    objPos tempPos;
    tempPos.setObjPos((mainGameMechsRef->getBoardSizeX())/2,(mainGameMechsRef->getBoardSizeY())/2,'*'); //initializes player to center of board

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}


Player::~Player() //destructor
{
    // deletes any heap members
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos array list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic   
    switch(mainGameMechsRef->getInput()) { //checks the input against some cases
        case ' ':  // exit character
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
    objPos currHead;
    playerPosList->getHeadElement(currHead); 
    // PPA3 Finite State Machine logic, changes moving direction based on updatedPlayerDir
    if (myDir == RIGHT) {
        currHead.x = currHead.x+1;
        if (currHead.x == mainGameMechsRef->getBoardSizeX()-1) {
            currHead.x = 1;
        }
    }
    else if (myDir == LEFT) {
        currHead.x = currHead.x-1;
        if (currHead.x == 0) {
            currHead.x = mainGameMechsRef->getBoardSizeX()-2;
        }
    }
    else if (myDir == UP) {
        currHead.y = currHead.y-1;
        if (currHead.y == 0) {
            currHead.y = mainGameMechsRef->getBoardSizeY()-2;
        }
    }
    else if (myDir == DOWN) {
        currHead.y = currHead.y+1;
        if (currHead.y == mainGameMechsRef->getBoardSizeY()-1) {
            currHead.y = 1;
        }
    }

    if (checkFoodConsumption())
    {
        increasePlayerLength(); //will increase player length if player overlaps with food
    }
    else
    {
        //shifts all the indeces of the player array list for movement
        playerPosList->insertHead(currHead);
        playerPosList->removeTail();
    }

    if (checkSelfCollision()) //if any elements of the snake body overlap, the game is lost
    {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseTrue();
    }
}

bool Player::checkFoodConsumption()
{
    objPos tempFood; //initializes temporary food variable
    mainGameMechsRef->getFoodPos(tempFood); //copies information from original food variable into temporary food variable
    objPos currHead; //initializes temporary player-head variable
    playerPosList->getHeadElement(currHead); //copies information from original player-head into temporary player-head

    if (currHead.x==tempFood.x && currHead.y==tempFood.y) //checks if the food variable and player-head variable have same position
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void Player::increasePlayerLength()
{   
    objPos currHead; //initializes temporary player-head variable
    playerPosList->getHeadElement(currHead); //copies information from original player-head into temporary player-head variable

    if (checkFoodConsumption()) //if food food is consumed, increase snake body length, randomly generate food position again, and increment score
    {
        playerPosList->insertHead(currHead);
        mainGameMechsRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore();
    }
}

bool Player::checkSelfCollision()
{
    objPos currHead; //initializes temporary player-head variable
    playerPosList->getHeadElement(currHead); //copies information from original player-head into temporary player-head variable

    int i;
    for (i = 2; i < playerPosList->getSize(); i++)
    {
        objPos temp; //initializes temporary variable
        playerPosList->getElement(temp, i); //copies data of an element of snake body into temp variable in each iteration of for loop
        if (currHead.isPosEqual(&temp)) //checks head position against the position every other element in the snake body
        {
            return true;
        }
    }
    return false;
}
