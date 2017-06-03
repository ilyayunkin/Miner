#ifndef SAPPERGAMEFIELD_H
#define SAPPERGAMEFIELD_H

#include <QObject>
#include <QPoint>
#include <QList>
#include <QQueue>

#include <random>

struct FieldCell
{
    bool mined;
    short neiMined;
    bool flagged;
    bool opened;

    FieldCell();
};

class SapperGameField : public QObject
{
    Q_OBJECT

    std::default_random_engine randomEngine;
    int side;
    FieldCell *map;

    QPoint randomPoint();
    void placeMines(const int mines, const QPoint &freeCell);
    void placeMine(const QPoint &point);
    void markNeighbors(const QPoint &point);
    void markNeighbor(const QPoint &point);
    void openNotMinedNeighbors(const QPoint &point);
    bool exists(const QPoint &point);

    void enqueueNeighbors(const QPoint &point,
                      QQueue<QPoint> &queue,
                      QList<QPoint> &openedList);
    void enqueueNeighbor(const QPoint &point,
                      QQueue<QPoint> &queue,
                      QList<QPoint> &openedList);

    void openAll();
    bool allFreeOpened();

public:
    SapperGameField(int side, int mines, const QPoint &freeCell,
                    QObject *parent = 0);
    ~SapperGameField();

    FieldCell *getCell(const QPoint &point) const;
    void click(const QPoint &point);
    void toggleFlag(const QPoint &point);
    bool isFlagged(const QPoint &point);
    bool isOpended(const QPoint &point);
    bool isMined(const QPoint &point);
    int getNeiMines(const QPoint &point);

signals:
    void bombed();
    void win();

public slots:

};

#endif // SAPPERGAMEFIELD_H
