#pragma once
#include <QAbstractListModel>
#include <qstring.h>

#include "user_repository.h"
#include "user_scanner.h"

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
        QSharedPointer<IUserScanner> i_user_scanner_ptr;

    private slots:
        void update_users();

    protected:
        QHash<int, QByteArray> roleNames() const override;

    public:
        UsersListModel(
            QObject *parent,
            QSharedPointer<IUserRepository> i_user_repository_ptr,
            QSharedPointer<IUserScanner> i_user_scanner_ptr
        );

        int columnCount(const QModelIndex &parent) const override;

        int rowCount(const QModelIndex &parent) const override;

        QVariant data(const QModelIndex &index, int role) const override;

        Q_INVOKABLE void scan_users();
    };
}
