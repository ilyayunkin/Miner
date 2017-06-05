#include "SapperFieldWidget.h"

#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

#include <algorithm>

SapperFieldWidget::SapperFieldWidget(Sapper *sapper, QWidget *parent) :
    QWidget(parent),
    sapper(sapper),
    plotToWidgetScale(0),
    widgetToPlotScale(0),
    horizontalBorder(0),
    verticalBorder(0),
    cellWidth(32),
    plotWidth(cellWidth * sapper->getSide())
{
    QTimer *timer = new QTimer(this);
    timer->start(100);
    connect(timer, SIGNAL(timeout()), SLOT(update()));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(500, 500);
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

            p.setBrush(getCellColor(point));

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
}

QColor SapperFieldWidget::getCellColor(const QPoint &point)
{
    if(sapper->isFlagged(point)){
        return Qt::yellow;
    }else if(sapper->isOpended(point)){
        if(sapper->isMined(point)){
            return Qt::red;
        }else{
            return Qt::transparent;
        }
    }else{
        return Qt::lightGray;
    }
}


void SapperFieldWidget::resizeEvent(QResizeEvent * event)
{
    int h = event->size().height();
    int w = event->size().width();

    int side = std::min(h, w);

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

    QPoint cell(col, row);

    if(onField){
        if(e->button() == Qt::LeftButton){
            sapper->click(cell);
        }else if(e->button() == Qt::RightButton){
            sapper->toggleFlag(cell);
        }
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
