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
    return session.sql(query).execute();
}

void DBWorker::SetupDB() {
    session.createSchema(db_name_);
    boost::format fmt =
        boost::format("GRANT ALL ON %1%.* TO '%2%'@'%3%';") % db_name_ % user_name_ % server_name_;
    session.sql(fmt.str()).execute();
    fmt = boost::format("USE %1%") % db_name_;
    session.sql(fmt.str()).execute();
}

bool DBWorker::FindDB() {
    mysqlx::Schema schema = session.getSchema(db_name_, true);
    return schema.existsInDatabase();
}
bool DBWorker::FindTable(const std::string& table_name) {
    mysqlx::Schema schema = session.getSchema(db_name_, true);
    return schema.getTable(table_name, true).existsInDatabase();
}
mysqlx::Schema DBWorker::GetDB() {
    return session.getSchema(db_name_);
}
mysqlx::Table DBWorker::GetTable(const std::string& table_name) {
    return GetDB().getTable(table_name);
}
