#ifndef USERSYSTEM_H
#define USERSYSTEM_H

#include <string>
#include <unordered_map>
#include <optional>
#include <fstream>

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

inline UserDatabase LoadDatabase(const std::string& path) {
    UserDatabase db;
    std::ifstream in(path);
    std::string user, pass;
    while (in >> user >> pass) {
        db.users[user] = pass;
    }
    return db;
}

inline void SaveDatabase(const UserDatabase& db, const std::string& path) {
    std::ofstream out(path);
    for (const auto& p : db.users) {
        out << p.first << ' ' << p.second << '\n';
    }
}

} // namespace Chess

#endif // USERSYSTEM_H
