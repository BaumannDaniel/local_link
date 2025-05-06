#include "user_repository.h"
llink::UserRepository::UserRepository() {
    User user1 = { "test1", "test_ip" };
    users.append(user1);
    emit users_updated(users);
}

