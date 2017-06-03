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
