#include "tst_database.h"

#include "CommonDatabase/database.h"
#include "DebugOutput/debugoutput.h"

const QString dbFileName = "aTestDb.db";
const QString connectionName = "db";
const QString DB_TYPE = "QSQLITE";

//void TestDatabase::cleanupTestCase() {
//    //QFile db(dbFileName);
//    //QVERIFY(db.exists());
//    // NOTE now not deleted
//    //bool success = true;//db.remove();
//    //QVERIFY(success);
//}


void TestDatabase::removeDb() {
    QFile db(dbFileName);
    //QVERIFY(db.exists());
    // NOTE now not deleted
    bool success = db.remove();
    dbg << "base removed" << success;
    //QVERIFY(success);
}

void TestDatabase::initTestCase() {
    removeDb();
}

void TestDatabase::testCreateOneTableDatabase() {
    struct Struct {
        int a;
    };
    {
        Database<Struct> db(dbFileName);
    }
    QFile dbf(dbFileName);
    QVERIFY(dbf.exists());
    removeDb();
}
void TestDatabase::testRecordsCount() {
    QFETCH(int, test_size);
    QFETCH(int, result);

    QCOMPARE(test_size, result);
}

void TestDatabase::testRecordsCount_data() {
    QTest::addColumn<int>("test_size");
    QTest::addColumn<int>("result");

    int count;
    //QString dbConnectionName;
    struct Struct {
        int a;
    };
    struct NotValidStruct {
        bool b;
    };

    // TODO test when database not valid

    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        QSqlQuery createQuery(db);
        QString queryString = DatabaseDetail::createTableQuery<Struct, 0>();
        createQuery.prepare(queryString);
        createQuery.exec();
        //dbConnectionName = db.connectionName();
    }
    QSqlDatabase::removeDatabase(connectionName);
    dbg << "connection names" << QSqlDatabase::connectionNames() << connectionName;
    {
        Database<Struct> db(dbFileName);
        count = db.numberOfRecords();
    }
    QTest::addRow("Empty") << count << 0;
    removeDb();

    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        QSqlQuery createQuery(db);
        QString queryString = DatabaseDetail::createTableQuery<Struct, 0>();
        createQuery.prepare(queryString);
        createQuery.exec();
        QSqlQuery addQuery(db);
        QString addString = DatabaseDetail::addRecordQuery<Struct, 0>();
        addQuery.prepare(addString);
        addQuery.addBindValue(3000);
        addQuery.exec();
    }
    QSqlDatabase::removeDatabase(connectionName);
    {
        Database<Struct> db(dbFileName);
        count = db.numberOfRecords();
    }
    QTest::addRow("One record") << count << 1;
    removeDb();

    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        QSqlQuery createQuery(db);
        QString queryString = DatabaseDetail::createTableQuery<Struct, 0>();
        createQuery.prepare(queryString);
        createQuery.exec();
        QSqlQuery addQuery(db);
        QString addString = DatabaseDetail::addRecordQuery<Struct, 0>();
        addQuery.prepare(addString);
        addQuery.addBindValue(1000);
        for (int i = 0; i < 30; ++i) {
            addQuery.exec();
        }
    }
    QSqlDatabase::removeDatabase(connectionName);
    {
        Database<Struct> db(dbFileName);
        count = db.numberOfRecords();
    }
    QTest::addRow("Thirty records ") << count << 30;
    removeDb();

    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        QSqlQuery createQuery(db);
        QString queryString = DatabaseDetail::createTableQuery<Struct, 0>();
        createQuery.prepare(queryString);
        createQuery.exec();
        QSqlQuery addQuery(db);
        QString addString = DatabaseDetail::addRecordQuery<Struct, 0>();
        addQuery.prepare(addString);
        addQuery.addBindValue(1000);
        for (int i = 0; i < 31; ++i) {
            addQuery.exec();
        }
        QSqlQuery removeHalfQuery(db);
        QString removeHalfString = DatabaseDetail::removeHalfRecordsQuery<0>();
        removeHalfQuery.prepare(removeHalfString);
        removeHalfQuery.exec();
    }
    QSqlDatabase::removeDatabase(connectionName);
    {
        Database<Struct> db(dbFileName);
        count = db.numberOfRecords();
    }
    QTest::addRow("After remove half") << count << 16;
    removeDb();

    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        QSqlQuery createQuery(db);
        QString queryString = DatabaseDetail::createTableQuery<Struct, 0>();
        createQuery.prepare(queryString);
        createQuery.exec();
        QSqlQuery addQuery(db);
        QString addString = DatabaseDetail::addRecordQuery<Struct, 0>();
        addQuery.prepare(addString);
        addQuery.addBindValue(1000);
        for (int i = 0; i < 31; ++i) {
            addQuery.exec();
        }
        QSqlQuery removeHalfQuery(db);
        QString removeHalfString = DatabaseDetail::removeHalfRecordsQuery<0>();
        removeHalfQuery.prepare(removeHalfString);
        removeHalfQuery.exec();
        QSqlQuery vacuumQuery(db);
        vacuumQuery.prepare("VACUUM");
        vacuumQuery.exec();
    }
    QSqlDatabase::removeDatabase(connectionName);
    {
        Database<Struct> db(dbFileName);
        count = db.numberOfRecords();
    }
    QTest::addRow("After remove half & vacuum") << count << 16;
    removeDb();

    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        QSqlQuery createQuery(db);
        QString queryString = DatabaseDetail::createTableQuery<Struct, 0>();
        createQuery.prepare(queryString);
        createQuery.exec();
        QSqlQuery addQuery(db);
        QString addString = DatabaseDetail::addRecordQuery<Struct, 0>();
        addQuery.prepare(addString);
        addQuery.addBindValue(1000);
        for (int i = 0; i < 30; ++i) {
            addQuery.exec();
        }
        QSqlQuery removeHalfQuery(db);
        QString removeHalfString = DatabaseDetail::removeHalfRecordsQuery<0>();
        removeHalfQuery.prepare(removeHalfString);
        removeHalfQuery.exec();
        QSqlQuery vacuumQuery(db);
        vacuumQuery.prepare("VACUUM");
        vacuumQuery.exec();
        QSqlQuery cleanQuery(db);
        cleanQuery.prepare(DatabaseDetail::cleanQuery<0>());
        cleanQuery.exec();
    }
    QSqlDatabase::removeDatabase(connectionName);
    {
        Database<Struct> db(dbFileName);
        count = db.numberOfRecords();
    }
    QTest::addRow("After clean") << count << 0;
    removeDb();

    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        QSqlQuery createQuery(db);
        QString queryString = DatabaseDetail::createTableQuery<Struct, 0>();
        createQuery.prepare(queryString);
        createQuery.exec();
        QSqlQuery addQuery(db);
        QString addString = DatabaseDetail::addRecordQuery<Struct, 0>();
        addQuery.prepare(addString);
        addQuery.addBindValue(1000);
        for (int i = 0; i < 30; ++i) {
            addQuery.exec();
        }
        QSqlQuery removeHalfQuery(db);
        QString removeHalfString = DatabaseDetail::removeHalfRecordsQuery<0>();
        removeHalfQuery.prepare(removeHalfString);
        removeHalfQuery.exec();
        QSqlQuery vacuumQuery(db);
        vacuumQuery.prepare("VACUUM");
        vacuumQuery.exec();
        QSqlQuery cleanQuery(db);
        cleanQuery.prepare(DatabaseDetail::cleanQuery<0>());
        cleanQuery.exec();
        QSqlQuery vacuumQuery2(db);
        vacuumQuery2.prepare("VACUUM");
        vacuumQuery2.exec();
    }
    QSqlDatabase::removeDatabase(connectionName);
    {
        Database<Struct> db(dbFileName);
        count = db.numberOfRecords();
    }
    QTest::addRow("After clean & vacuum") << count << 0;
    removeDb();
}




