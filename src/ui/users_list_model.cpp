#include "users_list_model.h"

#include <utility>

QHash<int, QByteArray> llink::users_list_model::roleNames() const {
    return {
        {NameRole, "name"},
        {AddressRole, "address"}
    };
}

llink::users_list_model::users_list_model(
    QObject *parent,
    QSharedPointer<IUserRepository> i_user_repository_ptr,
    QSharedPointer<IUserStatusManager> i_user_status_manager_ptr
) : QAbstractListModel(parent),
    i_user_repository_ptr_(std::move(i_user_repository_ptr)),
    i_user_status_manager_ptr_(std::move(i_user_status_manager_ptr)) {
    connect(
        i_user_repository_ptr_.get(), &IUserRepository::users_updated,
        this, &users_list_model::update_users
    );
    update_users();
}

void llink::users_list_model::update_users() {
    qDebug() << "Updating users";
    beginResetModel();
    ui_users_.clear();
    for (auto users = i_user_repository_ptr_->get_users(); const auto &[name, ip]: users) {
        UiUser ui_user = {name, ip.toString()};
        ui_users_.append(ui_user);
        emit dataChanged(index(ui_users_.size()-1), index(ui_users_.size()-1));
    }
    endResetModel();
}


int llink::users_list_model::columnCount(const QModelIndex &parent) const {
    return 2;
}

int llink::users_list_model::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return ui_users_.size();
}

QVariant llink::users_list_model::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= ui_users_.size()) return {};

    const UiUser &user = ui_users_[index.row()];
    switch (role) {
        case NameRole:
            return user.name;
        case AddressRole:
            return user.address;
        default:
            return {};
    }
}

void llink::users_list_model::scan_users() const {
    i_user_status_manager_ptr_->send_user_info_query();
}
