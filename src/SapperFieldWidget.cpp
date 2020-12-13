#include "SapperFieldWidget.h"

#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

#include <algorithm>
#include <assert.h>

SapperFieldWidget::SapperFieldWidget(Sapper &sapper, QWidget *parent) :
    QWidget(parent),
    sapper(sapper),
    plotToWidgetScale(0),
    widgetToPlotScale(0),
    horizontalBorder(0),
    verticalBorder(0),
    cellWidth(64),
    margin(2),
    plotWidth(cellWidth * sapper.getSide() + margin * 2)
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
    QPen pen(Qt::black);
    pen.setWidth(plotWidth / 1000);
    p.setPen(pen);
    QFont f;
    f.setPixelSize(plotWidth / 100 * 4);
    p.setFont(f);

    for(int row = 0; row < sapper.getSide(); row++){
        for(int col = 0; col < sapper.getSide(); col++){
            QPoint point(col, row);

            p.setBrush(getCellColor(point));

            int x = cellWidth * col;
            int y = cellWidth * row;
            p.drawRect(x, y, cellWidth, cellWidth);

            if(sapper.isOpended(point)){
                if(sapper.isMined(point)){
                    if(sapper.isExploded(point)){
                        drawExplosion(p, x, y);
                    }else{
                        drawMine(p, x, y);
                    }
                }else{
                    if(sapper.getNeighborMines(point) > 0){
                        p.drawText(QRect(x, y, cellWidth, cellWidth),
                                   QString::number(sapper.getNeighborMines(point)),
                                   QTextOption(Qt::AlignCenter));
                    }
                }
            }
            switch (sapper.getFlag(point)) {
            case Flag::NO: // Nothing to do
                break;
            case Flag::MINE:drawMineFlag(p, x, y);
                break;
            case Flag::DOUBT:drawDoubtFlag(p, x, y);
                break;
            default: assert(false);
                break;
            }
        }
    }
}

QColor SapperFieldWidget::getCellColor(const QPoint &point)
{
    if(sapper.getFlag(point) != Flag::NO){
        return Qt::yellow;
    }else if(sapper.isOpended(point)){
            return Qt::transparent;
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
                        cellWidth * sapper.getSide())/ 2;
    verticalBorder = (h / plotToWidgetScale -
                      cellWidth * sapper.getSide())/ 2;
}

void SapperFieldWidget::mouseReleaseEvent(QMouseEvent *e)
{
    int xOnPlot = e->pos().x() * widgetToPlotScale - horizontalBorder;
    int yOnPlot = e->pos().y() * widgetToPlotScale - verticalBorder;

    int col = xOnPlot / cellWidth;
    int row = yOnPlot / cellWidth;

    bool onField = (col >= 0) && (col < sapper.getSide()) &&
            (row >= 0) && (row < sapper.getSide());

    if(onField){
        QPoint cell(col, row);

        if(e->button() == Qt::LeftButton){
            sapper.click(cell);
        }else if(e->button() == Qt::RightButton){
            sapper.toggleFlag(cell);
        }
    }
}

void SapperFieldWidget::drawExplosion(QPainter &p, int x, int y)
{
    p.drawPixmap(QRect(x, y, cellWidth, cellWidth),
                 QPixmap(":/icons/icons/boom.png"));
}

void SapperFieldWidget::drawMine(QPainter &p, int x, int y)
{
    p.drawPixmap(QRect(x, y, cellWidth, cellWidth),
                 QPixmap(":/icons/icons/mine.png"));
}

void SapperFieldWidget::drawMineFlag(QPainter &p, int x, int y)
{
    p.drawPixmap(QRect(x, y, cellWidth, cellWidth),
                 QPixmap(":/icons/icons/red-flag.png"));
}

void SapperFieldWidget::drawDoubtFlag(QPainter &p, int x, int y)
{
    p.drawPixmap(QRect(x, y, cellWidth, cellWidth),
                 QPixmap(":/icons/icons/doubt-flag.png"));
}
