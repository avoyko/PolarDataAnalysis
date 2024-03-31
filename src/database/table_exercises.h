#pragma once

#include "table_base.h"

static constexpr size_t col_num = 11;

class ExercisesTable : public BaseTable<col_num> {
public:
    ExercisesTable() : BaseTable(table_name_, columns_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    static std::string GenerateTable();

    void Update(const wjson &exercises);

    mysqlx::Row Read();

private:
    static constexpr std::string table_name_ = "exercises";
    static constexpr std::array<std::string, col_num> columns_ = {
        "date",      "exercise1", "exercise2", "exercise3", "exercise4", "exercise5",
        "exercise6", "exercise7", "exercise8", "exercise9", "exercise10"};
    ;
};