void TestDatabase::testAddRecord() {
    QFETCH(int, test_size);
    QFETCH(int, result);

    QCOMPARE(test_size, result);

}

void TestDatabase::testAddRecord_data() {
    QTest::addColumn<int>("test_size");
    QTest::addColumn<int>("result");

    int count;
    // TODO test when database not valid

    struct Struct {
        int a;
    };
    struct NotValidStruct {
        bool b;
    };
    {
        Database<Struct> db(dbFileName);
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Empty") << count << 0;
    {
        Database<Struct> db(dbFileName);
        db.addRecord(Struct{1});
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Add one") << count << 1;

    {
        Database<Struct> db(dbFileName);
        for (auto i = 0; i < 20; ++i) {
            db.addRecord(Struct{i+1});
        }
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Add twenty") << count << 20;
}

void TestDatabase::testClearDatabase() {
    QFETCH(int, test_size);
    QFETCH(int, result);

    QCOMPARE(test_size, result);
}

void TestDatabase::testClearDatabase_data() {
    QTest::addColumn<int>("test_size");
    QTest::addColumn<int>("result");

    // TODO test when database not valid

    struct TestStruct {
        int a;
    };
    struct NotValidStruct {
        bool b;
    };
    int count = -1;

    {
        Database<TestStruct> db(dbFileName);
        db.clearDatabase();
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Clear empty database") << count << 0;

    {
        Database<TestStruct> db(dbFileName);
        db.addRecord(TestStruct{1000});
        db.clearDatabase();
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Clear one record database") << count << 0;

    {
        Database<TestStruct> db(dbFileName);
        for (int i = 0; i < 30; ++i) {
            db.addRecord(TestStruct{1000});
        }
        db.clearDatabase();
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Clear 30 records database") << count << 0;

}

void TestDatabase::testRemoveHalfRecords() {
    QFETCH(int, test_size);
    QFETCH(int, result);

    QCOMPARE(test_size, result);
}

void TestDatabase::testRemoveHalfRecords_data() {
    QTest::addColumn<int>("test_size");
    QTest::addColumn<int>("result");


    // TODO test when database not valid

    struct TestStruct {
        int a;
    };
    struct NotValidStruct {
        bool b;
    };
    int count = -1;

    {
        Database<TestStruct> db(dbFileName);
        db.removeHalfRecords();
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Clear empty database") << count << 0;

    {
        Database<TestStruct> db(dbFileName);
        db.addRecord(TestStruct{1000});
        db.removeHalfRecords();
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Clear one record database") << count << 1;

    {
        Database<TestStruct> db(dbFileName);
        db.addRecord(TestStruct{1000});
        db.addRecord(TestStruct{1001});
        db.removeHalfRecords();
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Clear two record database") << count << 1;

    {
        Database<TestStruct> db(dbFileName);
        for (int i = 0; i < 30; ++i) {
            db.addRecord(TestStruct{1000});
        }
        db.removeHalfRecords();
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Clear 30 records database") << count << 15;

    {
        Database<TestStruct> db(dbFileName);
        for (int i = 0; i < 31; ++i) {
            db.addRecord(TestStruct{1000});
        }
        db.removeHalfRecords();
        count = db.numberOfRecords();
    }
    removeDb();
    QTest::addRow("Clear 31 records database") << count << 16;
}

void TestDatabase::testCheckTypes() {
    QFETCH(bool, actual);
    QFETCH(bool, needed);

    QCOMPARE(actual, needed);
}

void TestDatabase::testCheckTypes_data() {
    QTest::addColumn<bool>("actual");
    QTest::addColumn<bool>("needed");

    struct TestStruct {
        int a;
    };
    struct TestStruct2 {
        bool a;
    };

    bool result = false;

    {
        Database<TestStruct> db(dbFileName);
    }
    {
        Database<TestStruct> db(dbFileName);
        result = db.checkTypes();
    }
    QTest::newRow("right struct") << result << true;
    {
        Database<TestStruct2> db(dbFileName);
        result = db.checkTypes();
    }
    QTest::newRow("wrong struct") << result << false;

    removeDb();

}


void TestDatabase::testReadData() {
    QFETCH(bool, result);
    QVERIFY(result);
}

void TestDatabase::testReadData_data() {
    QTest::addColumn<bool>("result");

    struct TestStruct {
        int a;
        QString s;
    };

    bool result = false;

    {
        Database<TestStruct> db(dbFileName);
        for (int i = 0; i < 30; ++i) {
            db.addRecord(TestStruct{i,QString::number(i)});
        }
    }
    {
        Database<TestStruct> db(dbFileName);
        auto res = db.read(3, 1);
        auto d = res.at(0);
        result = (d.s == "3");
    }
    QTest::newRow("test string") << result;
    removeDb();
}

void TestDatabase::testReadDataCount() {
    QFETCH(uint, test_size);
    QFETCH(uint, result);

    QCOMPARE(test_size, result);
}

void TestDatabase::testReadDataCount_data() {
    QTest::addColumn<uint>("test_size");
    QTest::addColumn<uint>("result");

    struct TestStruct {
        int a;
        QString s;
    };

    uint result = 100; // non-zero

    {
        Database<TestStruct> db(dbFileName);
        for (int i = 0; i < 30; ++i) {
            db.addRecord(TestStruct{i,QString::number(i)});
        }
    }
    {
        Database<TestStruct> db(dbFileName);
        auto res = db.read(3, 1);
        result = res.size();
    }
    QTest::newRow("one") << 1u << result;
    removeDb();


}



