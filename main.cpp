#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QQmlContext>
#include <QDebug>
#include "wrappers/filewrap.h"
#include "wrappers/dictwrap.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Text Analyser");
    QGuiApplication app(argc, argv);
    qmlRegisterType<FileWrap>("FileWrap", 1, 0, "FileWrap");
    qmlRegisterType<DictWrap>("DictWrap", 1, 0, "DictWrap");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
