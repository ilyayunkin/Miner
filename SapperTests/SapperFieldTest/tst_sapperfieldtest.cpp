#include <QtTest>
#include <QCoreApplication>

#include "SapperGameField.h"

class SapperFieldTest : public QObject
{
    Q_OBJECT

public:
    SapperFieldTest();
    ~SapperFieldTest();

private slots:
    void returnsSide();
    void specifiedCellIsNotMined();
    void createdUnexplored();
    void clickedCellOpens();
    void togglesMineDoubtNoFlag();
    void countsMinesFlags();
    void placesSpecifiedCountOfMines();
    void noMinesInitiallyExploded();
};

SapperFieldTest::SapperFieldTest(){
}

SapperFieldTest::~SapperFieldTest(){
}

void SapperFieldTest::returnsSide(){
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);

    QCOMPARE(side, field.getFieldSide());
}

void SapperFieldTest::specifiedCellIsNotMined(){
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);

    QVERIFY(!field.isMined(point));
}

void SapperFieldTest::createdUnexplored(){
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);
    for(int i = 0; i < side; ++i){
        for(int j = 0; j < side; ++j){
            QVERIFY(!field.isOpended(QPoint(i, j)));
        }
    }
}

void SapperFieldTest::clickedCellOpens(){
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);

    QVERIFY(!field.isOpended(point));
    field.click(point);
    QVERIFY(field.isOpended(point));
}

void SapperFieldTest::togglesMineDoubtNoFlag()
{
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);
    QCOMPARE(field.getFlag(point), Flag::NO);
    field.toggleFlag(point);
    QCOMPARE(field.getFlag(point), Flag::MINE);
    field.toggleFlag(point);
    QCOMPARE(field.getFlag(point), Flag::DOUBT);
    field.toggleFlag(point);
    QCOMPARE(field.getFlag(point), Flag::NO);
}

void SapperFieldTest::countsMinesFlags(){
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);

    QCOMPARE(mines, field.getEstimatedFlags());
    field.toggleFlag(point);
    QCOMPARE(mines - 1, field.getEstimatedFlags());
}

void SapperFieldTest::placesSpecifiedCountOfMines(){
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);

    int minesCount = 0;
    for(int i = 0; i < side; ++i){
        for(int j = 0; j < side; ++j){
            if(field.isMined(QPoint(i, j))){
                ++minesCount;
            }
        }
    }
    QCOMPARE(mines, minesCount);
}

void SapperFieldTest::noMinesInitiallyExploded(){
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);
    for(int i = 0; i < side; ++i){
        for(int j = 0; j < side; ++j){
            QVERIFY(!field.isExploded(QPoint(i, j)));
        }
    }
}

QTEST_MAIN(SapperFieldTest)

#include "tst_sapperfieldtest.moc"
