#ifndef SAPPER_H
#define SAPPER_H

#include <QObject>
#include <QPoint>

class SapperPrivate;

class Sapper : public QObject
{
    Q_OBJECT

    const int side;
    const int mines;
    SapperPrivate *privateMembers;
public:
    Sapper(int side, int mines, QObject *parent = 0);
    int getSide();
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
    bool isFlagged(const QPoint &point);
    /**
     * @param point - Cell index.
     * @return Returns true if cell were opened.
     */
    bool isOpended(const QPoint &point);
    bool isMined(const QPoint &point);
    /**
     * @param point - Cell index.
     * @return 0 if cell is not opened or count of mines in 8 neighboring cells.
     */
    int getNeighborMines(const QPoint &point);

    int getEstimatedFlags();
    int getTimeSeconds();
signals:
    bool bombed();
    void win();

public slots:
    void restartSlot();

};

#endif // SAPPER_H
