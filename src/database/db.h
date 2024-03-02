#pragma once

#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>

namespace Health
{
    namespace WatchData_
    {
        struct Id
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "id";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T id;
                    T& operator()() { return id; }
                    const T& operator()() const { return id; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
        struct UserName
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "user_name";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T userName;
                    T& operator()() { return userName; }
                    const T& operator()() const { return userName; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
        };
        struct Date
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "date";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T date;
                    T& operator()() { return date; }
                    const T& operator()() const { return date; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::day_point, sqlpp::tag::can_be_null>;
        };
        struct TotalSteps
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "total_steps";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T totalSteps;
                    T& operator()() { return totalSteps; }
                    const T& operator()() const { return totalSteps; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
        struct TotalCalories
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "total_calories";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T totalCalories;
                    T& operator()() { return totalCalories; }
                    const T& operator()() const { return totalCalories; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
        struct Weight
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "weight";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T weight;
                    T& operator()() { return weight; }
                    const T& operator()() const { return weight; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
        struct Height
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "height";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T height;
                    T& operator()() { return height; }
                    const T& operator()() const { return height; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
        struct MaxHeartRate
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "max_heart_rate";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T maxHeartRate;
                    T& operator()() { return maxHeartRate; }
                    const T& operator()() const { return maxHeartRate; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
        struct MinHeartRate
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "min_heart_rate";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T minHeartRate;
                    T& operator()() { return minHeartRate; }
                    const T& operator()() const { return minHeartRate; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
        struct AvgHeartRate
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "avg_heart_rate";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T avgHeartRate;
                    T& operator()() { return avgHeartRate; }
                    const T& operator()() const { return avgHeartRate; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
        struct LightSleep
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "light_sleep";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T lightSleep;
                    T& operator()() { return lightSleep; }
                    const T& operator()() const { return lightSleep; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
        struct DeepSleep
        {
            struct _alias_t
            {
                static constexpr const char _literal[] =  "deep_sleep";
                using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
                template<typename T>
                struct _member_t
                {
                    T deepSleep;
                    T& operator()() { return deepSleep; }
                    const T& operator()() const { return deepSleep; }
                };
            };
            using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
        };
    } // namespace WatchData_

    struct WatchData: sqlpp::table_t<WatchData,
            WatchData_::Id,
            WatchData_::UserName,
            WatchData_::Date,
            WatchData_::TotalSteps,
            WatchData_::TotalCalories,
            WatchData_::Weight,
            WatchData_::Height,
            WatchData_::MaxHeartRate,
            WatchData_::MinHeartRate,
            WatchData_::AvgHeartRate,
            WatchData_::LightSleep,
            WatchData_::DeepSleep>
    {
        struct _alias_t
        {
            static constexpr const char _literal[] =  "WatchData";
            using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
            template<typename T>
            struct _member_t
            {
                T WatchData;
                T& operator()() { return WatchData; }
                const T& operator()() const { return WatchData; }
            };
        };
    };
} // namespace Health
