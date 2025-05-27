#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QLoggingCategory>

#include "video_recorder.h"
#include "ui/users_list_model.h"
#include "ui/video_frame_item.h"
#include "ui/call_model.h"

#if QT_CONFIG(permissions)
  #include <QPermission>
#endif

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.core.signal.warning=true");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    auto video_recorder_ptr = QSharedPointer<llink::VideoRecorder>::create();
    auto udp_socket_adapter_ptr = QSharedPointer<llink::UdpSocketAdapter>::create();
    auto tcp_server_adapter_ptr = QSharedPointer<llink::TcpServerAdapter>::create();
    auto network_api_ptr = QSharedPointer<llink::NetworkApi>::create(udp_socket_adapter_ptr, tcp_server_adapter_ptr);
    auto user_repository_ptr = QSharedPointer<llink::UserRepository>::create(network_api_ptr);
    auto call_manager_ptr = QSharedPointer<llink::CallManager>::create(network_api_ptr);
    auto user_status_manager_ptr = QSharedPointer<llink::UserStatusManager>::create(network_api_ptr);
    user_status_manager_ptr->send_user_info_broadcast();
    user_status_manager_ptr->send_user_info_query();
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [user_status_manager_ptr] {
        qDebug() << "App is shutting down!";
        user_status_manager_ptr->send_user_disconnect_broadcast();
    });
    llink::users_list_model users_list_model = llink::users_list_model(nullptr, user_repository_ptr, user_status_manager_ptr);
    llink::CallModel call_model = llink::CallModel(video_recorder_ptr, call_manager_ptr);
    engine.rootContext()->setContextProperty("users_list_model", &users_list_model);
    engine.rootContext()->setContextProperty("call_model", &call_model);
    qmlRegisterType<llink::VideoFrameItem>("llink", 1, 0, "VideoFrameItem");
    engine.load(QUrl(QStringLiteral("qrc:/qml/root.qml")));
    video_recorder_ptr->start();
    return app.exec();
}
