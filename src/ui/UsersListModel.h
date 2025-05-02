#pragma once
#include <QAbstractListModel>
#include <qstring.h>

namespace llink {
    struct UiUser {
        QString name;
    };

    enum UiUserAttributeRoles {
        NameRole = Qt::UserRole + 1,
    };

    class UsersListModel : public QAbstractListModel {
        Q_OBJECT
        QList<UiUser> ui_users;

    protected:
        QHash<int, QByteArray> roleNames() const override;

    public:
        explicit UsersListModel(QObject *parent = nullptr);

        int columnCount(const QModelIndex &parent) const override;

        int rowCount(const QModelIndex &parent) const override;

        QVariant data(const QModelIndex &index, int role) const override;
    };
}