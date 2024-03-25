#pragma once

#include "../utilities.h"

class BaseTable {
public:
    BaseTable() = default;

    explicit BaseTable(std::string table_name) : table_name_(std::move(table_name)) {
    }

    std::string LastRecordDate();

    bool InsertIntoTable(const std::vector<std::string> &values,
                         std::vector<std::string> column_names);

private:
    std::string table_name_;
};
