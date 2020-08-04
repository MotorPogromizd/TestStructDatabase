#ifndef TST_TESTMULTITABLEDATABASE_H
#define TST_TESTMULTITABLEDATABASE_H

#include <QtTest>

class TestMultitableDatabase : public QObject
{
    Q_OBJECT
public:
    explicit TestMultitableDatabase(){}
    ~TestMultitableDatabase(){}

private:
    void removeDb();

private slots:
    void initTestCase();

    void testTableCount();
    void testTableCount_data();

    void testRecordCount();
    void testRecordCount_data();

};

#endif // TST_TESTMULTITABLEDATABASE_H
