#include "db.h"
#include "table_exercises.h"


bool DBWorker::UpdateDayActivity(const wjson &exercises_info) {
    DayExercisesTable exercises_table("day_exercises");
    exercises_table.Update(exercises_info);
}

bool DBWorker::UpdateHealthData(const wjson &user_info) {}

mysqlx::SqlResult DBWorker::SQL(const std::string &query) {
    return session_.sql(query).execute();
}