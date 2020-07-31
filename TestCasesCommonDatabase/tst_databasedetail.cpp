#include "tst_databasedetail.h"

#include "CommonDatabase/database_detail.h"


void TestDatabaseDetail::testTableName() {
    QFETCH(QString, testString);
    QFETCH(QString, result);

    QCOMPARE(testString, result);
}

void TestDatabaseDetail::testTableName_data() {
    QTest::addColumn<QString>("testString");
    QTest::addColumn<QString>("result");

    QTest::newRow("table 0") << DatabaseDetail::tableName<0>() << QString("table0");
    QTest::newRow("table 1") << DatabaseDetail::tableName<1>() << QString("table1");
    QTest::newRow("table 2") << DatabaseDetail::tableName<2>() << QString("table2");
    QTest::newRow("table 3") << DatabaseDetail::tableName<3>() << QString("table3");
    QTest::newRow("table 1000") << DatabaseDetail::tableName<1000>() << QString("table1000");
}

void TestDatabaseDetail::testColumnName() {
    QFETCH(QString, testString);
    QFETCH(QString, result);

    QCOMPARE(testString, result);
}

void TestDatabaseDetail::testColumnName_data() {
    QTest::addColumn<QString>("testString");
    QTest::addColumn<QString>("result");

    struct Struct1 {
        int a;
        double d;
        qint64 i;
        bool b;
        QString s;
        QDateTime t;
    };

    QTest::newRow("int at 0")
            << DatabaseDetail::columnName<Struct1, 0>()
            << "_0Integer";
    QTest::newRow("double at 1")
            << DatabaseDetail::columnName<Struct1, 1>()
            << "_1Double";
    QTest::newRow("qint64 at 2")
            << DatabaseDetail::columnName<Struct1, 2>()
            << "_2Int64";
    QTest::newRow("bool at 3")
            << DatabaseDetail::columnName<Struct1, 3>()
            << "_3Bool";
    QTest::newRow("QString at 4")
            << DatabaseDetail::columnName<Struct1, 4>()
            << "_4QString";
    QTest::newRow("QDateTime at 5")
            << DatabaseDetail::columnName<Struct1, 5>()
            << "_5QDateTime";
}

void TestDatabaseDetail::testColumnType() {
    QFETCH(QString, testString);
    QFETCH(QString, result);

    QCOMPARE(testString, result);
}

void TestDatabaseDetail::testColumnType_data() {
    QTest::addColumn<QString>("testString");
    QTest::addColumn<QString>("result");

    struct Struct1 {
        bool b;
        int a;
        double d;
        qint64 i;
        QString s;
        QDateTime t;
    };
    QTest::newRow("bool at 0")
            << DatabaseDetail::columnType<Struct1, 0>()
            << "BOOLEAN";
    QTest::newRow("int at 1")
            << DatabaseDetail::columnType<Struct1, 1>()
            << "INTEGER";
    QTest::newRow("double at 2")
            << DatabaseDetail::columnType<Struct1, 2>()
            << "REAL";
    QTest::newRow("qint64 at 3")
            << DatabaseDetail::columnType<Struct1, 3>()
            << "INTEGER";
    QTest::newRow("QString at 4")
            << DatabaseDetail::columnType<Struct1, 4>()
            << "STRING";
    QTest::newRow("QDateTime at 5")
            << DatabaseDetail::columnType<Struct1, 5>()
            << "INTEGER";
}

void TestDatabaseDetail::testCreateTablePartQuery() {
    QFETCH(QString, testString);
    QFETCH(QString, result);

    QCOMPARE(testString, result);
}

void TestDatabaseDetail::testCreateTablePartQuery_data() {
    QTest::addColumn<QString>("testString");
    QTest::addColumn<QString>("result");

    struct Struct1 {
        int a;
    };
    QTest::newRow("Struct1")
            << DatabaseDetail::createTableQueryPart<Struct1>()
            << "_0Integer INTEGER";

    struct Struct2 {
        bool a;
    };
    QTest::newRow("Struct2")
            << DatabaseDetail::createTableQueryPart<Struct2>()
            << "_0Bool BOOLEAN";

    struct Struct3 {
        qint64 i;
        double d;
    };
    QTest::newRow("Struct3")
            << DatabaseDetail::createTableQueryPart<Struct3>()
            << "_0Int64 INTEGER, _1Double REAL";

    struct Struct4 {
        QString s;
        QDateTime dt;
        bool a;
    };
    QTest::newRow("Struct4")
            << DatabaseDetail::createTableQueryPart<Struct4>()
            << "_0QString STRING, _1QDateTime INTEGER, "
               "_2Bool BOOLEAN";
}


