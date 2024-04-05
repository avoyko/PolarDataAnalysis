#include "table_phys_info.h"

void PhysTable::Update(const wjson& phys) {
    std::string last_date = LastRecordDate();

    for (size_t i = 0; i < phys.size(); ++i) {
        std::string date = JsonHelper::StringValue(phys[i], "date");
        std::string weight = JsonHelper::StringValue(phys[i], "weight");
        std::string height = JsonHelper::StringValue(phys[i], "height");
        std::string max_heart_rate = JsonHelper::IntValue(phys[i], "max-heart-rate");
        std::string resting_heart_rate = JsonHelper::IntValue(phys[i], "resting-heart-rate");
        std::string aerobic_threshold = JsonHelper::IntValue(phys[i], "aerobic-threshold");
        std::string anaerobic_threshold = JsonHelper::IntValue(phys[i], "anaerobic-threshold");
        std::string vo2_max = JsonHelper::IntValue(phys[i], "vo2-max");
        if (date > last_date) {
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
