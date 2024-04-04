#pragma once

#include "table_base.h"

class PhysTable : public BaseTable {
public:
    explicit PhysTable() : BaseTable(table_name_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();
    void Update(const wjson &heart_samples);

private:
    static constexpr std::string table_name_ = "phys_info";
};
