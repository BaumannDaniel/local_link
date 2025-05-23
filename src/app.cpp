#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QLoggingCategory>

#include "ui/UsersListModel.h"

#if QT_CONFIG(permissions)
  #include <QPermission>
#endif

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.core.signal.warning=true");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    auto udp_socket_adapter_ptr = QSharedPointer<llink::UdpSocketAdapter>::create();
    auto network_api_ptr = QSharedPointer<llink::NetworkApi>::create(udp_socket_adapter_ptr);
    auto user_repository_ptr = QSharedPointer<llink::UserRepository>::create(network_api_ptr);
    auto user_status_manager_ptr = QSharedPointer<llink::UserStatusManager>::create(network_api_ptr);
    user_status_manager_ptr->send_user_info_broadcast();
    user_status_manager_ptr->send_user_info_query();
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [user_status_manager_ptr] {
        qDebug() << "App is shutting down!";
        user_status_manager_ptr->send_user_disconnect_broadcast();
    });
    llink::UsersListModel users_list_model = llink::UsersListModel(nullptr, user_repository_ptr, user_status_manager_ptr);
    engine.rootContext()->setContextProperty("users_list_model", &users_list_model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/home.qml")));
    return app.exec();
}
