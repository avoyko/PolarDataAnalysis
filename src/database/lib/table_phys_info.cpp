#include "../include/table_phys_info.h"

void PhysTable::Update(const WriteJson& phys) {
    std::string last_date = LastRecordDate();

    for (size_t i = 0; i < phys.size(); ++i) {
        std::string date = JsonHelper::DateValue(phys[i], "created");
        std::string weight = JsonHelper::IntValue(phys[i], "weight");
        std::string height = JsonHelper::IntValue(phys[i], "height");
        std::string max_heart_rate = JsonHelper::IntValue(phys[i], "maximum-heart-rate");
        std::string resting_heart_rate = JsonHelper::IntValue(phys[i], "resting-heart-rate");
        std::string aerobic_threshold = JsonHelper::IntValue(phys[i], "aerobic-threshold");
        std::string anaerobic_threshold = JsonHelper::IntValue(phys[i], "anaerobic-threshold");
        std::string vo2_max = JsonHelper::IntValue(phys[i], "vo2-max");
        if (date != mysqlx::DEFAULT_DATE && date > last_date) {
            InsertIntoTable(date, weight, height, max_heart_rate, resting_heart_rate,
                            aerobic_threshold, anaerobic_threshold, vo2_max);
        }
    }
}
std::string PhysTable::GenerateTable() {
    boost::format fmt = boost::format(
                            "CREATE TABLE %1%("
                            "date DATE,"
                            "weight INT,"
                            "height INT,"
                            "max_hr INT,"
                            "resting_hr INT,"
                            "ae_t INT,"
                            "an_t INT,"
                            "vo2_max INT"
                            ");") %
                        table_name_.data();
    return fmt.str();
}
std::string PhysTable::GetName() {
    return table_name_.data();
}
