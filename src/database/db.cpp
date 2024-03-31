#include "db.h"
#include "table_exercises.h"
#include "table_activity.h"
#include "table_phys_info.h"
#include "table_sleep.h"

void DBWorker::UpdateDB(const PolarUser& polar_user) {
    mysqlx::Client client(mysqlx::SessionOption::USER, user_name_, mysqlx::SessionOption::PWD,
                          pass_, mysqlx::SessionOption::HOST, server_name_,
                          mysqlx::SessionOption::PORT, port_);
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

void DBWorker::SetupDB() {
    session_.createSchema(db_name_);
    boost::format fmt =
        boost::format("GRANT ALL ON %1%.* TO '%2%'@'%3%';") % db_name_ % user_name_ % server_name_;
    session_.sql(fmt.str()).execute();
    fmt = boost::format("USE %1%") % db_name_;
    session_.sql(fmt.str()).execute();
}

bool DBWorker::DBExists() {
    mysqlx::Schema schema = session_.getSchema(db_name_, true);
    return schema.existsInDatabase();
}
