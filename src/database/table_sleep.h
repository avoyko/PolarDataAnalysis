#pragma once
#include "table_base.h"

class DaySleepTable : public BaseTable {
public:
    DaySleepTable() : BaseTable(table_name_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();
    void Update(const wjson &sleep);

private:
    static constexpr std::string table_name_ = "sleep";
};
