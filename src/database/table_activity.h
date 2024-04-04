#pragma once

#include "table_base.h"

class ActivityTable : public BaseTable {
public:
    ActivityTable() : BaseTable(table_name_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();

    void Update(const wjson &activities);

    mysqlx::Row Read();

private:
    static constexpr std::string table_name_ = "activity";
};
