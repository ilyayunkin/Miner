#ifndef SAPPERWIDGET_H
#define SAPPERWIDGET_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QLabel>

#include "Sapper.h"

class SapperWidget : public QMainWindow
{
    Q_OBJECT

    Sapper * sapper;
    long timeSeconds;
    QLCDNumber *flagsEstimationLcd;
    QLCDNumber *timerLcd;
    QLabel *smileLabel;

public:
    explicit SapperWidget(Sapper *sapper, QWidget *parent = 0);

signals:

public slots:

private slots:
    void bombed();
    void win();

    void update();
    void restartSlot();
};

#endif // SAPPERWIDGET_H