void TestDatabaseDetail::testCreateTableQuery() {
    QFETCH(QString, testString);
    QFETCH(QString, result);

    QCOMPARE(testString, result);
}

void TestDatabaseDetail::testCreateTableQuery_data() {
    QTest::addColumn<QString>("testString");
    QTest::addColumn<QString>("result");

    struct Struct1 {
        int a;
    };
    QTest::newRow("Struct1")
            << DatabaseDetail::createTableQuery<Struct1, 0>()
            << "CREATE TABLE table0(_0Integer INTEGER);";

    struct Struct2 {
        bool a;
    };
    QTest::newRow("Struct2")
            << DatabaseDetail::createTableQuery<Struct2, 0>()
            << "CREATE TABLE table0(_0Bool BOOLEAN);";

    struct Struct3 {
        qint64 i;
        double d;
        QString s;
        QDateTime dt;
        bool a;
    };
    QTest::newRow("Struct3")
            << DatabaseDetail::createTableQuery<Struct3, 0>()
            << QString("CREATE TABLE ")
               + DatabaseDetail::tableName<0>()
               + "("
               "_0Int64 INTEGER, _1Double REAL, "
               "_2QString STRING, _3QDateTime INTEGER, "
               "_4Bool BOOLEAN);";

}

void TestDatabaseDetail::testAddQuery() {
    QFETCH(QString, testString);
    QFETCH(QString, result);

    QCOMPARE(testString, result);
}

void TestDatabaseDetail::testAddQuery_data() {
    QTest::addColumn<QString>("testString");
    QTest::addColumn<QString>("result");

    struct Struct1 {
        int a;
    };
    QTest::newRow("Struct1")
            << DatabaseDetail::addRecordQuery<Struct1, 0>()
            << (QString("INSERT INTO ")
                + DatabaseDetail::tableName<0>()
                + "(_0Integer)"
                  " VALUES(?)");

    struct Struct2 {
        bool a;
    };
    QTest::newRow("Struct2")
            << DatabaseDetail::addRecordQuery<Struct2, 0>()
            << QString("INSERT INTO ")
               + DatabaseDetail::tableName<0>()
               + "(_0Bool)"
                 " VALUES(?)";

    struct Struct3 {
        qint64 i;
        double d;
        QString s;
        QDateTime dt;
        bool a;
    };
    QTest::newRow("Struct3")
            << DatabaseDetail::addRecordQuery<Struct3, 0>()
            << QString("INSERT INTO ")
               + DatabaseDetail::tableName<0>()
               + "(_0Int64,_1Double,"
                 "_2QString,_3QDateTime,"
                 "_4Bool)"
                 " VALUES(?,?,?,?,?)";

}

void TestDatabaseDetail::testOneLength() {
    QFETCH(bool, testLength);
    QFETCH(bool, result);

    QCOMPARE(testLength, result);
}

