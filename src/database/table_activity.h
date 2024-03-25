#pragma once


#include "table_base.h"



class DayActivityTable : public BaseTable {
public:
    DayActivityTable() = default;

    explicit DayActivityTable(std::string table_name) : BaseTable(std::move(table_name)),
                                                       table_name_(std::move(table_name)) {};

    void Update(const wjson &activities);

private:

    std::string table_name_;
    const std::vector<std::string> columns_ = {"date", "steps", "total_calories",
                                              "active_calories"};

};