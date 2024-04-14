#include "include/model.h"
#include "include/model_exception.h"
#include "model_utilities.h"
#include "Python.h"
#include "../calendar_scheduler/include/scheduler.h"

const std::wstring venv_executable = L"../../venv/bin/python3.12";

void Model::Activate() {
//    CSVHelpers::ConvertToCSV();
    CROW_LOG_INFO << "Model is working...";
    PyConfig config;
    PyConfig_InitIsolatedConfig(&config);
    PyConfig_SetString(&config, &config.executable, venv_executable.data());
    auto status = Py_InitializeFromConfig(&config);
    PyConfig_Clear(&config);
    if (PyStatus_Exception(status)) {
        throw ModelException(status.err_msg ? status.err_msg : "N/A");
    }
    FILE *fp = fopen("../model/model.py", "r+");
    if (fp == nullptr) {
        throw ModelException("Model failed because file's not been opened.");
    }
    PyRun_SimpleFile(fp, "../model/model.py");
    CROW_LOG_INFO << "Model has finished";
}