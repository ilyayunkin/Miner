#include <QtTest>
#include <QCoreApplication>

#include "SapperGameField.h"

auto getMinedPoint(SapperGameField &field){
    for(int i = 0; i < field.getFieldSide(); ++i){
        for(int j = 0; j < field.getFieldSide(); ++j){
            QPoint p(i, j);
            if(field.isMined(p))
                return p;
        }
    }
    throw std::runtime_error("No mines found");
};

void openAllFreePoints(SapperGameField &field){
    for(int i = 0; i < field.getFieldSide(); ++i){
        for(int j = 0; j < field.getFieldSide(); ++j){
            QPoint p(i, j);
            if(!field.isMined(p)){
                field.click(p);
                QVERIFY(field.isOpended(p));
            }
        }
    }
}

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
    void clickingMinedFieldLeadsToExplosion();
    void openingAllFreeCellsFlagsAllMines();
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

void SapperFieldTest::clickingMinedFieldLeadsToExplosion(){
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);

    auto minedPoint = getMinedPoint(field);

    QVERIFY(field.isMined(minedPoint));
    QVERIFY(!field.isExploded(minedPoint));
    field.click(minedPoint);
    QVERIFY(field.isExploded(minedPoint));
}

void SapperFieldTest::openingAllFreeCellsFlagsAllMines(){
    constexpr auto side = 10;
    constexpr auto mines = 10;
    constexpr auto point = QPoint(0, 0);
    SapperGameField field(side, mines, point);
    openAllFreePoints(field);

    for(int i = 0; i < side; ++i){
        for(int j = 0; j < side; ++j){
            QPoint p(i, j);
            if(field.isMined(p)){
                QCOMPARE(field.getFlag(p), Flag::MINE);
            }
        }
    }
}

QTEST_MAIN(SapperFieldTest)

#include "tst_sapperfieldtest.moc"
