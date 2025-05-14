#pragma once
#include <qhostaddress.h>

namespace llink {
    struct MessageType {
        static constexpr quint16 USER_INFO_QUERY = 1000;
        static constexpr quint16 USER_DISCONNECTED = 1001;
        static constexpr quint16 USER_INFO_RESPONSE = 1002;
    };
    template <typename T> struct NetworkMessage {
        quint16 message_type;
        T payload;
    };
    template <typename T> struct NetworkResponse {
        QHostAddress sender_address;
        T payload;
    };

    struct UserInfo {
        QString name;
    };

    // Serialization
    inline QDataStream &operator<<(QDataStream &out, const UserInfo &user_info) {
        out << user_info.name;
        return out;
    }

    // Deserialization
    inline QDataStream &operator>>(QDataStream &in, UserInfo &user_info) {
        in >> user_info.name;
        return in;
    }
}
