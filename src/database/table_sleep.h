#pragma once
#include "table_base.h"

class DaySleepTable : public BaseTable {
public:
    DaySleepTable() : table_name_("sleep"), BaseTable(table_name_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();
    void Update(const wjson &sleep);

private:
    const std::string table_name_;
};
