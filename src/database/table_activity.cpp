#include "table_activity.h"

void DayActivityTable::Update(const wjson &activities) {
    std::string last_date = LastRecordDate();
    std::vector<std::string> day_activity;

    for (size_t i = 0; i < activities.size(); ++i) {
        std::string date = JsonHelper::StringValue(activities[i], "date");
        std::string steps = JsonHelper::IntValue(activities[i], "active-steps");
        std::string total_calories = JsonHelper::IntValue(activities[i], "calories");
        std::string active_calories = JsonHelper::IntValue(activities[i], "active-calories");
        day_activity = {date, steps, total_calories, active_calories};
        InsertIntoTable(day_activity, columns_);
    }
}