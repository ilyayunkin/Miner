#include "SapperGameField.h"

#include <time.h>
#include <assert.h>
#include <algorithm>

FieldCell::FieldCell() :
    mined(false), neiMined(0), flag(Flag::NO), opened(false), bombed(false)
{
}

SapperGameField::SapperGameField(int side, int mines, const QPoint &freeCell,
                                 QObject *parent) :
    QObject(parent),
    randomEngine(time(NULL)),
    side(side),
    mines(mines),
    flags(0),
    gameContinues(true)
{
    map.resize(side * side);

    placeMines(mines, freeCell);
}

SapperGameField::~SapperGameField()
{
}

void SapperGameField::placeMines(const int mines, const QPoint &freeCell)
{
    for(int i = 0; i < mines; i++){
        QPoint point;

        do{
            point = randomPoint();
        }while((point == freeCell) ||
               (getCell(point).mined) ||
               areNeighbors(point, freeCell));

        placeMine(point);
    }
}

void SapperGameField::placeMine(const QPoint &point)
{
    FieldCell &cell = getCell(point);
    cell.mined = true;
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
        (getCell(point).neiMined)++;
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

FieldCell &SapperGameField::getCell(const QPoint &point)
{
    return map[point.y() * side + point.x()];
}

const FieldCell &SapperGameField::getCell(const QPoint &point) const
{
    return map[point.y() * side + point.x()];
}

bool SapperGameField::allFreeOpened()
{
    return std::none_of(map.begin(), map.end(),
                        [](auto tile){return (!tile.opened) && (!tile.mined);});
}


void SapperGameField::openNotMinedNeighbors(const QPoint &point)
{
    QQueue<QPoint> queue;
    QList<QPoint> openedList;

    enqueueNeighbors(point, queue, openedList);
    while(!queue.empty()){
        QPoint point= queue.takeFirst();
        FieldCell &cell = getCell(point);

        cell.opened = true;
        openedList.append(point);
        if(cell.neiMined == 0){
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
            (!getCell(point).mined)){
        queue.enqueue(point);
    }
}

void SapperGameField::openAll()
{
    for(auto &tile : map){
        tile.opened = true;
    }
}

void SapperGameField::flagAllMines()
{
    for(auto &tile : map){
        if(tile.mined && (!tile.flag)){
            toggleFlag(tile);
        }
    }
}

void SapperGameField::toggleFlag(const QPoint &point)
{
    toggleFlag(getCell(point));
}

void SapperGameField::toggleFlag(FieldCell &cell)
{
    if(gameContinues){
        switch (cell.flag) {
        case Flag::NO: cell.flag = Flag::MINE;
            flags++;
            break;
        case Flag::MINE: cell.flag = Flag::DOUBT;
            flags--;
            break;
        case Flag::DOUBT: cell.flag = Flag::NO;
            break;
        default: assert(false);
            break;
        }
    }
}

void SapperGameField::click(const QPoint &point)
{
    if(gameContinues){
        FieldCell &cell = getCell(point);
        if(!cell.opened){
            cell.opened = true;

            if(cell.mined){
                cell.bombed = true;
                openAll();
                gameContinues = false;
                emit bombed();
            }else{
                // Open neighbors only if clicked to free space
                if(getNeiMines(point) == 0){
                    openNotMinedNeighbors(point);
                }
                if(allFreeOpened()){
                    flagAllMines();
                    gameContinues = false;
                    emit win();
                }
            }
        }
    }
}

Flag::FlagState SapperGameField::isFlagged(const QPoint &point)
{
    return getCell(point).flag;
}

bool SapperGameField::isOpended(const QPoint &point)
{
    return getCell(point).opened;
}

bool SapperGameField::isMined(const QPoint &point)
{
    FieldCell &cell = getCell(point);
    if(!cell.opened){
        return false;
    }else{
        return cell.mined;
    }
}

bool SapperGameField::isExploded(const QPoint &point)
{
    FieldCell &cell = getCell(point);
    if(!cell.opened){
        return false;
    }else{
        return cell.bombed;
    }
}

int SapperGameField::getNeiMines(const QPoint &point)
{
    FieldCell &cell = getCell(point);
    if(!cell.opened){
        return 0;
    }else{
        return cell.neiMined;
    }
}

int SapperGameField::getEstimatedFlags()
{
    return mines - flags;
}

bool SapperGameField::areNeighbors(const QPoint &point1, const QPoint &point2)
{
    return (abs(point1.x() - point2.x()) <= 1) &&
            (abs(point1.y() - point2.y()) <= 1);
}
