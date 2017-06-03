#include "Sapper.h"

#include "SapperPrivate.h"

Sapper::Sapper(int side, int mines, QObject *parent) :
    QObject(parent),
    side(side),
    mines(mines),
    privateMembers(new SapperPrivate(side, mines, this))
{
    connect(privateMembers, SIGNAL(bombed()), SIGNAL(bombed()));
    connect(privateMembers, SIGNAL(win()), SIGNAL(win()));
}

int Sapper::getSide()
{
    return privateMembers->getSide();
}

int Sapper::getEstimatedFlags()
{
    return privateMembers->getEstimatedFlags();
}

int Sapper::getTimeSeconds()
{
    return privateMembers->getTimeSeconds();
}


void Sapper::click(const QPoint &point)
{
    privateMembers->click(point);
}

void Sapper::toggleFlag(const QPoint &point)
{
    privateMembers->toggleFlag(point);
}

bool Sapper::isFlagged(const QPoint &point)
{
    return privateMembers->isFlagged(point);
}

bool Sapper::isOpended(const QPoint &point)
{
    return privateMembers->isOpended(point);
}

bool Sapper::isMined(const QPoint &point)
{
    return privateMembers->isMined(point);
}

int Sapper::getNeighborMines(const QPoint &point)
{
    return privateMembers->getNeiMines(point);
}

void Sapper::restartSlot()
{
    delete privateMembers;
    privateMembers = new SapperPrivate(side, mines, this);
    connect(privateMembers, SIGNAL(bombed()), SIGNAL(bombed()));
    connect(privateMembers, SIGNAL(win()), SIGNAL(win()));
}
