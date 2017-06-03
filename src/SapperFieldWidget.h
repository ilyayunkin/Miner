#ifndef SAPPERFIELDWIDGET_H
#define SAPPERFIELDWIDGET_H

#include <QWidget>

#include "Sapper.h"

class SapperFieldWidget : public QWidget
{
    Q_OBJECT

    Sapper *sapper;

    int side;
    float plotToWidgetScale;
    float widgetToPlotScale;

    int horizontalBorder;
    int verticalBorder;

    const int plotWidth;
    int cellWidth;

    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent * event);
    void mouseReleaseEvent(QMouseEvent *e);

    void drawMine(QPainter &p, int x, int y);

public:
    SapperFieldWidget(Sapper *sapper, QWidget *parent = 0);

signals:

public slots:

};

#endif // SAPPERFIELDWIDGET_H
