#pragma once

#include <mysqlx/xdevapi.h>
#include <iostream>
#include "utilities.h"
#include "../json_helpers/execises.h"


class DBWorker {
public:

    DBWorker(const std::string &server_name, const int port, const std::string &user_name, const std::string &pass)
            : session_(server_name, port, user_name, pass) {
        session_.sql("use polar_user");
    };


    bool UpdateDayActivity(const wjson &exercises) {
        for (size_t i = 0; i < exercises.size(); ++i) {
            auto ex_info = JsonExerciseInfo(exercises[i]);
            auto time = ex_info.HeartRate();
            auto sport = ex_info.SportName();

        }
        const int ind = 0;
        std::string us = exercises.dump();
        std::cout << us[0];
        return true;
    }

    bool UpdateHealthData(ParsedResponse &user_info) {

    }

private:


    mysqlx::Session session_;
};



