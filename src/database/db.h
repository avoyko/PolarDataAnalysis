#pragma once

#include <mysqlx/xdevapi.h>
#include "../utilities.h"
#include "../accesslink.h"

class DBWorker {
public:

    explicit DBWorker();

    static DBWorker &GetInstance();

    static void UpdateDB(const PolarUser &polar_user);

    mysqlx::SqlResult SQL(const std::string &query);

    void SetupDB();

    bool FindDB();

    mysqlx::Schema GetDB();

    mysqlx::Table GetTable(const std::string &table_name);

    bool FindTable(const std::string &table_name);


public:
    mysqlx::Session session;

private:
    static constexpr frozen::string server_name_ = "localhost";
    static constexpr int port_ = 33060;
    static constexpr frozen::string user_name_ = "polar_user";
    static constexpr frozen::string pass_ = "2004";
    static constexpr frozen::string db_name_ = "POLAR_DATA";
};
