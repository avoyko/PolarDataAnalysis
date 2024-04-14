#pragma once

#include "table_base.h"

class SleepTable : public BaseTable {
public:
    SleepTable() : BaseTable(table_name_.data()) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();
    static std::string GetName();
    void Update(const WriteJson &sleep);

private:
    static constexpr frozen::string table_name_ = "sleep";
};
