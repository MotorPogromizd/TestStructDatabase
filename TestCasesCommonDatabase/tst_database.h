#ifndef TST_DATABASE_H
#define TST_DATABASE_H

#include <QtTest>

/**
 * @brief The TestDatabase class
 * @ingroup TestCommonDatabase
 */
class TestDatabase : public QObject
{
    Q_OBJECT
public:
    explicit TestDatabase(){}
    ~TestDatabase(){}

private:
    void removeDb();

private slots:
    // TODO test how is works with empty struct
    void initTestCase();
    //void cleanupTestCase();


    void testCreateOneTableDatabase();    

    /**
     * @brief testRecordsCount
     * Manually add records and test function numberOfRecords()
     */
    void testRecordsCount();
    void testRecordsCount_data();

    // TODO benchmark between different types if counting

    /**
     * @brief testAddRecord
     * Function using already tested count function
     */
    void testAddRecord();
    void testAddRecord_data();




    void testClearDatabase();
    void testClearDatabase_data();

    void testRemoveHalfRecords();
    void testRemoveHalfRecords_data();

    void testCheckTypes();
    void testCheckTypes_data();

    void testReadData();
    void testReadData_data();

    void testReadDataCount();
    void testReadDataCount_data();




};

#endif // TST_DATABASE_H
