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

TEST(TestRetrieveData, Activity) {
    WriteJson activity_info = accesslink.GetActivity(access_token, user_id)[0];
    EXPECT_EQ(NormalizedString(activity_info["id"]), "1234");
    EXPECT_EQ(NormalizedString(activity_info["polar-user"]),
              "https://www.polaraccesslink/v3/users/1");
    EXPECT_EQ(NormalizedString(activity_info["transaction-id"]), "179879");
    EXPECT_EQ(NormalizedString(activity_info["date"]), "2010-12-31");
    EXPECT_EQ(NormalizedString(activity_info["created"]), "2016-04-27T20:11:33.000Z");
    EXPECT_EQ(NormalizedString(activity_info["calories"]), "2329");
    EXPECT_EQ(NormalizedString(activity_info["active-calories"]), "428");
    EXPECT_EQ(NormalizedString(activity_info["duration"]), "PT2H44M");
    EXPECT_EQ(NormalizedString(activity_info["active-steps"]), "250");
}

TEST(TestRetrieveData, Exercise) {
    WriteJson exercise = accesslink.GetExercises(access_token, user_id)[0];
    EXPECT_EQ(NormalizedString(exercise["id"]), "100");
    EXPECT_EQ(NormalizedString(exercise["upload-time"]), "2008-10-13T10:40:0.000Z");
    EXPECT_EQ(NormalizedString(exercise["transaction-id"]), "179879");
    EXPECT_EQ(NormalizedString(exercise["device"]), "Polar M400");
    EXPECT_EQ(NormalizedString(exercise["device-id"]), "1111AAAA");
    EXPECT_EQ(NormalizedString(exercise["start-time"]), "2008-10-13T10:40:02");
    EXPECT_EQ(NormalizedString(exercise["duration"]), "PT2H44M45S");
    EXPECT_EQ(NormalizedString(exercise["calories"]), "530");
    EXPECT_EQ(NormalizedString(exercise["distance"]), "1600.2");
}

TEST(TestRetrieveData, PhysicalInfo) {
    WriteJson physical_info = accesslink.GetPhysicalInfo(access_token, user_id)[0];
    EXPECT_EQ(NormalizedString(physical_info["id"]), "123");
    EXPECT_EQ(NormalizedString(physical_info["created"]), "2016-04-27T20:11:33.000Z");
    EXPECT_EQ(NormalizedString(physical_info["polar-user"]),
              "https://www.polaraccesslink/v3/users/61111666");
    EXPECT_EQ(NormalizedString(physical_info["transaction-id"]), "179879");
    EXPECT_EQ(NormalizedString(physical_info["weight"]), "80");
    EXPECT_EQ(NormalizedString(physical_info["height"]), "180");
    EXPECT_EQ(NormalizedString(physical_info["maximum-heart-rate"]), "160");
    EXPECT_EQ(NormalizedString(physical_info["resting-heart-rate"]), "60");
    EXPECT_EQ(NormalizedString(physical_info["aerobic-threshold"]), "123");
    EXPECT_EQ(NormalizedString(physical_info["anaerobic-threshold"]), "123");
    EXPECT_EQ(NormalizedString(physical_info["vo2-max"]), "12");
}

TEST(TestRetrieveData, Sleep) {
    WriteJson sleep_info = accesslink.GetSleep(access_token, user_id)[0][0];

    EXPECT_EQ(NormalizedString(sleep_info["polar_user"]),
              "https://www.polaraccesslink/v3/users/61111666");
    EXPECT_EQ(NormalizedString(sleep_info["sleep_start_time"]), "2020-01-01T00:39:07+03:00");
    EXPECT_EQ(NormalizedString(sleep_info["sleep_end_time"]), "2020-01-01T09:19:37+03:00");
    EXPECT_EQ(NormalizedString(sleep_info["light_sleep"]), "1000");
    EXPECT_EQ(NormalizedString(sleep_info["deep_sleep"]), "1000");
    EXPECT_EQ(NormalizedString(sleep_info["sleep_score"]), "80");
}

TEST(TestRetrieveData, UserInfo) {
    WriteJson user_info = accesslink.GetUserdata(access_token, user_id);
    EXPECT_EQ(NormalizedString(user_info["polar-user-id"]), "2278512");
    EXPECT_EQ(NormalizedString(user_info["member-id"]), "i09u9ujj");
    EXPECT_EQ(NormalizedString(user_info["registration-date"]), "2011-10-14T12:50:37.000Z");
    EXPECT_EQ(NormalizedString(user_info["first-name"]), "Eka");
    EXPECT_EQ(NormalizedString(user_info["last-name"]), "Toka");
    EXPECT_EQ(NormalizedString(user_info["birthdate"]), "1985-09-06");
    EXPECT_EQ(NormalizedString(user_info["gender"]), "MALE");
    EXPECT_EQ(NormalizedString(user_info["weight"]), "66");
    EXPECT_EQ(NormalizedString(user_info["height"]), "170");
    ASSERT_NO_THROW(1 + 1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}