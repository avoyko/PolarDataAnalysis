#pragma once

#include <string>

struct DateStamp {
public:
    DateStamp(int y, int mon, int d,
              int h, int min, int sec) : year(y), month(mon), day(d),
                                         hour(h), minutes(min), seconds(sec) {};

    [[nodiscard]] std::string Serialize() const;

private:
    int year, month, day;
    int hour, minutes, seconds;
};

class CalendarClient {
public:
    void PostEvent(const std::string &event_name, DateStamp start_datestamp, DateStamp end_datestamp);

    void ScheduleEvents(const std::vector<std::string>& event_names);
};