#include "tst_benchdatabase.h"

#include "CommonDatabase/database.h"
#include "DebugOutput/debugoutput.h"

const QString dbFileName = "aTestDb.db";
const QString connectionName = "db";
const QString DB_TYPE = "QSQLITE";

void BenchDatabase::removeDb()
{
    QFile db(dbFileName);
    //QVERIFY(db.exists());
    // NOTE now not deleted
    bool success = db.remove();
    dbg << "base removed" << success;

}

void BenchDatabase::initTestCase() {
    removeDb();
}


void BenchDatabase::benchmarkRowIdCount() {
    struct Struct {
        int a;
    };

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

        QSqlQuery countQuery(db);
        QString countString = DatabaseDetail::maxRowIdQuery<0>();
        countQuery.prepare(countString);
        QBENCHMARK {
            countQuery.exec();
        }
    }
    QSqlDatabase::removeDatabase(connectionName);
    removeDb();
}

void BenchDatabase::benchmarkSqlCount() {
    struct Struct {
        int a;
    };

    {
        QSqlDatabase::addDatabase(DB_TYPE, connectionName).setDatabaseName(dbFileName);
        auto db = QSqlDatabase::database(connectionName);
        QSqlQuery addQuery(db);
        QString addString = DatabaseDetail::addRecordQuery<Struct, 0>();
        addQuery.prepare(addString);
        addQuery.addBindValue(1000);
        for (int i = 0; i < 30; ++i) {
            addQuery.exec();
        }

        QSqlQuery countQuery(db);
        QString countString = DatabaseDetail::countQuery<0>();
        countQuery.prepare(countString);
        QBENCHMARK {
            countQuery.exec();
        }
    }
    QSqlDatabase::removeDatabase(connectionName);
    removeDb();
}
