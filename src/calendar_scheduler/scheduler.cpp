#include "calendar_exception.h"
#include "scheduler.h"

#include <boost/format.hpp>
#include <Python.h>
#include <algorithm>
#include <array>

const std::wstring venv_executable = L"../../venv/bin/python3.11";

std::wstring DateStamp::Serialize() const {
    boost::wformat fmt = boost::wformat(L"%1%-%2%-%3%T%4%:%5%:%6%+03:00")
                         % std::to_wstring(year) % std::to_wstring(month) % std::to_wstring(day) %
                         std::to_wstring(hour) % std::to_wstring(minutes) % std::to_wstring(seconds);
    return fmt.str();
}

void CalendarClient::PostEvent(const std::wstring &event_name, DateStamp start_datestamp, DateStamp end_datestamp) {
    PyConfig config;
    PyConfig_InitIsolatedConfig(&config);
    PyConfig_SetString(&config, &config.executable, venv_executable.data());
    auto argv = InitializeEventArgv(event_name, start_datestamp.Serialize(), end_datestamp.Serialize());
    PyConfig_SetArgv(&config, 4, argv);
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
    FreeEventArgv(4, argv);
}

wchar_t *CalendarClient::CopyWcharArgument(const std::wstring &wstr) {
    auto *buf = new wchar_t[wstr.size() + 1];
    std::ranges::copy(wstr.begin(), wstr.end(), buf);
    buf[wstr.size()] = '\0';
    return buf;
}

wchar_t **CalendarClient::InitializeEventArgv(const std::wstring &event_name, const std::wstring &start_date_string,
                                              const std::wstring &end_date_string) {
    std::array<std::wstring, 4> wstring_args;
    wstring_args[0] = L"post.py";
    wstring_args[1] = event_name;
    wstring_args[2] = start_date_string;
    wstring_args[3] = end_date_string;
    auto **argv = new wchar_t *[4];
    for (size_t i = 0; i < wstring_args.size(); ++i) {
        argv[i] = CopyWcharArgument(wstring_args[i]);
    }
    return argv;
};

void CalendarClient::FreeEventArgv(int argc, wchar_t **argv) {
    for (size_t i = 0; i < argc; ++i) {
        delete[] argv[i];
    }
    delete[] argv;
}