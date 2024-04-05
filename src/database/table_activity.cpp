#include "table_activity.h"

void ActivityTable::Update(const wjson& activities) {
    std::string last_date = LastRecordDate();

    for (size_t i = 0; i < activities.size(); ++i) {
        std::string date = JsonHelper::StringValue(activities[i], "date");
        std::string steps = JsonHelper::IntValue(activities[i], "active-steps");
        std::string total_calories = JsonHelper::IntValue(activities[i], "calories");
        std::string active_calories = JsonHelper::IntValue(activities[i], "active-calories");
        InsertIntoTable(date, steps, total_calories, active_calories);
    }
}
std::string ActivityTable::GenerateTable() {

    boost::format fmt = boost::format(
                            "CREATE TABLE %1%("
                            "date DATE,"
                            "steps INT,"
                            "total_calories INT,"
                            "active_calories INT"
                            ");") %
                        table_name_.data();
    return fmt.str();
}
std::string ActivityTable::GetName() {
    return table_name_.data();
}
