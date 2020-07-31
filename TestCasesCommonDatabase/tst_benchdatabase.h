#ifndef TST_BENCHDATABASE_H
#define TST_BENCHDATABASE_H

#include <QtTest>

class BenchDatabase : public QObject
{
    Q_OBJECT
public:
    explicit BenchDatabase(){}
    ~BenchDatabase(){}

private:
    void removeDb();

private slots:
    void initTestCase();

    void benchmarkRowIdCount();
    void benchmarkSqlCount();

};

#endif // TST_BENCHDATABASE_H
