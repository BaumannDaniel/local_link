#pragma once

#include <QString>

namespace llink {
    struct User {
        QString name;
        QHostAddress ip;
    };
}
