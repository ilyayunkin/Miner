#ifndef SAPPERWIDGET_H
#define SAPPERWIDGET_H

#include <QMainWindow>
#include <QLCDNumber>

class SapperWidget : public QMainWindow
{
    Q_OBJECT

    long timeSeconds;
    QLCDNumber *flagsEstimationLcd;
    QLCDNumber *timerLcd;
public:
    explicit SapperWidget(QWidget *parent = 0);

signals:

public slots:

private slots:
    void restartClicked();

};

#endif // SAPPERWIDGET_H
