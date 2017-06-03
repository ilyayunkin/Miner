#include "SapperPrivate.h"

SapperPrivate::SapperPrivate(int side, int mines, QObject *parent) :
    QObject(parent),
    side(side),
    mines(mines),
    minesEstimation(mines),
    gameField(NULL)
{
}

int SapperPrivate::getSide()
{
    return side;
}

int SapperPrivate::getFlagsEstimation()
{
    return minesEstimation;
}

void SapperPrivate::click(const QPoint &point)
{
    if(gameField == NULL){
        gameField = new SapperGameField(side, mines, point, this);
    }else{
        // Field already exists
    }

    gameField->click(point);
}
