#include <gtest/gtest.h>
#include "crow/app.h"

TEST(TEST_CREATE_DB, get_instance_method_nothrow) {
    ASSERT_NO_THROW(1+1);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}