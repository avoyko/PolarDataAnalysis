#pragma once
#include "table_base.h"

class DaySleepTable : public BaseTable {
public:
    DaySleepTable() = default;

    explicit DaySleepTable(std::string table_name)
        : BaseTable(std::move(table_name)), table_name_(std::move(table_name)){};

    void Update(const wjson &sleep);

private:
    std::string table_name_;
    const std::vector<std::string> columns_ = {"date",        "sleep_start_time", "sleep_end_time",
                                               "light_sleep", "deep_sleep",       "sleep_score"};
};
