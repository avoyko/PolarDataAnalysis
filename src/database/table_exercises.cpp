#include "table_exercises.h"




void DayExercisesTable::Update(const wjson &exercises) {
    std::string last_date = LastRecordDate();
    std::vector<std::string> day_activities;

    for (size_t i = 0; i < exercises.size(); ++i) {
        std::string start_time = JsonHelper::StringValue(exercises[i], "start-time");
        std::string sport_name = JsonHelper::StringValue(exercises[i], "detailed-sport-info");
        if (last_date > start_time) {
            /// we dont't want old records
            continue;
        }
        if (last_date != start_time) {
            InsertIntoTable(day_activities, columns);
            last_date = start_time;
            day_activities.clear();
            day_activities.push_back(start_time);
        } else {
            day_activities.push_back(sport_name);
        }
    }
}