#ifndef SAPPER_H
#define SAPPER_H

#include <QObject>
#include <QPoint>

#include "FlagState.h"

class SapperPrivate;

class Sapper : public QObject
{
    Q_OBJECT

    const int side;
    const int mines;
    SapperPrivate *privateMembers;
public:
    Sapper(int side, int mines, QObject *parent = 0);
    int getSide() const;
    void click(const QPoint &point);
    /**
     * @brief Sets flag to specified cell.
     * @param point - Cell index.
     */
    void toggleFlag(const QPoint &point);
    /**
     * @param point - Cell index.
     * @return true if flag seted to this cell.
     */
    Flag getFlag(const QPoint &point)const;
    /**
     * @param point - Cell index.
     * @return Returns true if cell were opened.
     */
    bool isOpended(const QPoint &point)const;
    bool isMined(const QPoint &point) const;
    bool isExploded(const QPoint &point) const;
    /**
     * @param point - Cell index.
     * @return 0 if cell is not opened or count of mines in 8 neighboring cells.
     */
    int getNeighborMines(const QPoint &point) const;

    int getEstimatedFlags() const;
    int getTimeSeconds() const;
signals:
    bool bombed();
    void win();

public slots:
    void restartSlot();

};

#endif // SAPPER_H
