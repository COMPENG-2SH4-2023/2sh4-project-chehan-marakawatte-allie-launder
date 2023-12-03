#include "objPosArrayList.h"
#include <iostream>
#include <ctime>

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

objPosArrayList::objPosArrayList() //constructor
{
    aList = new objPos[ARRAY_MAX_CAP]; //this is the snake body's with a maximum of 200 segments
    sizeList = 0; //size of the snake body, excluding any segments that are empty (have not been assigned)
    sizeArray = ARRAY_MAX_CAP; 
}

objPosArrayList::~objPosArrayList() //destructor
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList == sizeArray) { //doesn't add any segments if the snake array list is already full
        return;
    }
    for (int i = sizeList; i > 0; i--) { //moves each element in the snake array list down one index
        aList[i].setObjPos(aList[i - 1]);
    }

    aList[0].setObjPos(thisPos);
    sizeList++; //inserts new snake segment at the first index (head) of snake
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList == sizeArray) { //doesn't add any segments if the snake array list is already full
        return;
    }

    aList[sizeList].setObjPos(thisPos);
    sizeList++; //inserts new snake segment at the end of it's body (not at the end of the list)
}

void objPosArrayList::removeHead()
{
    if (sizeList==0) { //doesn't remove anything if there is no segments in the snake array list (no head)
        return;
    }
    for (int i = 0; i < sizeList - 1; i++) { //sets every value at each index of snake array list equal to the value of the following index
        aList[i].setObjPos(aList[i + 1]);
    }
    sizeList--; //lazy deletion of the last element of the snake body
}

void objPosArrayList::removeTail()
{
    if (sizeList==0) { //doesn't remove anything if there are no segments in the snake array list
        return;
    }
    sizeList--; //lazy deletion of last element of the snake body
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}