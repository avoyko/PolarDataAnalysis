#include "table_base.h"
#include "db.h"

std::string Join(const std::vector<std::string> &strings, const std::string &delim = ",") {
    return std::accumulate(strings.begin(), strings.end(), std::string(),
                           [&delim](const std::string &x, const std::string &y) {
                               return x.empty() ? y : x + delim + y;
                           });
}


std::string BaseTable::LastRecordDate() {
    DBWorker &db_worker = DBWorker::GetInstance();
   // boost::format fmt = boost::format("") % table_name_;
    mysqlx::SqlResult records = db_worker.SQL("SELECT * FROM day_exercises;");
    mysqlx::Row last_row = records.fetchOne();
    std::cout << last_row[0];
    std::cout<<last_row<<'\n';
    return last_row[0].get<std::string>();
}

bool BaseTable::InsertIntoTable(const std::vector<std::string> &values,
                                std::vector<std::string> column_names) {

    DBWorker &db_worker = DBWorker::GetInstance();
    while (column_names.size() > values.size()) {
        column_names.pop_back();
    }
    boost::format fmt =
            boost::format("INSERT INTO %1%(%2%) VALUES(%3%);") % table_name_ % Join(column_names) %
            Join(values);
    db_worker.SQL(fmt.str());
    return true;
}

