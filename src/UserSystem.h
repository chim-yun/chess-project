#ifndef USERSYSTEM_H
#define USERSYSTEM_H

#include <string>
#include <unordered_map>
#include <optional>

namespace Chess {

struct UserDatabase {
    std::unordered_map<std::string, std::string> users; // username -> password
};

inline UserDatabase EmptyDatabase() {
    return UserDatabase{};
}

inline UserDatabase RegisterUser(UserDatabase db, const std::string& name, const std::string& password) {
    auto copy = db;
    copy.users.emplace(name, password);
    return copy;
}

inline bool LoginUser(const UserDatabase& db, const std::string& name, const std::string& password) {
    auto it = db.users.find(name);
    return it != db.users.end() && it->second == password;
}

} // namespace Chess

#endif // USERSYSTEM_H
