#include "SapperGameField.h"

FieldCell::FieldCell() :
    mined(false), neiMined(0), flagged(false), opened(false)
{
}

SapperGameField::SapperGameField(int side, int mines, const QPoint &freeCell,
                                 QObject *parent) :
    QObject(parent),
    side(side)
{
    map = new FieldCell[side * side];

    placeMines(mines, freeCell);
}

SapperGameField::~SapperGameField()
{
    delete[] map;
}

void SapperGameField::placeMines(const int mines, const QPoint &freeCell)
{
    for(int i = 0; i < mines; i++){
        QPoint point;

        do{
            point = randomPoint();
        }while(point == freeCell);

        placeMine(point);
    }
}

void SapperGameField::placeMine(const QPoint &point)
{
    FieldCell *cell = getCell(point);
    cell->mined = true;
    markNeighbors(point);
}

void SapperGameField::markNeighbors(const QPoint &point)
{
    for(int i = 0; i < 3; i++){
        markNeighbor(QPoint(point.x() - 1 + i, point.y() + 1));
        markNeighbor(QPoint(point.x() - 1 + i, point.y() - 1));
    }
    markNeighbor(QPoint(point.x() - 1, point.y()));
    markNeighbor(QPoint(point.x() + 1, point.y()));
}

void SapperGameField::markNeighbor(const QPoint &point)
{
    bool xOk = (point.x() > 0) && (point.x() < side);
    bool yOk = (point.y() > 0) && (point.y() < side);

    if(xOk && yOk){
        (getCell(point)->neiMined)++;
    }
}

QPoint SapperGameField::randomPoint()
{
    int randomNumber = randomEngine() % (side * side);
    int row = randomNumber / side;
    int col = randomNumber % side;

    return QPoint(col, row);
}

FieldCell *SapperGameField::getCell(const QPoint &point) const
{
    return map + point.y() * side + point.x();
}

void SapperGameField::click(const QPoint &point)
{
    FieldCell *cell = getCell(point);
    if(!cell->opened){
        cell->opened = true;

        if(cell->mined){
            /// BOOOOOM
        }else{
            openNotMinedNeighbors(point);
        }
    }
}

void SapperGameField::openNotMinedNeighbors(const QPoint &point)
{
}

