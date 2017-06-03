#ifndef SAPPERPRIVATE_H
#define SAPPERPRIVATE_H

#include <QObject>
#include "SapperGameField.h"

class SapperPrivate : public QObject
{
    Q_OBJECT

    const int side;
    const int mines;
    const int minesEstimation;
    SapperGameField *gameField;

public:
    explicit SapperPrivate(int side, int mines, QObject *parent = 0);
    int getSide();
    int getFlagsEstimation();
    void click(const QPoint &point);

    void toggleFlag(const QPoint &point);
    bool isFlagged(const QPoint &point);
    bool isOpended(const QPoint &point);
    bool isMined(const QPoint &point);
    int getNeiMines(const QPoint &point);

signals:

public slots:

};

#endif // SAPPERPRIVATE_H
