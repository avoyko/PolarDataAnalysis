#include "../include/db_worker.h"
#include "../include/table_exercises.h"
#include "../include/table_activity.h"
#include "../include/table_phys_info.h"
#include "../include/table_sleep.h"
#include "../../model/model_utilities.h"
#include "utilities.h"
#include <gtest/gtest.h>

TEST(TEST_CREATE_DB, get_instance_method_nothrow) {
    ASSERT_NO_THROW(DBWorker::GetInstance());
}

TEST(TEST_INSERT_DB, exercise_insertion) {
    ActivityTable activityTable;
    ASSERT_NO_THROW(activityTable.InsertIntoTable("2030-02-02", "2329", "428", "250"));
}

TEST(TEST_INSERT_DB, activity_insertion) {
    ExercisesTable exercisesTable;
    ASSERT_NO_THROW(exercisesTable.InsertIntoTable("2030-02-02", "swim", "swim", "swim", "swim",
                                                   "swim", "swim", "swim", "swim", "swim", "swim"));
}

TEST(TEST_INSERT_DB, physical_info_insertion) {
    PhysTable physTable;
    ASSERT_NO_THROW(
        physTable.InsertIntoTable("2030-02-02", "80", "180", "160", "60", "123", "123", "12"));
}

TEST(TEST_INSERT_DB, sleep_insertion) {
    SleepTable sleepTable;
    ASSERT_NO_THROW(sleepTable.InsertIntoTable("2030-02-02", "2020-01-01T00:39:07+03:00",
                                               "2020-01-01T09:19:37+03:00", "1000", "1000", "80"));
}

TEST(TEST_UPDATE_DB, activity_update) {
    ActivityTable activityTable;
    ASSERT_NO_THROW(activityTable.Update(JsonExamples::activity));
}

TEST(TEST_UPDATE_DB, exercise_update) {
    ExercisesTable exercisesTable;
    ASSERT_NO_THROW(exercisesTable.Update(JsonExamples::exercises));
}

TEST(TEST_UPDATE_DB, phys_info_update) {
    PhysTable physTable;
    ASSERT_NO_THROW(physTable.Update(JsonExamples::physical_info));
}

TEST(TEST_UPDATE_DB, sleep_update) {
    SleepTable sleepTable;
    ASSERT_NO_THROW(sleepTable.Update(JsonExamples::sleep));
}

TEST(TEST_CONVERT_DB, convert_to_csv) {
    DBWorker &db_worker = DBWorker::GetInstance();
    ASSERT_NO_THROW(CSVHelpers::ConvertToCSV());
}

TEST(TEST_CONVERT_DB, delete_csv) {
    ASSERT_NO_THROW(CSVHelpers::DeleteCSV());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}