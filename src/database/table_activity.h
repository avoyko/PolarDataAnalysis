#pragma once

#include "table_base.h"

class ActivityTable : public BaseTable {
public:
    ActivityTable() : table_name_("activity"), BaseTable(table_name_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();

    void Update(const wjson &activities);

    mysqlx::Row Read();

private:
    const std::string table_name_ ;
};
