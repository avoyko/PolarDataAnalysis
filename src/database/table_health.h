#pragma once


#include "table_base.h"


class HealthDataTable : public BaseTable {
public:

    HealthDataTable() = default;

    explicit HealthDataTable(std::string table_name) : BaseTable(std::move(table_name)),
                                                       table_name_(std::move(table_name)) {};

    void Update(const wjson &exercises);

private:

    std::string table_name_;
    const std::vector<std::string> columns = {"date", "total_steps", "total_calories",
                                              "weight", "height", "max_heart_rate", "min_heart_rate", "avg_heart_rate",
                                              "light_sleep", "deep_sleep"};

};