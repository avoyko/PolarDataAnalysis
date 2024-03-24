#include <Python.h>
#include <iostream>

int main() {
    PyConfig config;
    PyConfig_InitIsolatedConfig(&config);

    const wchar_t *venv_executable = L"../../venv/bin/python";
    PyConfig_SetString(&config, &config.executable, venv_executable);
    auto status = Py_InitializeFromConfig(&config);
    PyConfig_Clear(&config);

    if (PyStatus_Exception(status)) {
        std::cerr << "status.func: " << (status.func ? status.func : "N/A") << std::endl;
        std::cerr << "status.err_msg: " << (status.err_msg ? status.err_msg : "N/A") << std::endl;
    }

    FILE *fp = fopen("quickstart.py", "r");
    if (fp == nullptr) {
        std::cerr << "File hasn't been opened." << std::endl;
    }
    PyRun_SimpleFile(fp, "quickstart.py");
    Py_Finalize();
}