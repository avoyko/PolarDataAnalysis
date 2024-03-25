#pragma once

#include "table_base.h"


class DayExercisesTable : public BaseTable {
public:

    DayExercisesTable() = default;

    explicit DayExercisesTable(std::string table_name) : BaseTable(table_name),
                                                         table_name_(std::move(table_name)) {};

    void Update(const wjson &exercises);

private:

    std::string table_name_;
    const std::vector<std::string> columns = {"date", "exercise1", "exercise2", "exercise3", "exercise4",
                                              "exercise5", "exercise6", "exercise7", "exercise8", "exercise9",
                                              "exercise10"};

};