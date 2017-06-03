#include "SapperFieldWidget.h"

#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

SapperFieldWidget::SapperFieldWidget(Sapper *sapper, QWidget *parent) :
    QWidget(parent),
    sapper(sapper),
    side(0),
    plotToWidgetScale(0),
    widgetToPlotScale(0),
    horizontalBorder(0),
    verticalBorder(0),
    plotWidth(10000),
    cellWidth(1)
{
    QTimer *timer = new QTimer(this);
    timer->start(100);
    connect(timer, SIGNAL(timeout()), SLOT(update()));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void SapperFieldWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.scale(plotToWidgetScale, plotToWidgetScale);
    p.translate(horizontalBorder, verticalBorder);

    for(int row = 0; row < sapper->getSide(); row++){
        for(int col = 0; col < sapper->getSide(); col++){
            QPoint point(col, row);

            if(sapper->isOpended(point)){
                p.setBrush(Qt::cyan);
                if(sapper->isMined(point)){
                    p.setBrush(Qt::red);
                }else{
                    p.setBrush(Qt::cyan);
                }
            }else{
                p.setBrush(QBrush());
            }
            int x = cellWidth * col;
            int y = cellWidth * row;
            QPen pen(Qt::black);
            pen.setWidth(plotWidth / 1000);
            p.setPen(pen);
            p.drawRect(x, y, cellWidth, cellWidth);

            if(sapper->isOpended(point)){
                if(sapper->isMined(point)){
                    drawMine(p, x, y);
                }else{
                    QFont f;
                    f.setPixelSize(plotWidth / 100 * 4);
                    p.setPen(Qt::black);
                    p.setFont(f);
                    if(sapper->getNeighborMines(point) > 0){
                        p.drawText(QRect(x, y, cellWidth, cellWidth),
                                   QString::number(sapper->getNeighborMines(point)),
                                   QTextOption(Qt::AlignCenter));
                    }
                }
            }

        }
    }
    QFont f;
    f.setPixelSize(plotWidth / 100 * 4);
    p.setPen(Qt::black);
    p.setFont(f);
}

void SapperFieldWidget::resizeEvent(QResizeEvent * event)
{
    int h = event->size().height();
    int w = event->size().width();

    if((float(h) / w) < 1){
        side = h;
        cellWidth = float(plotWidth) / sapper->getSide();
    }else{
        side = w;
        cellWidth = float(plotWidth) / sapper->getSide();
    }
    widgetToPlotScale = float(plotWidth) / side;
    plotToWidgetScale = float(side) / plotWidth;
    horizontalBorder = (w / plotToWidgetScale -
                        cellWidth * sapper->getSide())/ 2;
    verticalBorder = (h / plotToWidgetScale -
                      cellWidth * sapper->getSide())/ 2;
}

void SapperFieldWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int xOnPlot = e->pos().x() * widgetToPlotScale - horizontalBorder;
    int yOnPlot = e->pos().y() * widgetToPlotScale - verticalBorder;

    int col = xOnPlot / cellWidth;
    int row = yOnPlot / cellWidth;

    bool onField = (col >= 0) && (col < sapper->getSide()) &&
            (row >= 0) && (row < sapper->getSide());

    if(onField){
        sapper->click(QPoint(col, row));
    }
}

void SapperFieldWidget::drawMine(QPainter &p, int x, int y)
{
    p.setBrush(Qt::black);

    float rectSide = cellWidth * 0.8;
    float spanSize = cellWidth / 2 - rectSide / 2;
    QPointF upLeft(x + spanSize, y + spanSize);
    QPointF downRight(x + spanSize + rectSide, y + spanSize + rectSide);

    QRectF elementRect(upLeft,downRight);

    p.drawEllipse(elementRect);
}