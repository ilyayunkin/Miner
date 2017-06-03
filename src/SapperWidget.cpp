#include "SapperWidget.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QPixmap>

#include <QTimer>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QMessageBox>

#include "SapperFieldWidget.h"
#include "ChampionsTable.h"

SapperWidget::SapperWidget(Sapper * sapper, QWidget *parent) :
    QMainWindow(parent),
    sapper(sapper),
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
            }
            {
                smileLabel = new QLabel;
                QPixmap picture(":/icons/icons/smile-template.png");
                smileLabel->setPixmap(picture);
                smileLabel->setFixedSize(QSize(picture.width(),
                                               picture.height()));
                heapLayout->addWidget(smileLabel);
            }
            {
                timerLcd = new QLCDNumber;
                heapLayout->addWidget(timerLcd);
                timerLcd->setFixedHeight(50);
            }
        }
        mainLayout->addWidget(new SapperFieldWidget(sapper));
    }
    connect(sapper, SIGNAL(bombed()), SLOT(bombed()));
    connect(sapper, SIGNAL(win()), SLOT(win()));

    QTimer *timer = new QTimer(this);
    timer->start(100);
    connect(timer, SIGNAL(timeout()), SLOT(update()));
}

void SapperWidget::bombed()
{
    QMessageBox::critical(0, "You lose", "You lose");
    QPixmap picture(":/icons/icons/smile-sad.png");
    smileLabel->setPixmap(picture);
    smileLabel->setFixedSize(QSize(picture.width(),
                                   picture.height()));
}

void SapperWidget::win()
{
    QMessageBox::about(0, "You win!", "You win!");
    ChampionsTable table("Ilya Yunkin", "Sapper", 5, false);
    table.setResult(sapper->getTimeSeconds());

    QPixmap picture(":/icons/icons/smile-happy.png");
    smileLabel->setPixmap(picture);
    smileLabel->setFixedSize(QSize(picture.width(),
                                   picture.height()));
}

void SapperWidget::update()
{
    flagsEstimationLcd->display(sapper->getEstimatedFlags());
    timerLcd->display(sapper->getTimeSeconds());
}

void SapperWidget::restartSlot()
{
    QPixmap picture(":/icons/icons/smile-template.png");
    smileLabel->setPixmap(picture);
    smileLabel->setFixedSize(QSize(picture.width(),
                                   picture.height()));
}
