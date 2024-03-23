#include "table_exercises.h"

void DayExercisesTable::Update(const wjson &exercises) {
    std::string last_date = LastRecordDate(table_name_);
    std::vector<std::string> day_activities;

    for (size_t i = 0; i < exercises.size(); ++i) {
        JsonExerciseInfo exercise_info(exercises[i]);
        std::string start_time = exercise_info.StartTime();
        std::string sport_name = exercise_info.SportName();
        if (last_date > start_time) {
            ///we dont't want old records
            continue;
        }
        if (last_date != start_time) {
            InsertIntoTable(table_name_, day_activities, columns);
            last_date = start_time;
            day_activities.clear();
            day_activities.push_back(start_time);
        } else {
            day_activities.push_back(sport_name);
        }

    }
}