#include "calendar_exception.h"

#include <Python.h>
#include <iostream>
#include <array>
#include <chrono>
#include <algorithm>

const std::wstring venv_executable = L"../../venv/bin/python3.11";

class CalendarPost {
public:
    void PostEvent(const std::chrono::year_month_day &ymd, const std::wstring &event_name) {
        if (!ymd.ok()) {
            throw CalendarException("Wrong year-month-date format");
        }
        PyConfig config;
        PyConfig_InitIsolatedConfig(&config);
        PyConfig_SetString(&config, &config.executable, venv_executable.data());
        auto argv = InitializeEventArgv(ymd, event_name);
        PyConfig_SetArgv(&config, 5, argv);
        auto status = Py_InitializeFromConfig(&config);
        PyConfig_Clear(&config);

        if (PyStatus_Exception(status)) {
            throw CalendarException(status.err_msg ? status.err_msg : "N/A");
        }
        FILE *fp = fopen("post.py", "r");
        if (fp == nullptr) {
            throw CalendarException("Post failed because file's not been opened.");
        }
        PyRun_SimpleFile(fp, "post.py");
        Py_Finalize();
        FreeEventArgv(5, argv);
    }

    static wchar_t *CopyWcharArgument(const std::wstring &wstr) {
        auto *buf = new wchar_t[wstr.size() + 1];
        std::ranges::copy(wstr.begin(), wstr.end(), buf);
        buf[wstr.size()] = '\0';
        return buf;
    }

    static wchar_t **InitializeEventArgv(const std::chrono::year_month_day &ymd, const std::wstring &event_name) {
        std::array<std::wstring, 5> wstring_args;
        wstring_args[0] = L"post.py";
        wstring_args[1] = event_name;
        wstring_args[2] = std::to_wstring(static_cast<int>(ymd.year()));
        wstring_args[3] = std::to_wstring(static_cast<unsigned>(ymd.month()));
        wstring_args[4] = std::to_wstring(static_cast<unsigned>(ymd.day()));
        auto **argv = new wchar_t *[5];
        for (size_t i = 0; i < wstring_args.size(); ++i) {
            argv[i] = CopyWcharArgument(wstring_args[i]);
        }
        return argv;
    };

    static void FreeEventArgv(int argc, wchar_t **argv) {
        for (size_t i = 0; i < argc; ++i) {
            delete[] argv[i];
        }
        delete[] argv;
    }
};