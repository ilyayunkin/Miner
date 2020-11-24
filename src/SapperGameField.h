#ifndef SAPPERGAMEFIELD_H
#define SAPPERGAMEFIELD_H

#include <QObject>
#include <QPoint>
#include <QList>
#include <QQueue>

#include <random>
#include <vector>

#include "FlagState.h"

struct FieldCell
{
    bool mined;
    short neiMined;
    Flag flag;
    bool opened;
    bool bombed;

    FieldCell();
};

class SapperGameField : public QObject
{
    Q_OBJECT

    mutable std::default_random_engine randomEngine;
    /// Count of cells per row / col.
    const int side;
    /// Count of mines on the field.
    int mines;
    /// Count of flagged cells.
    int flags;
    /// Should be true until win or lose.
    bool gameContinues;
    std::vector<FieldCell> map;

    /**
     * @return random point index on field;
     */
    QPoint randomPoint()const;
    /// Settles the field by mines, the specified poind must stay free
    void placeMines(const int mines, const QPoint &freeCell);
    void placeMine(const QPoint &point);
    void markNeighbors(const QPoint &point);
    void markNeighbor(const QPoint &point);
    void openNotMinedNeighbors(const QPoint &point);
    bool exists(const QPoint &point)const;

    void enqueueNeighbors(const QPoint &point,
                      QQueue<QPoint> &queue,
                      QList<QPoint> &openedList);
    void enqueueNeighbor(const QPoint &point,
                      QQueue<QPoint> &queue,
                      QList<QPoint> &openedList);

    void openAll();
    void flagAllMines();

    bool allFreeOpened() const;
    FieldCell &getCell(const QPoint &point);
    const FieldCell &getCell(const QPoint &point) const;

    void toggleFlag(FieldCell &cell);
    bool areNeighbors(const QPoint &point1, const QPoint &point2) const;

public:
    SapperGameField(int side, int mines, const QPoint &freeCell,
                    QObject *parent = 0);
    ~SapperGameField();

    void click(const QPoint &point);
    void toggleFlag(const QPoint &point);
    Flag getFlag(const QPoint &point)const;
    bool isOpended(const QPoint &point)const;
    bool isMined(const QPoint &point)const;
    bool isExploded(const QPoint &point)const;
    int getNeiMines(const QPoint &point)const;

    int getEstimatedFlags() const;
signals:
    void bombed();
    void win();

public slots:

};

#endif // SAPPERGAMEFIELD_H
