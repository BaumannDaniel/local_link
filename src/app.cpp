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
    auto udp_socket_adapter_ptr = QSharedPointer<llink::UdpSocketAdapter>::create();
    auto network_api_ptr = QSharedPointer<llink::NetworkApi>::create(udp_socket_adapter_ptr);
    auto user_repository_ptr = QSharedPointer<llink::UserRepository>::create(network_api_ptr);
    auto user_status_manager_ptr = QSharedPointer<llink::UserStatusManager>::create(network_api_ptr);
    user_status_manager_ptr->send_user_info_broadcast();
    user_status_manager_ptr->send_user_info_query();
    llink::UsersListModel users_list_model = llink::UsersListModel(nullptr, user_repository_ptr, user_status_manager_ptr);
    engine.rootContext()->setContextProperty("users_list_model", &users_list_model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/home.qml")));

    return app.exec();
}