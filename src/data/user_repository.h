#pragma once
#include <QObject>

#include "user.h"

namespace llink {
    class IUserRepository : public QObject {
        Q_OBJECT
    signals:
        void users_updated(QList<llink::User>) const;
    };

    class UserRepository : public IUserRepository {
        Q_OBJECT
        QList<User> users;

    public:
        UserRepository();
    };
}
