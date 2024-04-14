#pragma once

#include <string>

struct DateStamp {
public:
    DateStamp(int y, int mon, int d,
              int h, int min, int sec) : year(y), month(mon), day(d),
                                         hour(h), minutes(min), seconds(sec) {};

    [[nodiscard]] std::wstring Serialize() const;

private:
    int year, month, day;
    int hour, minutes, seconds;
};

class CalendarClient {
public:
    void PostEvent(const std::wstring &event_name, DateStamp start_datestamp, DateStamp end_datestamp);

    static wchar_t *CopyWcharArgument(const std::wstring &wstr);

    static wchar_t **InitializeEventArgv(const std::wstring &event_name, const std::wstring &start_date_string,
                                         const std::wstring &end_date_string);

    static void FreeEventArgv(int argc, wchar_t **argv);
};