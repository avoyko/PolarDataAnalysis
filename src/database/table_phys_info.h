#pragma once
#include "table_base.h"

class PhysTable : public BaseTable {
public:
    explicit PhysTable() : table_name_("phys_info"), BaseTable(table_name_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();
    void Update(const wjson &heart_samples);

private:
    const std::string table_name_;
};
