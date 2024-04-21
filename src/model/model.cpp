#include "include/model.h"
#include "include/model_exception.h"
#include "model_utilities.h"
#include "../calendar_scheduler/include/scheduler.h"
#include <sys/wait.h>
#include <fstream>

const std::string venv_executable = "../../venv/bin/python";

void Model::Activate() {
    //    CSVHelpers::ConvertToCSV();
    CROW_LOG_INFO << "Model is working...";
    std::flush(std::cout);
    std::string command = venv_executable + " ../model/model.py";
    std::system(command.c_str());
    CROW_LOG_INFO << "Model has finished";
}

std::vector<std::string> Model::GetPrediction() {
    std::ifstream fin("prediction.txt");
    std::string prediction;
    std::vector<std::string> exercises;
    while (fin >> prediction) {
        exercises.push_back(prediction);
    }
    return exercises;
}