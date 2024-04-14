#include "../include/table_base.h"

void BaseTable::Create(const std::string &sql_query) {
    DBWorker &db_worker = DBWorker::GetInstance();
    db_worker.SQL(sql_query);
}

std::string BaseTable::LastRecordDate() {
    DBWorker &db_worker = DBWorker::GetInstance();
    mysqlx::Table table = db_worker.GetTable(table_name_);
    mysqlx::RowResult rowResult = table.select("*").orderBy("date DESC").limit(1).execute();
    try {
        return mysqlx::get_string_date(rowResult.fetchOne());
    } catch (...) {
        return mysqlx::DEFAULT_DATE;
    }
}

void BaseTable::Delete() {
    DBWorker &db_worker = DBWorker::GetInstance();
    boost::format fmt = boost::format("DROP TABLE %1%;") % table_name_;
    db_worker.SQL(fmt.str());
}

bool BaseTable::CheckExistence() {
    DBWorker &db_worker = DBWorker::GetInstance();
    return db_worker.FindTable(table_name_);
}
