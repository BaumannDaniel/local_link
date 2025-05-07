#pragma once
#include <QObject>

#include "user.h"

namespace llink {
    class IUserRepository : public QObject {
        Q_OBJECT
    signals:
        void users_updated();

    public:
        explicit IUserRepository(QObject* parent = nullptr) : QObject(parent) {}
        virtual QList<User> get_users() const = 0;
    };

    class UserRepository : public IUserRepository {
        Q_OBJECT
        QList<User> users;

    public:
        UserRepository();
        QList<User> get_users() const override;
    };
}
