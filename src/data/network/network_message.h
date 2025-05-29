#pragma once
#include <qhostaddress.h>

namespace llink {
    struct MessageType {
        static constexpr qint8 USER_INFO_QUERY = 11;
        static constexpr quint8 USER_DISCONNECTED = 12;
        static constexpr quint8 USER_INFO_RESPONSE = 13;
    };
    template <typename T> struct NetworkMessage {
        quint8 message_type;
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
