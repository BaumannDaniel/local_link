#include "user_repository.h"
llink::UserRepository::UserRepository() {
    User user1 = { "test1", "test_ip" };
    users.append(user1);
    emit users_updated();
}

QList<llink::User> llink::UserRepository::get_users() const {
    return this->users;
}
