#pragma once

#include "table_base.h"

class ExercisesTable : public BaseTable {
public:
    ExercisesTable() : table_name_("exercises"), BaseTable(table_name_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();

    void Update(const wjson& exercises);

    mysqlx::Row Read();

private:
    const std::string table_name_;
};



