#ifndef SAPPERFIELDWIDGET_H
#define SAPPERFIELDWIDGET_H

#include <QWidget>

#include "Sapper.h"

class SapperFieldWidget : public QWidget
{
    Q_OBJECT
public:
    SapperFieldWidget(Sapper &sapper, QWidget *parent = 0);
private:
    Sapper &sapper;

    float plotToWidgetScale;
    float widgetToPlotScale;

    int horizontalBorder;
    int verticalBorder;

    /// @brief Pixels count in side of one cell rect/
    const int cellWidth;

    int margin;
    /// @brief Pixels count in smaller side of widget
    const int plotWidth;

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent * event);
    void mouseReleaseEvent(QMouseEvent *e);

    void drawMine(QPainter &p, int x, int y);
    void drawExplosion(QPainter &p, int x, int y);
    void drawMineFlag(QPainter &p, int x, int y);
    void drawDoubtFlag(QPainter &p, int x, int y);

    QColor getCellColor(const QPoint &point);
};

#endif // SAPPERFIELDWIDGET_H
