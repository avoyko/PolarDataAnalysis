add_library(polarapi_sources_files
        ../endpoints/src/daily_activity.cpp
        ../endpoints/src/daily_activity_transaction.cpp
        ../endpoints/src/physical_info.cpp
        ../endpoints/src/physical_info_transaction.cpp
        ../endpoints/src/pull_notifications.cpp
        ../endpoints/src/training_data.cpp
        ../endpoints/src/training_data_transaction.cpp
        ../endpoints/src/transaction.cpp
        ../endpoints/src/users.cpp
        ../lib/accesslink.cpp
        ../lib/oauth2.cpp
        ../lib/request_wrap.cpp
)