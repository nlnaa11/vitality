#include <QApplication>
#include <QStandardPaths>
#include <QDir>
#include "ExerciseMap.h"
#include "initDB.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)
                    + "/Vitality";
    QDir dir(path);

    if(!dir.exists())
    {
        bool luck = dir.mkdir(path);
        if(!luck) return 1;
    }

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Vitality");
    QCoreApplication::setApplicationVersion("version 1.0");

    static bool luck{true};
    InitDB db;
    db.connectDB(luck);

    if(!luck) return 1;

    ExerciseMap w;
    w.show_PeriodMap();

    return a.exec();
}

