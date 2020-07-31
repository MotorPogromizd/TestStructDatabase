#include "tst_database.h"
#include "tst_databasedetail.h"
#include "tst_benchdatabase.h"
#include "tst_testmultitabledatabase.h"

//#include "../../TestCommonDatabase/CommonDatabaseProject/DebugOutput/debugoutput.h"
#include "../CommonDatabaseProject/DebugOutput/debugoutput.h"

int main(int argc, char *argv[])
{
    setDebugMessagePattern();
    {
        TestDatabaseDetail tdd;
        QTest::qExec(&tdd, argc, argv);
    }
    {
        TestDatabase tdb;
        QTest::qExec(&tdb, argc, argv);
    }
    {
        TestMultitableDatabase mtdb;
        QTest::qExec(&mtdb, argc, argv);
    }
    {
        BenchDatabase bdb;
        QTest::qExec(&bdb, argc, argv);
    }
    return 0;
}
