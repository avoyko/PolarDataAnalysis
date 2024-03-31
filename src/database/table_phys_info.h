#pragma once
#include "table_base.h"

class PhysTable : public BaseTable<8> {
public:
    explicit PhysTable() : BaseTable<8>(table_name_, columns_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    static std::string GenerateTable();
    void Update(const wjson &heart_samples);

private:
    static constexpr std::string table_name_ = "phys_info";
    static constexpr std::array<std::string, 8> columns_ = {
        "date", "weight", "height", "max_hr", "resting_hr", "ae_t", "an_t", "vo2_max"};
};
