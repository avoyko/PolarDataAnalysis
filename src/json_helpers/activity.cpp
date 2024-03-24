#include "activity.h"

int JsonActivityInfo::ActivityID() {
    return std::stoi(NormalizedString(activity_["id"].dump()));
}

int JsonActivityInfo::TransactionID() {
    return std::stoi(NormalizedString(activity_["transaction-id"].dump()));
}

std::string JsonActivityInfo::Date() {
    return NormalizedString(activity_["date"].dump());
}

int JsonActivityInfo::Calories() {
    return std::stoi(NormalizedString(activity_["calories"].dump()));
}

int JsonActivityInfo::ActiveCalories() {
    return std::stoi(NormalizedString(activity_["active-calories"].dump()));
}

std::string JsonActivityInfo::Duration() {
    return NormalizedString(activity_["duration"].dump());
}

int JsonActivityInfo::Steps() {
    return std::stoi(NormalizedString(activity_["active-steps"].dump()));
}
