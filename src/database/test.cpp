#include "db.h"
#include "table_exercises.h"
#include "table_activity.h"
#include "table_phys_info.h"
#include "table_sleep.h"
#include <gtest/gtest.h>

TEST(TEST_CREATE_DB, db_first){
    mysqlx::Session session("localhost", 33060, "voyko", "2004");
    try {
        session.sql("DROP DATABASE polar_user;").execute();
        session.sql("DROP USER 'voyko'@'localhost';").execute();
    } catch(...){};

    ASSERT_NO_THROW(DBWorker::GetInstance());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}