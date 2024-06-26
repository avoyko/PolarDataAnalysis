#include <boost/format.hpp>
#include <sys/wait.h>
#include "include/calendar_exception.h"
#include "include/scheduler.h"
#include <unistd.h>
#include <fcntl.h>
#include <ctime>

#if (DEVELOPER_MODE == 1)
const std::string venv_executable = "../../venv/bin/python";
#else
const std::string venv_executable = "python3";
#endif

std::string DateStamp::Serialize() const {
    boost::format fmt = boost::format("%1%-%2%-%3%T%4%:%5%:%6%+03:00") % std::to_string(year) %
                        std::to_string(month) % std::to_string(day) % std::to_string(hour) %
                        std::to_string(minutes) % std::to_string(seconds);
    return fmt.str();
}

void CalendarClient::PostEvent(const std::string &event_name, DateStamp start_datestamp,
                               DateStamp end_datestamp) {
    std::flush(std::cout);
    std::string args = "\'" + event_name + "\'" + ' ' + start_datestamp.Serialize() + ' ' +
                       end_datestamp.Serialize();
    std::string command = venv_executable + " ../calendar_scheduler/post.py " + args;
    std::system(command.c_str());
}

void CalendarClient::ScheduleEvents(const std::vector<std::string> &event_names) {
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);
    for (size_t i = 0; i < event_names.size(); ++i) {
        DateStamp dateStamp(1900 + now->tm_year, 1 + now->tm_mon, now->tm_mday, 18 + i, 00, 00);
        PostEvent(event_names[i], dateStamp, dateStamp);
    }
}