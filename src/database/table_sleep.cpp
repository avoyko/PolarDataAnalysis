#include "table_sleep.h"

void SleepTable::Update(const WriteJson& sleep) {
    std::string last_date = LastRecordDate();

    for (size_t i = 0; i < sleep.size(); ++i) {
        std::string date = JsonHelper::DateValue(sleep[i], "date");
        std::string sleep_start_time = JsonHelper::StringValue(sleep[i], "sleep_start_time");
        std::string sleep_end_time = JsonHelper::StringValue(sleep[i], "sleep_end_time");
        std::string light_sleep = JsonHelper::IntValue(sleep[i], "light_sleep");
        std::string deep_sleep = JsonHelper::IntValue(sleep[i], "deep_sleep");
        std::string sleep_score = JsonHelper::IntValue(sleep[i], "sleep_score");
        if (date != mysqlx::DEFAULT_DATE && date > last_date) {
            InsertIntoTable(date, sleep_start_time, sleep_end_time, light_sleep, deep_sleep,
                            sleep_score);
        }
    }
}
std::string SleepTable::GenerateTable() {
    boost::format fmt = boost::format(
                            "CREATE TABLE %1%("
                            "date DATE,"
                            "sleep_start VARCHAR(50),"
                            "sleep_end VARCHAR(50),"
                            "light_sleep INT,"
                            "deep_sleep INT,"
                            "sleep_score INT"
                            ");") %
                        table_name_.data();
    return fmt.str();
}
std::string SleepTable::GetName() {
    return table_name_.data();
}
