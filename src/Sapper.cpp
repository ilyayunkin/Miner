#include "Sapper.h"

#include "SapperPrivate.h"

Sapper::Sapper(int side, int mines, QObject *parent) :
    QObject(parent),
    side(side),
    mines(mines),
    privateMembers(new SapperPrivate(side, mines, this))
{
    connect(privateMembers.get(), SIGNAL(bombed()), SIGNAL(bombed()));
    connect(privateMembers.get(), SIGNAL(win()), SIGNAL(win()));
}

Sapper::~Sapper()
{
}

int Sapper::getSide() const
{
    return privateMembers->getSide();
}

int Sapper::getEstimatedFlags() const
{
    return privateMembers->getEstimatedFlags();
}

int Sapper::getTimeSeconds()const
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

Flag Sapper::getFlag(const QPoint &point) const
{
    return privateMembers->getFlag(point);
}

bool Sapper::isOpended(const QPoint &point) const
{
    return privateMembers->isOpended(point);
}

bool Sapper::isMined(const QPoint &point) const
{
    return privateMembers->isMined(point);
}

bool Sapper::isExploded(const QPoint &point) const
{
    return privateMembers->isExploded(point);
}

int Sapper::getNeighborMines(const QPoint &point)const
{
    return privateMembers->getNeiMines(point);
}

void Sapper::restartSlot()
{
    privateMembers.reset(new SapperPrivate(side, mines, this));
    connect(privateMembers.get(), SIGNAL(bombed()), SIGNAL(bombed()));
    connect(privateMembers.get(), SIGNAL(win()), SIGNAL(win()));
}
