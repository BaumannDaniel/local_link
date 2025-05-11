#include "UsersListModel.h"

#include <utility>

QHash<int, QByteArray> llink::UsersListModel::roleNames() const {
    return {
        {NameRole, "name"},
    };
}

llink::UsersListModel::UsersListModel(
    QObject *parent,
    QSharedPointer<IUserRepository> i_user_repository_ptr,
    QSharedPointer<IUserScanner> i_user_scanner_ptr
) : QAbstractListModel(parent),
    i_user_repository_ptr_(std::move(i_user_repository_ptr)),
    i_user_scanner_ptr(std::move(i_user_scanner_ptr)) {
    connect(
        i_user_repository_ptr_.get(), &IUserRepository::users_updated,
        this, &UsersListModel::update_users
    );
    update_users();
}

void llink::UsersListModel::update_users() {
    ui_users_.clear();
    auto users = i_user_repository_ptr_->get_users();
    for (const auto &[name, ip]: users) {
        UiUser ui_user = {name};
        ui_users_.append(ui_user);
    }
}


int llink::UsersListModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

int llink::UsersListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return ui_users_.size();
}

QVariant llink::UsersListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= ui_users_.size()) return {};
    Q_UNUSED(role);
    return ui_users_[index.row()].name;
}

void llink::UsersListModel::scan_users() {
    i_user_scanner_ptr->send_broadcast();
}
