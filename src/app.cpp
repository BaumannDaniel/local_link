#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "ui/UsersListModel.h"

#if QT_CONFIG(permissions)
  #include <QPermission>
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    auto user_repository_ptr = QSharedPointer<llink::UserRepository>::create();
    auto user_scanner_ptr = QSharedPointer<llink::UserScanner>::create();
    llink::UsersListModel users_list_model = llink::UsersListModel(nullptr, user_repository_ptr, user_scanner_ptr);
    engine.rootContext()->setContextProperty("users_list_model", &users_list_model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/home.qml")));

    return app.exec();
}