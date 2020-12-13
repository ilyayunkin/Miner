#include "SapperPrivate.h"

#include "SapperGameField.h"

#include <assert.h>

SapperPrivate::SapperPrivate(int side, int mines, QObject *parent) :
    QObject(parent),
    side(side),
    mines(mines),
    gameField(nullptr),
    startTime(QDateTime::currentDateTime())
{
}

SapperPrivate::~SapperPrivate()
{
}

int SapperPrivate::getEstimatedFlags()const
{
    if(gameField == nullptr){
        return mines;
    }else{
        return gameField->getEstimatedFlags();
    }
}

void SapperPrivate::createField(const QPoint &point)
{
    assert(gameField == nullptr);
    gameField.reset(new SapperGameField(side, mines, point, this));
    connect(gameField.get(), SIGNAL(bombed()), SLOT(bombedSlot()));
    connect(gameField.get(), SIGNAL(win()), SLOT(winSlot()));
}

void SapperPrivate::click(const QPoint &point)
{
    if(gameField == nullptr){
        createField(point);
    }
    gameField->click(point);
}

void SapperPrivate::toggleFlag(const QPoint &point)
{
    if(gameField == nullptr){
    }else{
        gameField->toggleFlag(point);
    }
}

Flag SapperPrivate::getFlag(const QPoint &point) const
{
    if(gameField == nullptr){
        return Flag::NO;
    }else{
        return gameField->getFlag(point);
    }
}

bool SapperPrivate::isOpended(const QPoint &point) const
{
    if(gameField == nullptr){
        return false;
    }else{
        return gameField->isOpended(point);
    }
}

bool SapperPrivate::isMined(const QPoint &point) const
{
    if(gameField == nullptr){
        return false;
    }else{
        return gameField->isMined(point);
    }
}

bool SapperPrivate::isExploded(const QPoint &point) const
{
    if(gameField == nullptr){
        return false;
    }else{
        return gameField->isExploded(point);
    }
}

int SapperPrivate::getNeiMines(const QPoint &point) const
{
    if(gameField == nullptr){
        return 0;
    }else{
        return gameField->getNeiMines(point);
    }
}

int SapperPrivate::getTimeSeconds() const
{
    if(timerEnd)
        return timerEnd;
    else
        return startTime.secsTo(QDateTime::currentDateTime());
}

void SapperPrivate::bombedSlot()
{
    timerEnd = startTime.secsTo(QDateTime::currentDateTime());
    emit bombed();
}

void SapperPrivate::winSlot()
{
    timerEnd = startTime.secsTo(QDateTime::currentDateTime());
    emit win();
}
