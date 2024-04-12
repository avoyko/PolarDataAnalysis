#pragma once

#include "db_worker.h"

class BaseTable {
public:
    BaseTable() = default;
    ~BaseTable() = default;

    explicit BaseTable(std::string table_name) : table_name_(std::move(table_name)){};

    void Create(const std::string &sql_query);

    bool CheckExistence();

    std::string LastRecordDate();

    template <typename... Args>
    void InsertIntoTable(Args &&...args) {
        if (mysqlx::IsValidRow(std::forward<Args>(args)...)) {
            return;
        }
        DBWorker &db_worker = DBWorker::GetInstance();
        mysqlx::Table table = db_worker.GetTable(table_name_);
        table.insert().values(std::forward<Args>(args)...).execute();
    };

    void Delete();

private:
    const std::string table_name_;
};
