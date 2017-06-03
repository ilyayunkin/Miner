#include "SapperWidget.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QMessageBox>

#include "SapperFieldWidget.h"

SapperWidget::SapperWidget(Sapper * sapper, QWidget *parent) :
    QMainWindow(parent),
    timeSeconds(0)
{
    {
        QMenu *gameMenu = menuBar()->addMenu("Game");
        {
            QAction *restartAction = new QAction("Restart", this);
            gameMenu->addAction(restartAction);
            connect(restartAction, SIGNAL(triggered()),
                    sapper, SLOT(restartSlot()));
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
                flagsEstimationLcd->setFixedHeight(50);
                flagsEstimationLcd->hide();
            }
            {
                timerLcd = new QLCDNumber;
                heapLayout->addWidget(timerLcd);
                timerLcd->setFixedHeight(50);
                timerLcd->hide();
            }
        }
        mainLayout->addWidget(new SapperFieldWidget(sapper));
    }
    connect(sapper, SIGNAL(bombed()), SLOT(bombed()));
    connect(sapper, SIGNAL(win()), SLOT(win()));
}

void SapperWidget::bombed()
{
    QMessageBox::critical(0, "You lose", "You lose");
}

void SapperWidget::win()
{
    QMessageBox::about(0, "You win!", "You win!");
}
