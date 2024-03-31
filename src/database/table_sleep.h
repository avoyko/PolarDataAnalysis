#pragma once
#include "table_base.h"

class DaySleepTable : public BaseTable<6> {
public:
    DaySleepTable() : BaseTable<6>(table_name_, columns_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    static std::string GenerateTable();
    void Update(const wjson &sleep);

private:
    static constexpr std::string table_name_ = "sleep";
    static constexpr std::array<std::string, 6> columns_ = {
        "date", "sleep_start", "sleep_end", "light_sleep", "deep_sleep", "sleep_score"};
};
