#include "table_sleep.h"

void DaySleepTable::Update(const wjson& sleep) {
    std::string last_date = LastRecordDate();
    std::vector<std::string> day_sleep;

    for (size_t i = 0; i < sleep.size(); ++i) {
        std::string date = JsonHelper::StringValue(sleep[i], "date");
        std::string sleep_start_time = JsonHelper::StringValue(sleep[i], "sleep_start_time");
        std::string sleep_end_time = JsonHelper::StringValue(sleep[i], "sleep_end_time");
        std::string light_sleep = JsonHelper::IntValue(sleep[i], "light_sleep");
        std::string deep_sleep = JsonHelper::IntValue(sleep[i], "deep_sleep");
        std::string sleep_score = JsonHelper::IntValue(sleep[i], "sleep_score");
        day_sleep = {date, sleep_start_time, sleep_end_time, light_sleep, deep_sleep, sleep_score};
        InsertIntoTable( day_sleep, columns_);
    }
}
