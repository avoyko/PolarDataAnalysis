#include "table_phys_info.h"

void DayPhysTable::Update(const wjson& phys) {
    std::string last_date = LastRecordDate();
    std::vector<std::string> day_phys_info;

    for (size_t i = 0; i < phys.size(); ++i) {
        std::string date = JsonHelper::StringValue(phys[i], "date");
        std::string weight = JsonHelper::StringValue(phys[i], "weight");
        std::string height = JsonHelper::StringValue(phys[i], "height");
        std::string max_heart_rate = JsonHelper::IntValue(phys[i], "max-heart-rate");
        std::string resting_heart_rate = JsonHelper::IntValue(phys[i], "resting-heart-rate");
        std::string aerobic_threshold = JsonHelper::IntValue(phys[i], "aerobic-threshold");
        std::string anaerobic_threshold = JsonHelper::IntValue(phys[i], "anaerobic-threshold");
        std::string vo2_max = JsonHelper::IntValue(phys[i], "vo2-max");
        day_phys_info = {date,
                         weight,
                         height,
                         max_heart_rate,
                         resting_heart_rate,
                         aerobic_threshold,
                         anaerobic_threshold,
                         vo2_max};
        InsertIntoTable(day_phys_info, columns_);
    }
}
