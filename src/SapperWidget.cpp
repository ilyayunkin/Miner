#include "SapperWidget.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>

SapperWidget::SapperWidget(QWidget *parent) :
    QMainWindow(parent),
    timeSeconds(0)
{
    {
        QMenu *gameMenu = menuBar()->addMenu("Game");
        {
            QAction *restartAction = new QAction("Restart", this);
            gameMenu->addAction(restartAction);
            connect(restartAction, SIGNAL(triggered()), SLOT(restartClicked()));
        }
    }
    {
        QWidget *centralWidget = new QWidget;
        setCentralWidget(centralWidget);
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        {
            QHBoxLayout *heapLayout = new QHBoxLayout;
            mainLayout->addLayout(heapLayout);
            {
                flagsEstimationLcd = new QLCDNumber;
                heapLayout->addWidget(flagsEstimationLcd);
            }
            {
                timerLcd = new QLCDNumber;
                heapLayout->addWidget(timerLcd);
            }
        }
    }
}

void SapperWidget::restartClicked()
{

}
