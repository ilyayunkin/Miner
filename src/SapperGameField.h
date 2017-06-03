#ifndef SAPPERGAMEFIELD_H
#define SAPPERGAMEFIELD_H

#include <QObject>
#include <QPoint>

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

public:
    SapperGameField(int side, int mines, const QPoint &freeCell,
                    QObject *parent = 0);
    ~SapperGameField();

    FieldCell *getCell(const QPoint &point) const;
    void click(const QPoint &point);

signals:

public slots:

};

#endif // SAPPERGAMEFIELD_H
