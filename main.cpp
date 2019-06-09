#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QQmlContext>
#include <QDebug>
#include "texthandler.h"
#include "dicthandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Text Analyser");
    QGuiApplication app(argc, argv);
    qmlRegisterType<TextHandler>("TextHandler", 1, 0, "TextHandler");
    qmlRegisterType<DictHandler>("DictHandler", 1, 0, "DictHandler");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
