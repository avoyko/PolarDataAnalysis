#pragma once

#include "db.h"

class BaseTable {
public:
    BaseTable() = default;

    explicit BaseTable(std::string table_name) : table_name_(std::move(table_name)){};

    void Create(const std::string &sql_query);

    bool CheckExistence();

    std::string LastRecordDate();

    template <typename... Args>
    void InsertIntoTable(Args &&...args) {
        DBWorker &db_worker = DBWorker::GetInstance();
        mysqlx::Table table = db_worker.GetTable(table_name_);
        table.insert().values(args...);
    };

    void Delete();

private:
    const std::string table_name_;
};
