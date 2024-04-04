#include "db.h"
#include "table_exercises.h"
#include "table_activity.h"
#include "table_phys_info.h"
#include "table_sleep.h"
#include <gtest/gtest.h>

TEST(TEST_CREATE_DB, get_instance_method_nothrow) {
    ASSERT_NO_THROW(DBWorker::GetInstance());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}