#pragma once
#include "crow.h"

using ReadJson = crow::json::rvalue;
using WriteJson = crow::json::wvalue;

namespace JsonExamples {
WriteJson activity = std::vector<WriteJson>{
    crow::json::load("{\n"
                     "  \"active-calories\": \"428\",\n"
                     "  \"active-steps\": \"250\",\n"
                     "  \"calories\": \"2329\",\n"
                     "  \"created\": \"2016-04-27T20:11:33.000Z\",\n"
                     "  \"date\": \"2031-12-31\",\n"
                     "  \"duration\": \"PT2H44M\",\n"
                     "  \"id\": \"1234\",\n"
                     "  \"polar-user\": \"https://www.polaraccesslink/v3/users/1\",\n"
                     "  \"transaction-id\": \"179879\"\n"
                     "}")};
WriteJson sleep = crow::json::load(
    "{\n"
    "  \"nights\": [\n"
    "    {\n"
    "      \"continuity\": \"2.1\",\n"
    "      \"continuity_class\": \"2\",\n"
    "      \"date\": \"2031-12-31\",\n"
    "      \"deep_sleep\": \"1000\",\n"
    "      \"device_id\": \"1111AAAA\",\n"
    "      \"group_duration_score\": \"75\",\n"
    "      \"group_solidity_score\": \"54.2\",\n"
    "      \"light_sleep\": \"1000\",\n"
    "      \"long_interruption_duration\": \"6\",\n"
    "      \"polar_user\": \"https://www.polaraccesslink/v3/users/61111666\",\n"
    "      \"rem_sleep\": \"1000\",\n"
    "      \"short_interruption_duration\": \"300\",\n"
    "      \"sleep_charge\": \"28800\",\n"
    "      \"sleep_cycles\": \"100\",\n"
    "      \"sleep_end_time\": \"2020-01-01T09:19:37+03:00\",\n"
    "      \"sleep_goal\": \"3\",\n"
    "      \"sleep_rating\": \"500\",\n"
    "      \"sleep_score\": \"80\",\n"
    "      \"sleep_start_time\": \"2020-01-01T00:39:07+03:00\",\n"
    "      \"total_interruption_duration\": \"3\",\n"
    "      \"unrecognized_sleep_stage\": \"1000\"\n"
    "    }\n"
    "  ]\n"
    "}");

WriteJson physical_info = std::vector<WriteJson>{
    crow::json::load("{\n"
                     "  \"aerobic-threshold\": \"123\",\n"
                     "  \"anaerobic-threshold\": \"123\",\n"
                     "  \"created\": \"2031-12-31T20:11:33.000Z\",\n"
                     "  \"height\": \"180\",\n"
                     "  \"id\": \"123\",\n"
                     "  \"maximum-heart-rate\": \"160\",\n"
                     "  \"polar-user\": \"https://www.polaraccesslink/v3/users/61111666\",\n"
                     "  \"resting-heart-rate\": \"60\",\n"
                     "  \"transaction-id\": \"179879\",\n"
                     "  \"vo2-max\": \"12\",\n"
                     "  \"weight\": \"80\",\n"
                     "  \"weight-source\": \"SOURCE_MEASURED\"\n"
                     "}")};

WriteJson exercises = std::vector<WriteJson>{
    crow::json::load("{\n"
                     "  \"id\": 1937529874,\n"
                     "  \"upload-time\": \"2031-12-31T10:40:0.000Z\",\n"
                     "  \"polar-user\": \"https://www.polaraccesslink/v3/users/1\",\n"
                     "  \"transaction-id\": 179879,\n"
                     "  \"device\": \"Polar M400\",\n"
                     "  \"device-id\": \"1111AAAA\",\n"
                     "  \"start-time\": \"2031-12-31T10:40:02\",\n"
                     "  \"start-time-utc-offset\": 180,\n"
                     "  \"duration\": \"PT2H44M45S\",\n"
                     "  \"calories\": 530,\n"
                     "  \"distance\": 1600.2,\n"
                     "  \"heart-rate\": {\n"
                     "    \"average\": 129,\n"
                     "    \"maximum\": 147\n"
                     "  },\n"
                     "  \"training-load\": 143.22,\n"
                     "  \"sport\": \"OTHER\",\n"
                     "  \"has-route\": true,\n"
                     "  \"club-id\": 999,\n"
                     "  \"club-name\": \"Polar Club\",\n"
                     "  \"detailed-sport-info\": \"RUNNING\",\n"
                     "  \"fat-percentage\": 60,\n"
                     "  \"carbohydrate-percentage\": 38,\n"
                     "  \"protein-percentage\": 2,\n"
                     "  \"running-index\": 51,\n"
                     "  \"training-load-pro\": [\n"
                     "    {\n"
                     "      \"date\": \"2023-01-01\",\n"
                     "      \"cardio-load\": 1,\n"
                     "      \"muscle-load\": 1,\n"
                     "      \"perceived-load\": 1,\n"
                     "      \"cardio-load-interpretation\": \"UNKNOWN\",\n"
                     "      \"muscle-load-interpretation\": \"UNKNOWN\",\n"
                     "      \"perceived-load-interpretation\": \"UNKNOWN\",\n"
                     "      \"user-rpe\": \"UNKNOWN\"\n"
                     "    }\n"
                     "  ]\n"
                     "}")};
}  // namespace JsonExamples