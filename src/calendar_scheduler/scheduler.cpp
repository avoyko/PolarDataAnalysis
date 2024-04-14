#include <boost/format.hpp>

#include "include/calendar_exception.h"
#include "include/scheduler.h"

const std::string venv_executable = "../../venv/bin/python";

std::string DateStamp::Serialize() const {
    boost::format fmt = boost::format("%1%-%2%-%3%T%4%:%5%:%6%+03:00") % std::to_string(year) %
                        std::to_string(month) % std::to_string(day) % std::to_string(hour) %
                        std::to_string(minutes) % std::to_string(seconds);
    return fmt.str();
}

void CalendarClient::PostEvent(const std::string &event_name, DateStamp start_datestamp,
                               DateStamp end_datestamp) {
    pid_t pid = fork();
    if (pid == 0) {
        std::flush(std::cout);
        std::string args = event_name + ' ' + start_datestamp.Serialize() + ' ' + end_datestamp.Serialize();
        std::string command = "../../venv/bin/python3.12 ../calendar_scheduler/post.py " + args;
        std::system(command.c_str());
        exit(0);
    }
    wait(nullptr);
}