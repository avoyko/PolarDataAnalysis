#include "table_exercises.h"

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
                        table_name_.data();
    return fmt.str();
}

void ExercisesTable::Update(const WriteJson& exercises) {
    std::string last_date = LastRecordDate();
    std::vector<std::string> day_exercises = JsonHelper::GetDefaultExercises();
    size_t index = 0;
    bool can_fill_row = false;

    for (size_t i = 0; i < exercises.size(); ++i) {
        std::string start_time = JsonHelper::DateValue(exercises[i], "start-time");
        std::string sport_name = JsonHelper::StringValue(exercises[i], "detailed-sport-info");
        if (last_date < start_time) {
            InsertIntoTable(day_exercises[0], day_exercises[1], day_exercises[2], day_exercises[3],
                            day_exercises[4], day_exercises[5], day_exercises[6], day_exercises[7],
                            day_exercises[8], day_exercises[9], day_exercises[10]);
            last_date = start_time;
            day_exercises = JsonHelper::GetDefaultExercises();
            index = 0;
            can_fill_row = true;
            day_exercises[index++] = start_time;
        }
        if (can_fill_row) {
            day_exercises[index++] = sport_name;
        }
    }
    InsertIntoTable(day_exercises[0], day_exercises[1], day_exercises[2], day_exercises[3],
                    day_exercises[4], day_exercises[5], day_exercises[6], day_exercises[7],
                    day_exercises[8], day_exercises[9], day_exercises[10]);
}

std::string ExercisesTable::GetName() {
    return table_name_.data();
}
