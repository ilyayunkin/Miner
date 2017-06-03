#include "SapperGameField.h"

#include <time.h>

FieldCell::FieldCell() :
    mined(false), neiMined(0), flagged(false), opened(false)
{
}

SapperGameField::SapperGameField(int side, int mines, const QPoint &freeCell,
                                 QObject *parent) :
    QObject(parent),
    randomEngine(time(NULL)),
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
        }while((point == freeCell) || (getCell(point)->mined));

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
    if(exists(point)){
        (getCell(point)->neiMined)++;
    }
}

bool SapperGameField::exists(const QPoint &point)
{
    bool xOk = (point.x() >= 0) && (point.x() < side);
    bool yOk = (point.y() >= 0) && (point.y() < side);

    return xOk && yOk;
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
            openAll();
            emit bombed();
        }else{
            openNotMinedNeighbors(point);
            if(allFreeOpened()){
                emit win();
            }
        }
    }
}

bool SapperGameField::allFreeOpened()
{
    bool ret = true;

    for(int i = 0; i < side * side; i++){
        if((!map[i].opened) && (!map[i].mined)){
            ret = false;
            break;
        }
    }

    return ret;
}


void SapperGameField::openNotMinedNeighbors(const QPoint &point)
{
    QQueue<QPoint> queue;
    QList<QPoint> openedList;

    enqueueNeighbors(point, queue, openedList);
    while(!queue.empty()){
        QPoint point= queue.takeFirst();
        FieldCell *cell = getCell(point);

        cell->opened = true;
        openedList.append(point);
        if(cell->neiMined == 0){
            enqueueNeighbors(point, queue, openedList);
        }
    }
}

void SapperGameField::enqueueNeighbors(const QPoint &point,
                                       QQueue<QPoint> &queue,
                                       QList<QPoint> &openedList)
{
    for(int i = 0; i < 3; i++){
        enqueueNeighbor(QPoint(point.x() - 1 + i, point.y() + 1), queue, openedList);
        enqueueNeighbor(QPoint(point.x() - 1 + i, point.y() - 1), queue, openedList);
    }
    enqueueNeighbor(QPoint(point.x() - 1, point.y()), queue, openedList);
    enqueueNeighbor(QPoint(point.x() + 1, point.y()), queue, openedList);
}

void SapperGameField::enqueueNeighbor(const QPoint &point,
                                      QQueue<QPoint> &queue,
                                      QList<QPoint> &openedList)
{
    if(exists(point) && (!openedList.contains(point)) &&
            (!getCell(point)->mined)){
        queue.enqueue(point);
    }
}

void SapperGameField::openAll()
{
    for(int i = 0; i < side * side; i++){
        map[i].opened = true;
    }
}


void SapperGameField::toggleFlag(const QPoint &point)
{
    getCell(point)->flagged = !getCell(point)->flagged;
}

bool SapperGameField::isFlagged(const QPoint &point)
{
    return getCell(point)->flagged;
}

bool SapperGameField::isOpended(const QPoint &point)
{
    return getCell(point)->opened;
}

bool SapperGameField::isMined(const QPoint &point)
{
    FieldCell *cell = getCell(point);
    if(!cell->opened){
        return false;
    }else{
        return cell->mined;
    }
}

int SapperGameField::getNeiMines(const QPoint &point)
{
    FieldCell *cell = getCell(point);
    if(!cell->opened){
        return 0;
    }else{
        return cell->neiMined;
    }
}
