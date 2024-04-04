#pragma once

#include "table_base.h"

class ExercisesTable : public BaseTable {
public:
    ExercisesTable() : BaseTable(table_name_.data()) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();

    void Update(const wjson& exercises);

    mysqlx::Row Read();

private:
    static constexpr frozen::string table_name_ = "exercise";
};
