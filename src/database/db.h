#pragma once

#include <mysqlx/xdevapi.h>
#include "utilities.h"


class DBWorker {
public:


    DBWorker() : session_(server_name_, port_, user_name_, pass_) {
        session_.sql("USE polar_user").execute();
    };

    static DBWorker &GetInstance() {
        static DBWorker db_worker;
        return db_worker;
    }


    static bool UpdateDB(const std::string &table_name, const wjson &info);


    mysqlx::SqlResult SQL(const std::string &query);

private:
    const std::string server_name_ = "localhost";
    const int port_ = 33060;
    const std::string user_name_ = "voyko";
    const std::string pass_ = "2004";
    mysqlx::Session session_;
};


