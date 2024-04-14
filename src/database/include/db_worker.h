#pragma once

#include "db_utilities.h"
#include "../../polar_api/include/accesslink.h"

#include <frozen/bits/basic_types.h>

class DBWorker {
public:
    DBWorker();

    static DBWorker &GetInstance();

    void UpdateDB(const PolarUser &polar_user);

    mysqlx::SqlResult SQL(const std::string &query);

    mysqlx::Schema GetDB();

    mysqlx::Table GetTable(const std::string &table_name);

    mysqlx::SqlResult GetTableColumns(const std::string &table_name);

    bool FindTable(const std::string &table_name);

    mysqlx::SqlResult JoinAllTables();

private:
    static void RunSetup();

    static void SetupUser(mysqlx::Session &temp_session);

    static void SetupDB(mysqlx::Session &temp_session);

    static bool FindUser(mysqlx::Session &temp_session);

    static bool FindDB(mysqlx::Session &temp_session);

    static constexpr frozen::string server_name_ = "localhost";
    static constexpr int port_ = 33060;
    static constexpr frozen::string user_name_ = "polar_user";
    static constexpr frozen::string pass_ = "2004";
    static constexpr frozen::string db_name_ = "POLAR_DATA";

    mysqlx::Session session;
};


