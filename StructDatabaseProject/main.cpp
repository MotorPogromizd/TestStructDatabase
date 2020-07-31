#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include <tuple>
#include <utility>
#include <type_traits>
#include "DebugOutput/debugoutput.h"

#include "CommonDatabase/database.h"
#include "CommonDatabase/TupleConversions/structconversions.h"

#include "CommonDatabase/databaseviewmodel.h"
#include "CommonDatabase/eventdatabase.h"

struct TestStructMain {
    //QDateTime time;
    double d;
    QString message;
};
struct TestStructMain2 {
    int i;
    bool b;
};

struct ComplexStructMain {
    int i;
    TestStructMain s;
};


//struct BaseStruct {
//    int i;
////    double d;
//};
//template <typename T>
//struct ChildStruct : public T {
//    double d;
//};

//namespace std {
//template <typename T>
//struct tuple_size<ChildStruct<T>>
//        : integral_constant<size_t, ::StructConversions::Detail::to_tuple_size<T>::value+1 >{};

////template <typename T>
////struct tuple_size<ChildStruct<T>> {
////    static const size_t value
////    = size_t(1)
////            +tuple_size<decltype(TupleConversions::makeTuple(T))>::value;
////};

//template < typename T>
//struct tuple_element<0, ChildStruct<T>> {
//    using type = double;
//};
//template <size_t I, typename T>
//struct tuple_element<I, ChildStruct<T>> {
//    using tupleType = typename ::StructConversions::StructExtractor<T>::TupleType;
//    using type = tuple_element_t<I-1, tupleType>;
//};
////template <typename T>
////auto get<0>(ChildStruct<T> cs) {
////    if constexpr (I == 0) {
////        return cs.d;
////    }
////    else {
////        const T& t = cs;
////        return std::get<I-1>(t);
////    }
////}

//} // namespace std

//template <size_t I, typename T>
//auto get(ChildStruct<T> cs) {
//    if constexpr (I == 0) {
//        return cs.d;
//    }
//    else {
//        const T& t = cs;
//        auto tu = TupleConversions::makeTuple(t);
//        return std::get<I-1>(tu);
//    }
//}

QDebug operator<<(QDebug debug, const TestStructMain& ts) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "TestStruct("
                    //<< ts.time.toString("dd.MM.yyyy HH:mm:ss")
                    << ts.d
                    << "; "
                    << ts.message
                    << ")";
    //std::get
    return debug;
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    setDebugMessagePattern();
    QGuiApplication app(argc, argv);

//    {
//        Database<TestStructMain, TestStructMain2> db("testtwotable.db");
//        dbg << db.numberOfRecords<TestStructMain>()
//            << db.numberOfRecords<0>();
//        dbg << db.numberOfRecords<TestStructMain2>()
//            << db.numberOfRecords<1>();
//        // WARNING check that code below not compile
//        //dbg << db.numberOfRecords();
//        //auto v = db.read(0, 1);
//    }

//    {
//        Database<ComplexStructMain> db("onecomplextable.db");
//        ComplexStructMain s {
//            0, {QDateTime::currentDateTime(), QString("test message")}
//        };
//        db.addRecord(s);
//        dbg << db.numberOfRecords();
        // WARNING check that code below not compile
        //dbg << db.numberOfRecords();
        //auto v = db.read(0, 1);
//    }



//    {
//        Database<TestStruct> db("testdbmaincpp.db");

//        for (auto i = 0; i < 30; ++i) {
//            TestStruct ts{
//                QDateTime::currentDateTime(),
//                QString::number(i) + "th message"
//            };
//            db.addRecord(ts);
//        }
//        //dbg << db.removeHalfRecords();
//        //dbg << db.removeHalfRecords();
//        dbg << db.numberOfRecords();

//        //auto list = db.read(1, 2);
//        //dbg << list;
//    }

    //BaseStruct bs { 4 };
//    ChildStruct<BaseStruct> cs { 5, 6.6 };
    //dbg << cs.i << cs.d;
//    auto t = TupleConversions::makeTuple(cs);
//    dbg << std::get<1>(t);

//    dbg << FilterDetail::IsColumn<FilterDetail::Column<4>>::value
//        << FilterDetail::IsColumn<QVector<int>>::value;

    QByteArray qt = QByteArray::number(QT_VERSION, 16);

    dbg << "##" << qt;
    DatabaseViewModel<TestStructMain> model(
                "testdbmaincppviewmodel.db",//"modelmaincpp.db",
                {"date", "message"}, true
                );

    EventDatabase<TestStructMain> eventDatabase(
                "testeventmaincpp.db",
                {"number", "message"}
                );

    TestStructMain s {
        458.9,//QDateTime::currentDateTime(),
        QString("test message: ") + QDateTime::currentDateTime().toString("HH:mm:ss.zzz")
    };
    model.addRecord(s);

    QTimer* t = new QTimer();
    t->setSingleShot(true);
    QObject::connect(t, &QTimer::timeout,
                     [&eventDatabase]() {
        for (int i = 0; i < 1000; ++i) {
            TestStructMain s {
                int(i),//QDateTime::currentDateTime(),
                QString("test message: ") + QDateTime::currentDateTime().toString("HH:mm:ss.zzz")
            };
            eventDatabase.addRecord(s);
        }
//        QCoreApplication::exit(0);
    });

    t->start(1000);
//    eventDatabase.addRecord(s);
//    using ER=EventDatabaseRecord<TestStructMain>;
//    auto rec = ER(s, 250, QDateTime::currentDateTime());
//    using T = DatabaseRecord<ER>;
//    auto rec2 = T(1234, rec);
//    dbg << StructConversions::Detail::to_tuple_size<std::decay_t<T>>::value << rec.id;
//    auto tup = TupleConversions::makeTuple(rec);
//    auto tup2 = TupleConversions::makeTuple(rec2);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("databaseModel", &model);
    engine.rootContext()->setContextProperty("eventDatabase", &eventDatabase);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
