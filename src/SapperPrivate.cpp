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
        connect(gameField, SIGNAL(bombed()), SIGNAL(bombed()));
        connect(gameField, SIGNAL(win()), SIGNAL(win()));
    }else{
        // Field already exists
    }

    gameField->click(point);
}

void SapperPrivate::toggleFlag(const QPoint &point)
{
    if(gameField == NULL){
    }else{
        gameField->toggleFlag(point);
    }
}

bool SapperPrivate::isFlagged(const QPoint &point)
{
    if(gameField == NULL){
        return false;
    }else{
        return gameField->isFlagged(point);
    }
}

bool SapperPrivate::isOpended(const QPoint &point)
{
    if(gameField == NULL){
        return false;
    }else{
        return gameField->isOpended(point);
    }
}

bool SapperPrivate::isMined(const QPoint &point)
{
    if(gameField == NULL){
        return false;
    }else{
        return gameField->isMined(point);
    }
}

int SapperPrivate::getNeiMines(const QPoint &point)
{
    if(gameField == NULL){
        return 0;
    }else{
        return gameField->getNeiMines(point);
    }
}
