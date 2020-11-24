#ifndef SAPPERPRIVATE_H
#define SAPPERPRIVATE_H

#include <QObject>
#include <QDateTime>
#include <QTimer>

#include "SapperGameField.h"

class SapperPrivate : public QObject
{
    Q_OBJECT

    const int side;
    const int mines;

    int time;
    SapperGameField *gameField;
    QDateTime startTime;

    QTimer *timer;

public:
    explicit SapperPrivate(int side, int mines, QObject *parent = 0);
    int getSide();
    int getEstimatedFlags();

    void click(const QPoint &point);
    void toggleFlag(const QPoint &point);
    Flag getFlag(const QPoint &point);
    bool isOpended(const QPoint &point);
    bool isMined(const QPoint &point);
    bool isExploded(const QPoint &point);
    int getNeiMines(const QPoint &point);

    int getTimeSeconds();

signals:
    void bombed();
    void win();

private slots:
    void update();
    void bombedSlot();
    void winSlot();

};

#endif // SAPPERPRIVATE_H
