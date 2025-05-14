#pragma once
#include <QAbstractListModel>
#include <qstring.h>

#include "user_repository.h"
#include "user_status_manager.h"

namespace llink {
    struct UiUser {
        QString name;
    };

    enum UiUserAttributeRoles {
        NameRole = Qt::UserRole + 1,
    };

    class UsersListModel : public QAbstractListModel {
        Q_OBJECT
        QList<UiUser> ui_users_;
        QSharedPointer<IUserRepository> i_user_repository_ptr_;
        QSharedPointer<IUserStatusManager> i_user_status_manager_ptr_;

    private slots:
        void update_users();

    protected:
        QHash<int, QByteArray> roleNames() const override;

    public:
        UsersListModel(
            QObject *parent,
            QSharedPointer<IUserRepository> i_user_repository_ptr,
            QSharedPointer<IUserStatusManager> i_user_status_manager_ptr
        );

        int columnCount(const QModelIndex &parent) const override;

        int rowCount(const QModelIndex &parent) const override;

        QVariant data(const QModelIndex &index, int role) const override;

        Q_INVOKABLE void scan_users() const;
    };
}
