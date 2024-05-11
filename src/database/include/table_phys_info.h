#pragma once

#include "table_base.h"

class PhysTable : public BaseTable {
public:
    explicit PhysTable() : BaseTable(table_name_.data()) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    std::string GenerateTable();
    static std::string GetName();
    void Update(const WriteJson &phys);

private:
    static constexpr frozen::string table_name_ = "phys_info";
};
