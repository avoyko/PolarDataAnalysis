#include "include/db_worker.h"
#include "include/table_exercises.h"
#include "include/table_activity.h"
#include "include/table_phys_info.h"
#include "include/table_sleep.h"
#include <gtest/gtest.h>
#include "../../data_analyser/model_utilities.h"

TEST(TEST_CREATE_DB, get_instance_method_nothrow) {
    ASSERT_NO_THROW(DBWorker::GetInstance());
}

TEST(TEST_CREATE_DB, simple_insertion) {
    DBWorker& db_worker = DBWorker::GetInstance();
    auto activity_table = db_worker.GetTable("exercise");
    auto r = activity_table.insert()
                 .values("2030-02-02", "swim", "swim", "swim", "swim", "swim", "swim", "swim",
                         "swim", "swim", "swim")
                 .execute();
    ASSERT_NO_THROW(activity_table.select("*").execute());
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