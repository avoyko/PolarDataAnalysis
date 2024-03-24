#pragma once

#include <utility>

#include "utilities.h"

using namespace Utils;

class JsonExerciseInfo {
public:
    explicit JsonExerciseInfo(wjson exercise) : exercise_(std::move(exercise)) {};

    int ExerciseID();

    std::string UploadTime();

    std::string PolarUser();

    int  TransactionId();

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


    const wjson exercise_;
};



