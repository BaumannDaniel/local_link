#pragma once
#include <QAbstractListModel>
#include <qstring.h>

#include "user_repository.h"

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

    private slots:
        void update_users();

    protected:
        QHash<int, QByteArray> roleNames() const override;

    public:
        UsersListModel(
            QObject *parent,
            QSharedPointer<IUserRepository> i_user_repository_ptr
        );

        int columnCount(const QModelIndex &parent) const override;

        int rowCount(const QModelIndex &parent) const override;

        QVariant data(const QModelIndex &index, int role) const override;
    };
}
