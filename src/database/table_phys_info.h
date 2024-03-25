#pragma once
#include "table_base.h"

class DayPhysTable : public BaseTable {
public:
    DayPhysTable() = default;

    explicit DayPhysTable(std::string table_name)
        : BaseTable(std::move(table_name)), table_name_(std::move(table_name)){};

    void Update(const wjson &heart_samples);

private:
    std::string table_name_;
    const std::vector<std::string> columns_ = {"date",
                                               "weight",
                                               "height",
                                               "max_heart_rate",
                                               "resting_heart_rate",
                                               "aerobic-threshold",
                                               "anaerobic-threshold",
                                               "vo2-max"};
};
