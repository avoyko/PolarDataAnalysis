#include "db.h"
#include "table_exercises.h"
#include "table_activity.h"
#include "table_phys_info.h"
#include "table_sleep.h"
#include <gtest/gtest.h>
#include "../data_analyser/model_utilities.h"

TEST(TEST_CREATE_DB, get_instance_method_nothrow) {
    ASSERT_NO_THROW(DBWorker::GetInstance());
}

TEST(TEST_CREATE_DB, simple_insertion) {
    DBWorker& db_worker = DBWorker::GetInstance();
    auto activity_table = db_worker.GetTable("exercise");
    auto r = activity_table.insert()
                 .values("2024-04-05", "swim", "swim", "swim", "swim", "swim", "swim", "swim",
                         "swim", "swim", "swim")
                 .execute();
    ASSERT_NO_THROW(activity_table.select("*").execute());
    mysqlx::Row row = activity_table.select("*").execute().fetchOne();
    std::string date = mysqlx::get_string_date(row);
}

TEST(TEST_CREATE_DB, convert_to_csv) {
    DBWorker& db_worker = DBWorker::GetInstance();
    ASSERT_NO_THROW(CSVHelpers::ConvertToCSV());
}

TEST(TEST_CREATE_DB, delete_csv) {
    ASSERT_NO_THROW(CSVHelpers::DeleteCSV());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}