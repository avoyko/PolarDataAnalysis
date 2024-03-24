#include "exercises.h"

int JsonExerciseInfo::ExerciseID() {
    return std::stoi(NormalizedString(exercise_["id"].dump()));
}

std::string JsonExerciseInfo::UploadTime() {
    return NormalizedString(exercise_["upload-time"].dump());
}

std::string JsonExerciseInfo::PolarUser() {
    return NormalizedString(exercise_["polar-user"].dump());
}

int JsonExerciseInfo::TransactionId() {
    return std::stoi(NormalizedString(exercise_["transaction-id"].dump()));
}

std::string JsonExerciseInfo::Device() {
    return NormalizedString(exercise_["device"].dump());
}

std::string JsonExerciseInfo::DeviceID() {
    return NormalizedString(exercise_["device_id"].dump());
}

std::string JsonExerciseInfo::StartTime() {
    return NormalizedString(exercise_["start-time"].dump());
}

int JsonExerciseInfo::StartTimeUtcOffset() {
    return std::stoi(NormalizedString(exercise_["start-time-utc-offset"].dump()));
}

std::string JsonExerciseInfo::Duration() {
    return NormalizedString(exercise_["duration"].dump());
}

int JsonExerciseInfo::Calories() {
    return std::stoi(NormalizedString(exercise_["calories"].dump()));
}

int JsonExerciseInfo::Distance() {
    return std::stoi(NormalizedString(exercise_["distance"].dump()));
}

std::pair<int, int> JsonExerciseInfo::HeartRate() {
    auto heart_info = exercise_["heart-rate"];
    try {
        int avg_heart_rate = std::stoi(NormalizedString(heart_info["average"].dump()));
        int max_heart_rate = std::stoi(NormalizedString(heart_info["maximum"].dump()));
        return std::pair<int, int>{avg_heart_rate, max_heart_rate};
    } catch (...) {
        return {0, 0};
    }
}

std::string JsonExerciseInfo::SportCategory() {
    return NormalizedString(exercise_["sport"].dump());
}

bool JsonExerciseInfo::HasRoute() {
    return NormalizedString(exercise_["has-route"].dump()) == "true";
}

std::string JsonExerciseInfo::SportName() {
    return NormalizedString(exercise_["detailed-sport-info"].dump());
}

int JsonExerciseInfo::FatPercentage() {
    return std::stoi(NormalizedString(exercise_["fat_percentage"].dump()));
}

int JsonExerciseInfo::CarbohydratePercentage() {
    return std::stoi(NormalizedString(exercise_["carbohydrate-percentage"].dump()));
}

int JsonExerciseInfo::ProteinPercentage() {
    return std::stoi(NormalizedString(exercise_["protein-percentage"].dump()));
}

int JsonExerciseInfo::RunningIndex() {
    return std::stoi(NormalizedString(exercise_["running-index"].dump()));
}

int JsonExerciseInfo::CardioLoad() {
    auto training_load_pro = exercise_["training-load-pro"];
    try {
        return std::stoi(NormalizedString(training_load_pro["cardio-load"].dump()));
    } catch (...) {
        return 0;
    }
}

int JsonExerciseInfo::MuscleLoad() {
    auto training_load_pro = exercise_["training-load-pro"];
    try {
        return std::stoi(NormalizedString(training_load_pro["muscle-load"].dump()));
    } catch (...) {
        return 0;
    }
}

int JsonExerciseInfo::PerceivedLoad() {
    auto training_load_pro = exercise_["training-load-pro"];
    try {
        return std::stoi(NormalizedString(training_load_pro["perceived-load"].dump()));
    } catch (...) {
        return 0;
    }
}

std::string JsonExerciseInfo::CardioLoadInterpretation() {
    auto training_load_pro = exercise_["training-load-pro"];
    try {
        return NormalizedString(training_load_pro["cardio-load-interpretation"].dump());
    } catch (...) {
        return "UNKNOWN";
    }
}

std::string JsonExerciseInfo::MuscleLoadInterpretation() {
    auto training_load_pro = exercise_["training-load-pro"];
    try {
        return NormalizedString(training_load_pro["muscle-load-interpretation"].dump());
    } catch (...) {
        return "UNKNOWN";
    }
}

std::string JsonExerciseInfo::PerceivedLoadInterpretation() {
    auto training_load_pro = exercise_["training-load-pro"];
    try {
        return NormalizedString(training_load_pro["perceived-load-interpretation"].dump());
    } catch (...) {
        return "UNKNOWN";
    }
}

std::string JsonExerciseInfo::UserRpe() {
    auto training_load_pro = exercise_["training-load-pro"];
    try {
        return NormalizedString(training_load_pro["user-rpe"].dump());
    } catch (...) {
        return "UNKNOWN";
    }
}

