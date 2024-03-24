#include "db.h"
#include "table_exercises.h"


bool DBWorker::UpdateDB(const std::string &table_name, const wjson &info) {
    DayExercisesTable exercises_table(table_name);
    exercises_table.Update(info);
}


mysqlx::SqlResult DBWorker::SQL(const std::string &query) {
    return session_.sql(query).execute();
}