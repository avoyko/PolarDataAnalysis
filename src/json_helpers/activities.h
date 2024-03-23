#pragma once

#include <utility>

#include "utilities.h"


class JsonExerciseInfo {
public:
    explicit JsonExerciseInfo(wjson exercise) : exercise_(std::move(exercise)) {};

    std::string UploadTime();

    std::string PolarUser();

    int TransactionId();

    std::string Device();

    std::string DeviceID();

    std::string StartTime();

    int StartTimeUtcOffset();

    std::string Duration();

    int Calories();

    int Distance();

    std::pair<int, int> HeartRate();

    std::string SportCategory();

    bool HasRoute();

    std::string SportName();

    int FatPercentage();

    int CarbohydratePercentage();

    int ProteinPercentage();

    int RunningIndex();

    int CardioLoad();

    int MuscleLoad();

    int PerceivedLoad();

    std::string CardioLoadInterpretation();

    std::string MuscleLoadInterpretation();

    std::string PerceivedLoadInterpretation();

    std::string UserRpe();


private:

    static std::string NormalizedString(const std::string &s);

    const wjson exercise_;
};



