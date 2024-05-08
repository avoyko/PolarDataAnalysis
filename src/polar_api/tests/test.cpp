#include <gtest/gtest.h>
#include "crow/app.h"
#include "../include/accesslink.h"
#include <yaml-cpp/yaml.h>

namespace Client {
const std::string CLIENT_ID = "bd3a77a4-0edc-44e5-81a5-309644f0fc9a";
const std::string CLIENT_SECRET = "b854a0ca-2a74-4dde-9196-0c0b1b63110e";
const std::string REDIRECT_URI = "http://localhost:8080/oauth2_callback";
const std::string DATA_URI = "http://localhost:8080/data";

};  // namespace Client

static AccessLink accesslink(Client::CLIENT_ID, Client::CLIENT_SECRET, Client::REDIRECT_URI);

const auto access_token = "access_token";
const auto user_id = "61111666";

inline std::string NormalizedString(const WriteJson& s) {
    auto st = s.dump();
    return st.substr(1, st.size() - 2);
}

TEST(TestTransactions, ActivityTransaction) {
    //    DailyActivity
    //    accesslink.GetExercises() ASSERT_NO_THROW(1 + 1);
}

TEST(TestTransactions, ExerciseTransaction) {
    ASSERT_NO_THROW(1 + 1);
}

TEST(TestTransactions, PhysTransaction) {
    ASSERT_NO_THROW(1 + 1);
}

 TEST(TestRetrieveData, Activity) {
     WriteJson activity_info = accesslink.GetActivity(access_token, user_id);

 }

//TEST(TestRetrieveData, Exercise) {
//    WriteJson exercise = accesslink.GetExercises(access_token, user_id)[0];
//    EXPECT_EQ(NormalizedString(exercise["id"]), "100");
//    EXPECT_EQ(NormalizedString(exercise["upload-time"]), "2008-10-13T10:40:0.000Z");
//    EXPECT_EQ(NormalizedString(exercise["transaction-id"]), "179879");
//    EXPECT_EQ(NormalizedString(exercise["device"]), "Polar M400");
//    EXPECT_EQ(NormalizedString(exercise["device-id"]), "1111AAAA");
//    EXPECT_EQ(NormalizedString(exercise["start-time"]), "2008-10-13T10:40:02");
//    EXPECT_EQ(NormalizedString(exercise["duration"]), "PT2H44M45S");
//    EXPECT_EQ(NormalizedString(exercise["calories"]), "530");
//    EXPECT_EQ(NormalizedString(exercise["distance"]), "1600.2");
//}

 id = "123"
     transaction_id = 179879
     created = "2016-04-27T20:11:33.000Z"
     polar_user = "https://www.polaraccesslink/v3/users/1"
     weight = "80"
     height = "180"
     maximum_heart_rate = "160"
     resting_heart_rate = "60"
     aerobic_threshold = "123"
     anaerobic_threshold = "123"
     vo2_max = "12"
     weight_source = "SOURCE_MEASURED"

TEST(TestRetrieveData, PhysicalInfo) {
    WriteJson exercise = accesslink.GetPhysicalInfo(access_token, user_id)[0];
    EXPECT_EQ(NormalizedString(exercise["id"]), "123");
    EXPECT_EQ(NormalizedString(exercise["created"]), "2016-04-27T20:11:33.000Z");
    EXPECT_EQ(NormalizedString(exercise["polar-user"]),
              "https://www.polaraccesslink/v3/users/61111666");
    EXPECT_EQ(NormalizedString(exercise["transaction-id"]), "179879");
    EXPECT_EQ(NormalizedString(exercise["weight"]), "Polar M400");
    EXPECT_EQ(NormalizedString(exercise["height"]), "1111AAAA");
    EXPECT_EQ(NormalizedString(exercise["maximum-heart-rate"]), "2008-10-13T10:40:02");
    EXPECT_EQ(NormalizedString(exercise["resting-heart-rate"]), "180");
    EXPECT_EQ(NormalizedString(exercise["aerobic-threshol"]), "PT2H44M45S");
    EXPECT_EQ(NormalizedString(exercise["anaerobic-threshol"]), "530");
    EXPECT_EQ(NormalizedString(exercise["vo2-max"]), "1600.2");
    EXPECT_EQ(NormalizedString(exercise["weight-source"]), "SOURCE_MEASURED");
}

 TEST(TestRetrieveData, Sleep) {
     WriteJson sleep_info = accesslink.GetSleep(access_token, user_id);
     ASSERT_NO_THROW(1 + 1);
 }

 TEST(TestRetrieveData, UserInfo) {
     WriteJson user_info = accesslink.GetUserdata(access_token, user_id);
     ASSERT_NO_THROW(1 + 1);
 }

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}