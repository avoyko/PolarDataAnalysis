#pragma once

#include "table_base.h"

class ActivityTable : public BaseTable {
public:
    ActivityTable() : BaseTable(table_name_.data()) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();
    static std::string GetName();
    void Update(const WriteJson &activities);

    mysqlx::Row Read();

private:
    static constexpr frozen::string table_name_ = "activity";
};
