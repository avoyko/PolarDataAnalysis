#include "table_exercises.h"
#include "db.h"

/// im so sorry for being stupid...
std::string ExercisesTable::GenerateTable() {
    boost::format fmt = boost::format(
                            "CREATE TABLE %1%("
                            "date DATE,"
                            "exercise1 VARCHAR(50),"
                            "exercise2 VARCHAR(50),"
                            "exercise3 VARCHAR(50),"
                            "exercise4 VARCHAR(50),"
                            "exercise5 VARCHAR(50),"
                            "exercise6 VARCHAR(50),"
                            "exercise7 VARCHAR(50),"
                            "exercise8 VARCHAR(50),"
                            "exercise9 VARCHAR(50),"
                            "exercise10 VARCHAR(50)"
                            ");") %
                        table_name_;
    return fmt.str();
}

void ExercisesTable::Update(const wjson& exercises) {
    std::string last_date = LastRecordDate();
    std::cout << last_date;
    std::vector<std::string> day_activities;

    for (size_t i = 0; i < exercises.size(); ++i) {
        std::string start_time = JsonHelper::DateValue(exercises[i], "start-time");
        std::string sport_name = JsonHelper::StringValue(exercises[i], "detailed-sport-info");
        if (last_date > start_time) {
            continue;
        }
        if (last_date != start_time) {
            InsertIntoTable(day_activities);
            last_date = start_time;
            day_activities.clear();
            day_activities.push_back(start_time);
        } else {
            day_activities.push_back(sport_name);
        }
    }
}
