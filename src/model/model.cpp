#include "include/model.h"
#include "include/model_exception.h"
#include "model_utilities.h"
#include "../calendar_scheduler/include/scheduler.h"
#include <sys/wait.h>
#include <fstream>

const std::string venv_executable = "../../venv/bin/python3.12";

void Model::Activate() {
//    CSVHelpers::ConvertToCSV();
    CROW_LOG_INFO << "Model is working...";
    pid_t pid = fork();
    if (pid == 0) {
        std::flush(std::cout);
        std::system("../../venv/bin/python3.12 ../model/model.py");
        exit(0);
    }
    wait(nullptr);
    CROW_LOG_INFO << "Model has finished";
}

std::string Model::GetPrediction() {
    std::ifstream fin("prediction.txt");
    std::string prediction;
    std::getline(fin, prediction);
    return prediction;
}