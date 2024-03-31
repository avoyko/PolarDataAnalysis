#pragma once

#include <mysqlx/xdevapi.h>
#include "../utilities.h"
#include "../accesslink.h"

class DBWorker {
public:
    DBWorker() : session_(server_name_, port_, user_name_, pass_) {
        if (!DBExists()) {
            SetupDB();
        }
    };

public:
    static DBWorker &GetInstance() {
        static DBWorker db_worker;
        return db_worker;
    }

    static void UpdateDB(const PolarUser &polar_user);

    mysqlx::SqlResult SQL(const std::string &query);

    void SetupDB();

    bool DBExists();

private:
    static constexpr std::string server_name_ = "localhost";
    static constexpr int port_ = 33060;
    static constexpr std::string user_name_ = "polar_user";
    static constexpr std::string pass_ = "2004";
    static constexpr std::string db_name_ = "POLAR_DATA";
    mysqlx::Session session_;
};
