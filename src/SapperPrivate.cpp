#include "SapperPrivate.h"

#include <assert.h>

SapperPrivate::SapperPrivate(int side, int mines, QObject *parent) :
    QObject(parent),
    side(side),
    mines(mines),
    time(0),
    gameField(NULL),
    startTime(QDateTime::currentDateTime()),
    timer(NULL)
{
}

int SapperPrivate::getSide()
{
    return side;
}

int SapperPrivate::getEstimatedFlags()
{
    if(gameField == NULL){
        return mines;
    }else{
        return gameField->getEstimatedFlags();
    }
}

void SapperPrivate::click(const QPoint &point)
{
    if(gameField == NULL){
        gameField = new SapperGameField(side, mines, point, this);
        connect(gameField, SIGNAL(bombed()), SLOT(bombedSlot()));
        connect(gameField, SIGNAL(win()), SLOT(winSlot()));

        timer = new QTimer(this);
        timer->start(100);
        connect(timer, SIGNAL(timeout()), SLOT(update()));
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

bool SapperPrivate::isExploded(const QPoint &point)
{
    if(gameField == NULL){
        return false;
    }else{
        return gameField->isExploded(point);
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

int SapperPrivate::getTimeSeconds()
{
    return time;
}

void SapperPrivate::update()
{
    time = startTime.secsTo(QDateTime::currentDateTime());
}

void SapperPrivate::bombedSlot()
{
    assert(timer != NULL);
    timer->stop();
    emit bombed();
}

void SapperPrivate::winSlot()
{
    assert(timer != NULL);
    timer->stop();
    emit win();
}
