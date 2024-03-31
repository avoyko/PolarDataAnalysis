#pragma once

#include "../utilities.h"
#include "db.h"

template <size_t Col>
class BaseTable {
public:
    BaseTable() = default;

    explicit BaseTable(std::string table_name, std::array<std::string, Col> columns)
        : table_name_(std::move(table_name)), columns_(std::move(columns)){};


    void Create(const std::string& sql_query){
        DBWorker& db_worker = DBWorker::GetInstance();
        db_worker.SQL(sql_query);
    }

    bool CheckExistence() {
        DBWorker &db_worker = DBWorker::GetInstance();
        boost::format fmt = boost::format("SHOW TABLES LIKE \"%1%\";") % table_name_;
        mysqlx::SqlResult records = db_worker.SQL(fmt.str());
        auto result = records.fetchOne();
        std::cout << result;
        return result != 0;
    };

    std::string LastRecordDate() {
        DBWorker &db_worker = DBWorker::GetInstance();
        boost::format fmt =
            boost::format("SELECT * FROM %1% ORDER BY date DESC LIMIT 1;") % table_name_;
        mysqlx::SqlResult records = db_worker.SQL(fmt.str());
        return mysqlx::get_string_date(records.fetchOne());
    };

    void InsertIntoTable(const std::vector<std::string> &values) {
        DBWorker &db_worker = DBWorker::GetInstance();
        //        while (columns_.size() > values.size()) {
        //            columns_.pop_back();
        //        }
        boost::format fmt = boost::format("INSERT INTO %1%(%2%) VALUES(%3%);") % table_name_ %
                            StringHelper::Join(columns_) % StringHelper::Join(values);
        db_worker.SQL(fmt.str());
    };

    void Delete() {
        DBWorker &db_worker = DBWorker::GetInstance();
        boost::format fmt = boost::format("DROP TABLE %1%;") % table_name_;
        db_worker.SQL(fmt.str());
    }

private:
    const std::string table_name_;
    const std::array<std::string, Col> columns_;
};
