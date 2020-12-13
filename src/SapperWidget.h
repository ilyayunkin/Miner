#ifndef SAPPERWIDGET_H
#define SAPPERWIDGET_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QLabel>

#include "Sapper.h"

class SapperWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit SapperWidget(Sapper &sapper, QWidget *parent = 0);

private slots:
    void bombed();
    void win();

    void update();
    void restartSlot();
private:
    Sapper &sapper;
    long timeSeconds;
    QLCDNumber *flagsEstimationLcd;
    QLCDNumber *timerLcd;
    QLabel *smileLabel;
};

#endif // SAPPERWIDGET_H
