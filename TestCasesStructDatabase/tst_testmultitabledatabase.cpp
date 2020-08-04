#include "tst_testmultitabledatabase.h"

#include "../StructDatabaseProject/QtStructDatabase/database.h"
#include "../StructDatabaseProject/QtDebugPrint/debugoutput.h"

const QString dbFileName = "aTestDb.db";
const QString connectionName = "db";
const QString DB_TYPE = "QSQLITE";

void TestMultitableDatabase::removeDb() {
    QFile db(dbFileName);
    //QVERIFY(db.exists());
    // NOTE now not deleted
    bool success = db.remove();
    dbg << "base removed" << success;
}

void TestMultitableDatabase::initTestCase() {
    removeDb();
}

void TestMultitableDatabase::testTableCount() {
    QFETCH(uint, test_size);
    QFETCH(uint, result);

    QCOMPARE(test_size, result);
}

void TestMultitableDatabase::testTableCount_data() {
    QTest::addColumn<uint>("test_size");
    QTest::addColumn<uint>("result");

    uint count;

    struct Struct1 {
        int i;
    };
    struct Struct2 {
        bool b;
    };
    struct Struct3 {
        double d;
    };
    struct Struct4 {
        qint64 f;
        QString s;
    };

    {
        Database<Struct4> db1(dbFileName);
    }
    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        count = db.tables().count();
    }
    QSqlDatabase::removeDatabase(connectionName);
    QTest::newRow("one table") << 1u << count;
    removeDb();

    {
        Database<Struct1, Struct3> db2(dbFileName);
    }
    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        count = db.tables().count();
    }
    QSqlDatabase::removeDatabase(connectionName);
    QTest::newRow("two table") << 2u << count;
    removeDb();

    {
        Database<Struct1, Struct4, Struct3> db3(dbFileName);
    }
    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        count = db.tables().count();
    }
    QSqlDatabase::removeDatabase(connectionName);
    QTest::newRow("three table") << 3u << count;
    removeDb();

    {
        Database<Struct4, Struct3, Struct2, Struct1> db4(dbFileName);
    }
    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        count = db.tables().count();
    }
    QSqlDatabase::removeDatabase(connectionName);
    QTest::newRow("four table") << 4u << count;
    removeDb();

}

void TestMultitableDatabase::testRecordCount() {
    QFETCH(uint, test_size);
    QFETCH(uint, result);

    QCOMPARE(test_size, result);
}

void TestMultitableDatabase::testRecordCount_data() {
    QTest::addColumn<uint>("test_size");
    QTest::addColumn<uint>("result");

    struct Struct1 {
        int i;
    };
    struct Struct2 {
        double d;
    };

    {
        Database<Struct1> db(dbFileName);
        db.addRecord(Struct1{1});
        QTest::newRow("one length no template") << 1u << db.numberOfRecords();
        QTest::newRow("one length size_t template") << 1u << db.numberOfRecords<0>();
        // TODO type template method
        QTest::newRow("one length typename template") << 1u << db.numberOfRecords<Struct1>();
    }
    removeDb();

    {
        Database<Struct2, Struct1> db(dbFileName);
        db.addRecord(Struct1{1});
        db.addRecord(Struct1{2});
        db.addRecord(Struct2{1.0});
        db.addRecord(Struct2{2.0});
        db.addRecord(Struct2{3.0});
        QTest::newRow("two length size_t template") << 2u << db.numberOfRecords<1>();
        QTest::newRow("two length typename template") << 2u << db.numberOfRecords<Struct1>();
        QTest::newRow("three length size_t template") << 3u << db.numberOfRecords<0>();
        QTest::newRow("three length typename template") << 3u << db.numberOfRecords<Struct2>();
    }
    removeDb();

}
