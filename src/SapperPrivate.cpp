#include "SapperPrivate.h"

#include <assert.h>

SapperPrivate::SapperPrivate(int side, int mines, QObject *parent) :
    QObject(parent),
    side(side),
    mines(mines),
    time(0),
    gameField(nullptr),
    startTime(QDateTime::currentDateTime()),
    timer(nullptr)
{
}

int SapperPrivate::getSide() const
{
    return side;
}

int SapperPrivate::getEstimatedFlags()const
{
    if(gameField == nullptr){
        return mines;
    }else{
        return gameField->getEstimatedFlags();
    }
}

void SapperPrivate::createFieldAndTimer(const QPoint &point)
{
    assert(timer == nullptr);
    assert(gameField == nullptr);
    gameField = new SapperGameField(side, mines, point, this);
    connect(gameField, SIGNAL(bombed()), SLOT(bombedSlot()));
    connect(gameField, SIGNAL(win()), SLOT(winSlot()));

    timer = new QTimer(this);
    timer->start(100);
    connect(timer, SIGNAL(timeout()), SLOT(update()));
}

void SapperPrivate::click(const QPoint &point)
{
    if(gameField == nullptr){
        createFieldAndTimer(point);
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
    return time;
}

void SapperPrivate::update()
{
    time = startTime.secsTo(QDateTime::currentDateTime());
}

void SapperPrivate::bombedSlot()
{
    assert(timer != nullptr);
    timer->stop();
    emit bombed();
}

void SapperPrivate::winSlot()
{
    assert(timer != nullptr);
    timer->stop();
    emit win();
}
