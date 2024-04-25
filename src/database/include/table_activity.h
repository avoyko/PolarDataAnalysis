#pragma once

#include "table_base.h"

class ActivityTable : public BaseTable {
public:
    ActivityTable();

    std::string GenerateTable();

    static std::string GetName();

    void Update(const WriteJson &activities);

private:
    static constexpr frozen::string table_name_ = "activity";
};
