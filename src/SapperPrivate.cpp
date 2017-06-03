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

void SapperPrivate::toggleFlag(const QPoint &point)
{
    /// ???
}

bool SapperPrivate::isFlagged(const QPoint &point)
{
    /// ???
}

bool SapperPrivate::isOpended(const QPoint &point)
{
    if(gameField == NULL){
        return false;
    }else{
        return gameField->getCell(point)->opened;
    }
}

bool SapperPrivate::isMined(const QPoint &point)
{
    if(gameField == NULL){
        return false;
    }else{
        FieldCell *cell = gameField->getCell(point);
        if(!cell->opened){
            return false;
        }else{
            return cell->mined;
        }
    }
}

int SapperPrivate::getNeiMines(const QPoint &point)
{
    if(gameField == NULL){
        return 0;
    }else{
        FieldCell *cell = gameField->getCell(point);
        if(!cell->opened){
            return 0;
        }else{
            return cell->neiMined;
        }
    }
}
