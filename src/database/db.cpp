#include "db.h"
#include "table_exercises.h"
#include "table_activity.h"
#include "table_phys_info.h"
#include "table_sleep.h"

static bool db_can_be_used = false;

DBWorker::DBWorker()
    : session(server_name_.data(), port_, user_name_.data(), pass_.data(), db_name_.data()){};

DBWorker &DBWorker::GetInstance() {
    if (!db_can_be_used) {
        RunSetup();
        db_can_be_used = true;
    }
    static DBWorker db_worker;
    return db_worker;
}

void DBWorker::UpdateDB(const PolarUser &polar_user) {
    ExercisesTable exercises_table;
    ActivityTable activity_table;
    PhysTable phys_table;
    SleepTable sleep_table;

    exercises_table.Update(polar_user.exercises_json);
    activity_table.Update(polar_user.activity_json);
    phys_table.Update(polar_user.physical_json);
    sleep_table.Update(polar_user.sleep_json);
}

mysqlx::SqlResult DBWorker::SQL(const std::string &query) {
    return session.sql(query).execute();
}

mysqlx::Schema DBWorker::GetDB() {
    return session.getSchema(db_name_.data());
}

mysqlx::Table DBWorker::GetTable(const std::string &table_name) {
    return GetDB().getTable(table_name);
}

bool DBWorker::FindTable(const std::string &table_name) {
    mysqlx::Schema schema = session.getSchema(db_name_.data(), true);
    return schema.getTable(table_name).existsInDatabase();
}

mysqlx::SqlResult DBWorker::JoinAllTables() {
    auto table_list = session.getDefaultSchema().getTableNames();
    boost::format fmt = boost::format(
                            "SELECT * FROM %1% "
                            "NATURAL LEFT JOIN %2% "
                            "NATURAL LEFT JOIN %3% "
                            "NATURAL LEFT JOIN %4%;") %
                        ActivityTable::GetName() % ExercisesTable::GetName() %
                        PhysTable::GetName() % SleepTable::GetName();
    return SQL(fmt.str());
}

mysqlx::SqlResult DBWorker::GetTableColumns(const std::string &table_name) {
    boost::format fmt =
        boost::format(
            "SELECT GROUP_CONCAT(COLUMN_NAME) FROM INFORMATION_SCHEMA.COLUMNS WHERE "
            "TABLE_NAME = \'%1%\' "
            "AND COLUMN_NAME!='date';") %
        table_name;
    return SQL(fmt.str());
}

/// THIS IS THE PLACE WHERE DIRTY STUFF HAPPENS

void DBWorker::RunSetup() {
    try {
        mysqlx::Session test_session(server_name_.data(), port_, user_name_.data(), pass_.data(),
                                     db_name_.data());
    } catch (...) {
        std::string existing_user;
        std::string pwd;
        std::cout << "TYPE YOUR CURRENT EXISTING MYSQL-USER LOGIN:\n";
        std::cin >> existing_user;
        std::cout << "PASSWORD:\n";
        std::cin >> pwd;
        mysqlx::Session setup_session(server_name_.data(), port_, existing_user, pwd);
        if (!FindDB(setup_session)) {
            SetupDB(setup_session);
        }
        if (!FindUser(setup_session)) {
            SetupUser(setup_session);
        }
    }
}

void DBWorker::SetupDB(mysqlx::Session &temp_session) {
    temp_session.createSchema(db_name_.data());
}

bool DBWorker::FindDB(mysqlx::Session &temp_session) {
    mysqlx::Schema schema = temp_session.getSchema(db_name_.data());
    return schema.existsInDatabase();
}

void DBWorker::SetupUser(mysqlx::Session &temp_session) {
    boost::format fmt = boost::format(R"(CREATE USER '%1%'@'%2%' IDENTIFIED BY '%3%')") %
                        user_name_.data() % server_name_.data() % pass_.data();
    temp_session.sql(fmt.str()).execute();
    fmt = boost::format(R"(GRANT ALL PRIVILEGES ON *.* TO '%1%'@'%2%';)") % user_name_.data() %
          server_name_.data();
    temp_session.sql(fmt.str()).execute();
}

bool DBWorker::FindUser(mysqlx::Session &temp_session) {
    mysqlx::Table table = temp_session.getSchema("mysql").getTable("user");
    boost::format fmt = boost::format("user == \'%1%\'") % user_name_.data();
    auto result = table.select("1").where(fmt.str()).execute();
    return result.fetchOne() == 1;
}
