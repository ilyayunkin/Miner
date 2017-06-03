/** @file
  * @author Yunkin Ilya.
  */
#ifndef CHAMPIONSTABLE_H
#define CHAMPIONSTABLE_H

#include <QString>
#include <QMap>

class ChampionsTable
{
    QString key;
    QMap<int, QString> map;

    const int count;
    const bool greater;

    QString company;
    QString application;

    bool isChampion(const QList<int> &sortedCoins, long long coins);
public:
    ChampionsTable(QString company,
                   QString application,
                   int count = 15,
                   bool greater = true);
    void setResult(long long coins);
};

#endif // CHAMPIONSTABLE_H