void TestDatabaseDetail::testOneLength_data() {
    QTest::addColumn<bool>("testLength");
    QTest::addColumn<bool>("result");

    struct Struct1 {
        int a;
    };
    struct Struct2 {
        double a;
    };

    bool result = false;
    {
        using L = Conversions::TypeList<int>;
        result = DatabaseDetail::OneLength<L>::value;
    }
    QTest::newRow("int") << result << true;

    {
        using L = Conversions::TypeList<Struct1>;
        result = DatabaseDetail::OneLength<L>::value;
    }
    QTest::newRow("int") << result << true;

    result = false;
    {
        using L = Conversions::TypeList<Struct1>;
        result = DatabaseDetail::OneLength<L>::value;
    }
    QTest::newRow("int") << result << true;

    {
        using L = Conversions::TypeList<>;
        result = DatabaseDetail::OneLength<L>::value;
    }
    QTest::newRow("zero") << result << false;

    {
        using L = Conversions::TypeList<int, Struct1>;
        result = DatabaseDetail::OneLength<L>::value;
    }
    QTest::newRow("two") << result << false;

    {
        using L = Conversions::TypeList<Struct1, int>;
        result = DatabaseDetail::OneLength<L>::value;
    }
    QTest::newRow("two") << result << false;

    {
        using L = Conversions::TypeList<Struct2, Struct1>;
        result = DatabaseDetail::OneLength<L>::value;
    }
    QTest::newRow("two structs") << result << false;

    {
        using L = Conversions::TypeList<int>;
        result = DatabaseDetail::OneLengthV<L>;
    }
    QTest::newRow("int") << result << true;

    {
        using L = Conversions::TypeList<Struct1>;
        result = DatabaseDetail::OneLengthV<L>;
    }
    QTest::newRow("int") << result << true;

    result = false;
    {
        using L = Conversions::TypeList<Struct1>;
        result = DatabaseDetail::OneLengthV<L>;
    }
    QTest::newRow("int") << result << true;

    {
        using L = Conversions::TypeList<>;
        result = DatabaseDetail::OneLengthV<L>;
    }
    QTest::newRow("zero") << result << false;

    {
        using L = Conversions::TypeList<int, Struct1>;
        result = DatabaseDetail::OneLengthV<L>;
    }
    QTest::newRow("two") << result << false;

    {
        using L = Conversions::TypeList<Struct1, int>;
        result = DatabaseDetail::OneLengthV<L>;
    }
    QTest::newRow("two") << result << false;

    {
        using L = Conversions::TypeList<Struct2, Struct1>;
        result = DatabaseDetail::OneLengthV<L>;
    }
    QTest::newRow("two structs") << result << false;

    {
        result = DatabaseDetail::OneLength<Conversions::TypeList<int>>::value;
    }
    QTest::newRow("int") << result << true;

    {
        result = DatabaseDetail::OneLength<Conversions::TypeList<Struct1>>::value;
    }
    QTest::newRow("int") << result << true;

    result = false;
    {
        result = DatabaseDetail::OneLength<Conversions::TypeList<Struct1>>::value;
    }
    QTest::newRow("int") << result << true;

    {
        result = DatabaseDetail::OneLength<Conversions::TypeList<>>::value;
    }
    QTest::newRow("zero") << result << false;

    {
        result = DatabaseDetail::OneLength<Conversions::TypeList<int, Struct1>>::value;
    }
    QTest::newRow("two") << result << false;

    {
        result = DatabaseDetail::OneLength<Conversions::TypeList<Struct1, int>>::value;
    }
    QTest::newRow("two") << result << false;

    {
        result = DatabaseDetail::OneLength<Conversions::TypeList<Struct2, Struct1>>::value;
    }
    QTest::newRow("two structs") << result << false;

    {
        result = DatabaseDetail::OneLengthV<Conversions::TypeList<int>>;
    }
    QTest::newRow("int") << result << true;

    {
        result = DatabaseDetail::OneLengthV<Conversions::TypeList<Struct1>>;
    }
    QTest::newRow("int") << result << true;

    result = false;
    {
        result = DatabaseDetail::OneLengthV<Conversions::TypeList<Struct1>>;
    }
    QTest::newRow("int") << result << true;

    {
        result = DatabaseDetail::OneLengthV<Conversions::TypeList<>>;
    }
    QTest::newRow("zero") << result << false;

    {
        result = DatabaseDetail::OneLengthV<Conversions::TypeList<int, Struct1>>;
    }
    QTest::newRow("two") << result << false;

    {
        result = DatabaseDetail::OneLengthV<Conversions::TypeList<Struct1, int>>;
    }
    QTest::newRow("two") << result << false;

    {
        result = DatabaseDetail::OneLengthV<Conversions::TypeList<Struct2, Struct1>>;
    }
    QTest::newRow("two structs") << result << false;

}




void TestDatabaseDetail::testRemoveHalfRecordsQuery() {
    QString result("DELETE FROM ");
    result += DatabaseDetail::tableName<0>();
    result += " WHERE _rowid_ <= "
              "(SELECT MAX(_rowid_) FROM ";
    result += DatabaseDetail::tableName<0>();
    result += ")/2";

    QCOMPARE(DatabaseDetail::removeHalfRecordsQuery<0>(), result);
}

void TestDatabaseDetail::testCleanDatabase() {
    QString result("DELETE FROM ");
    result += DatabaseDetail::tableName<0>();

    QCOMPARE(DatabaseDetail::cleanQuery<0>(), result);
}
