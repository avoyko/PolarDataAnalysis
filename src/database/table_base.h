#pragma once

#include "../utilities.h"
#include "db.h"

class BaseTable {
public:
    BaseTable() = default;

    explicit BaseTable(std::string table_name) : table_name_(std::move(table_name)){};

    void Create(const std::string &sql_query) {
        DBWorker &db_worker = DBWorker::GetInstance();
        db_worker.SQL(sql_query);
    }

    bool CheckExistence() {
        DBWorker &db_worker = DBWorker::GetInstance();
        return db_worker.FindTable(table_name_);
    };

    std::string LastRecordDate() {
        DBWorker &db_worker = DBWorker::GetInstance();
        mysqlx::Table table = db_worker.GetTable(table_name_);
        mysqlx::RowResult rowResult = table.select("*").orderBy("date DESC").limit(1).execute();
        return mysqlx::get_string_date(rowResult.fetchOne());
    };

    template <typename... Args>
    void InsertIntoTable(Args &&...args) {
        DBWorker &db_worker = DBWorker::GetInstance();
        mysqlx::Table table = db_worker.GetTable(table_name_);
        table.insert().values(args...);
    };

    void Delete() {
        DBWorker &db_worker = DBWorker::GetInstance();
        boost::format fmt = boost::format("DROP TABLE %1%;") % table_name_;
        db_worker.SQL(fmt.str());
    }

private:
    const std::string table_name_;
};
