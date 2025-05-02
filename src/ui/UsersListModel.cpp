#include "UsersListModel.h"

QHash<int, QByteArray> llink::UsersListModel::roleNames() const {
    return {
        {NameRole, "name"},
    };
}

llink::UsersListModel::UsersListModel(QObject *parent) : QAbstractListModel(parent) {
    UiUser user1 = {"User1"};
    UiUser user2 = {"User2"};
    ui_users.append(user1);
    ui_users.append(user2);
}

int llink::UsersListModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

int llink::UsersListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return ui_users.size();
}

QVariant llink::UsersListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= ui_users.size()) return {};
    Q_UNUSED(role);
    return ui_users[index.row()].name;
}
