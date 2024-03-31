#include "table_base.h"
#include "db.h"

//
//
//std::string BaseTable::LastRecordDate() {
//    DBWorker &db_worker = DBWorker::GetInstance();
//    boost::format fmt =
//        boost::format("SELECT * FROM %1% ORDER BY date DESC LIMIT 1;") % table_name_;
//    mysqlx::SqlResult records = db_worker.SQL(fmt.str());
//    return mysqlx::get_string_date(records.fetchOne());
//}

//void BaseTable::InsertIntoTable(const std::vector<std::string> &values) {
//
//    DBWorker &db_worker = DBWorker::GetInstance();
//    while (column_names.size() > values.size()) {
//        column_names.pop_back();
//    }
//    boost::format fmt = boost::format("INSERT INTO %1%(%2%) VALUES(%3%);") % table_name_ %
//                        Join(column_names) % Join(values);
//    db_worker.SQL(fmt.str());
//}

//bool BaseTable::CheckExistence() {
//    DBWorker &db_worker = DBWorker::GetInstance();
//    boost::format fmt = boost::format("SHOW TABLES LIKE %1%;") % table_name_;
//    mysqlx::SqlResult records = db_worker.SQL(fmt.str());
//    return records.fetchOne().isNull();
//}
