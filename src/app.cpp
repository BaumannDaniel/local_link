#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "ui/users_list_model.h"

#if QT_CONFIG(permissions)
  #include <QPermission>
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    llink::users_list_model users_list_model;
    engine.rootContext()->setContextProperty("users_list_model", &users_list_model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/home.qml")));

    return app.exec();
}