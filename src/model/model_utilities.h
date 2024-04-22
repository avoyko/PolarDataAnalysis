#pragma once

#include <fstream>
#include "../database/include/db_worker.h"
#include "../database/include/table_activity.h"
#include "../database/include/table_base.h"
#include "../database/include/table_sleep.h"
#include "../database/include/table_exercises.h"
#include "../database/include/table_phys_info.h"

namespace CSVHelpers {
static constexpr size_t DEFAULT_COLUMN_VALUE = 0;
static const std::string FILENAME = "polar_user_data.csv";
static constexpr size_t BATCH_SIZE = 10;

static inline std::string get_column_names() {
    DBWorker &db_worker = DBWorker::GetInstance();
    std::string activity_cols =
        db_worker.GetTableColumns(ActivityTable::GetName()).fetchOne()[0].get<std::string>();
    std::string exercise_cols =
        db_worker.GetTableColumns(ExercisesTable::GetName()).fetchOne()[0].get<std::string>();
    std::string phys_cols =
        db_worker.GetTableColumns(PhysTable::GetName()).fetchOne()[0].get<std::string>();
    std::string sleep_cols =
        db_worker.GetTableColumns(SleepTable::GetName()).fetchOne()[0].get<std::string>();
    return "date," + activity_cols + "," + exercise_cols + "," + phys_cols + "," + sleep_cols;
}

static inline void write_to_csv(std::vector<std::string> &csv_rows_batch) {
    static std::ofstream os(FILENAME);

    for (const auto &csv_row : csv_rows_batch) {
        os << csv_row << std::endl;
    }
}

static inline void ConvertToCSV() {
    DBWorker &db_worker = DBWorker::GetInstance();
    mysqlx::SqlResult records = db_worker.JoinAllTables();
    std::vector<std::string> csv_rows_batch;
    csv_rows_batch.push_back(get_column_names());

    while (auto row = records.fetchOne()) {
        std::string csv_row = mysqlx::get_string_date(row) + ",";
        for (size_t i = 1; i < row.colCount(); ++i) {
            if (row[i].getType() == mysqlx::Value::Type::INT64) {
                csv_row += std::to_string(row[i].get<int64_t>());
            } else if (row[i].getType() == mysqlx::Value::Type::STRING) {
                csv_row += row[i].get<std::string>();
            } else if (row[i].isNull()) {
                csv_row += "";
            } else {
                throw std::runtime_error("Unsupported value type");
            }
            if (i != row.colCount() - 1) {
                csv_row += ",";
            }
        }
        csv_rows_batch.push_back(csv_row);
        if (csv_rows_batch.size() == BATCH_SIZE) {
            write_to_csv(csv_rows_batch);
            csv_rows_batch.clear();
        }
    }
    if (!csv_rows_batch.empty()) {
        write_to_csv(csv_rows_batch);
    }
}

static inline void DeleteCSV() {
    std::remove(FILENAME.data());
};

}  // namespace CSVHelpers