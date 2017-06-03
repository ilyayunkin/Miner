/** @file
  * @author Yunkin Ilya.
  */
#include "ChampionsTable.h"

#include <QCoreApplication>
#include <QSettings>
#include <QInputDialog>
#include <QMessageBox>
#include <QDateTime>

ChampionsTable::ChampionsTable(QString company,
                               QString application,
                               int count,
                               bool greater)
    : key("champions"),
      count(count),
      greater(greater),
      company(company),
      application(application)
{
    QCoreApplication::setOrganizationName(company);
    QCoreApplication::setOrganizationDomain("");
    QCoreApplication::setApplicationName(application);

    QSettings s;
    QString defaultValue("NULLVALUE");
    QString key = "champions";
    QVariant champions = s.value(key, defaultValue);
    QString championsString(champions.toString());
    if(champions != defaultValue){
        QStringList list = championsString.split(";");
        foreach (QString item, list) {
            QStringList itemList = item.split("#");
            if(itemList.size() == 2){
                long long way = itemList[0].toLongLong();
                QString name = itemList[1];
                map.insert(way, name);
            }
        }
    }
}

void ChampionsTable::setResult(long long coins)
{
    QList<int> sortedCoins = map.keys();
    if(greater){
        qSort(sortedCoins.begin(), sortedCoins.end(), qGreater<int>());
    }else{
        qSort(sortedCoins.begin(), sortedCoins.end(), qLess<int>());
    }

    if((sortedCoins.size() < count) || isChampion(sortedCoins, coins)){
        QString name = QInputDialog::getText(0, "Enter your name", "Name");

        map.insert(coins, name);
        sortedCoins = map.keys();

        if(greater){
            qSort(sortedCoins.begin(), sortedCoins.end(), qGreater<int>());
        }else{
            qSort(sortedCoins.begin(), sortedCoins.end(), qLess<int>());
        }

        QString outputTable;
        QString text;
        int i = 1;
        foreach(int result, sortedCoins){
            if(i != 1){
                outputTable += ";";
            }
            QString name(map[result]);
            outputTable += QString("%1#%2").arg(result).arg(name);
            text += QString("%1 %2\n").arg(result).arg(name);
            if(i == count){
                break;
            }
            i++;
        }
        text += QString("%1 (c) %2 %3").
                arg(application).
                arg(company).
                arg(QDateTime::currentDateTime().date().year());
        QMessageBox::information(0, "Champions", text);

        QSettings s;
        s.setValue(key, outputTable);
    }
}

bool ChampionsTable::isChampion(const QList<int> &sortedCoins, long long coins)
{
    if(greater){
        return coins > sortedCoins.last();
    }else{
        return coins < sortedCoins.last();
    }
}
