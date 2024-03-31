#include "db.h"
#include "table_exercises.h"
#include "table_activity.h"
#include "table_phys_info.h"
#include "table_sleep.h"

void DBWorker::UpdateDB(const PolarUser& polar_user) {
    ExercisesTable exercises_table;
    ActivityTable activity_table;
    PhysTable phys_table;
    DaySleepTable sleep_table;

    exercises_table.Update(polar_user.exercises_info);
    activity_table.Update(polar_user.activity_info);
    phys_table.Update(polar_user.physical_info);
    sleep_table.Update(polar_user.sleep_info);
}

mysqlx::SqlResult DBWorker::SQL(const std::string& query) {
    return session_.sql(query).execute();
}
