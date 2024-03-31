#pragma once

#include "table_base.h"

class ActivityTable : public BaseTable<4> {
public:
    ActivityTable() : BaseTable<4>(table_name_, columns_) {
        if (!CheckExistence()) {
            Create(GenerateTable());
        }
    };

    static std::string GenerateTable();

    void Update(const wjson &activities);

    mysqlx::Row Read();

private:
    static constexpr std::string table_name_ = "activity";
    static constexpr std::array<std::string, 4> columns_ = {"date", "steps", "total_calories",
                                                            "active_calories"};
};