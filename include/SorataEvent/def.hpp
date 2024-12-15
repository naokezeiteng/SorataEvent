#pragma once
#include <string>

namespace sorata
{
    struct START_TASK
    {
        int enable;
        std::string msg;
    };

#define SORATA_EVENT_DESCRIPTION                   \
    SORATA_EVENT_OP(invalid, char, "invalid")      \
                                                   \
    SORATA_EVENT_OP(evnt_a, bool, "a")       \
    SORATA_EVENT_OP(evnt_b, START_TASK, "b") \
                                                   \
    SORATA_EVENT_OP(max, char, "max")

#define SORATA_EVENT_OP(code, type, desp) code,
    enum class EventId
    {
        SORATA_EVENT_DESCRIPTION
    };
}