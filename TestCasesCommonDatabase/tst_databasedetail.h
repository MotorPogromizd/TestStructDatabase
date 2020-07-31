#ifndef TST_DATABASEDETAIL_H
#define TST_DATABASEDETAIL_H

#include <QtTest>

class TestDatabaseDetail : public QObject
{
    Q_OBJECT
public:
    explicit TestDatabaseDetail(){}

private slots:
    void initTestCase(){}
    void cleanupTestCase(){}

    void testTableName();
    void testTableName_data();

    void testColumnName();
    void testColumnName_data();

    void testColumnType();
    void testColumnType_data();

    void testCreateTablePartQuery();
    void testCreateTablePartQuery_data();

    void testCreateTableQuery();
    void testCreateTableQuery_data();

    void testAddQuery();
    void testAddQuery_data();

    void testOneLength();
    void testOneLength_data();

    void testRemoveHalfRecordsQuery();
    void testCleanDatabase();

    // TODO test new write functions

};

#endif // TST_DATABASEDETAIL_H
