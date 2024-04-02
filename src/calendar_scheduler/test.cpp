#include "scheduler.h"

int main() {
    DateStamp start_date(2024, 04, 11, 13, 00, 00);
    DateStamp end_date(2024, 04, 11, 15, 00, 00);
    CalendarClient calendarPost;
    calendarPost.PostEvent(L"NIKITA's BD", start_date, end_date);
}