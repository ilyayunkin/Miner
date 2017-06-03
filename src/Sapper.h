#ifndef SAPPER_H
#define SAPPER_H

#include <QObject>
#include <QPoint>

class SapperPrivate;

class Sapper : public QObject
{
    Q_OBJECT

    SapperPrivate *privateMembers;
public:
    Sapper(int side, int mines, QObject *parent = 0);
    int getSide();
    int getFlagsEstimation();
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
    /**
     * @param point - Cell index.
     * @return 0 if cell is not opened or count of mines in 8 neighboring cells.
     */
    int getNeighborMines(const QPoint &point);
signals:

public slots:

};

#endif // SAPPER_H
