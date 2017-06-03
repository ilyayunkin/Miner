#include "Sapper.h"

#include "SapperPrivate.h"

Sapper::Sapper(int side, int mines, QObject *parent) :
    QObject(parent),
    privateMembers(new SapperPrivate(side, mines, this))
{
}

int Sapper::getSide()
{
    return privateMembers->getSide();
}

int Sapper::getFlagsEstimation()
{
    return privateMembers->getFlagsEstimation();
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
