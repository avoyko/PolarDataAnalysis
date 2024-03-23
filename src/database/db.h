#pragma once

#include <mysqlx/xdevapi.h>

#include "utilities.h"
#include <ctime>
#include "../json_helpers/exercises.h"


class DBWorker {
public:


    DBWorker() : session_(server_name_, port_, user_name_, pass_) {
        session_.sql("USE polar_user");
    };

    static DBWorker &GetInstance() {
        static DBWorker db_worker;
        return db_worker;
    }


    bool UpdateDayActivity(const wjson &exercises_info);

    bool UpdateHealthData(const wjson &user_info);

    mysqlx::SqlResult SQL(const std::string &query);

private:
    const std::string server_name_ = "localhost";
    const int port_ = 33060;
    const std::string user_name_ = "voyko";
    const std::string pass_ = "2004";
    mysqlx::Session session_;
};


