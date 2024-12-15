#pragma once

#include <memory>
#include <vector>
#include <array>
#include <functional>
#include <unordered_map>
#include "SorataEvent/def.hpp"

namespace sorata
{
#undef SORATA_EVENT_OP
#define SORATA_EVENT_OP(code, type, desp) {EventId::code, desp},
    inline std::unordered_map<EventId, std::string> event_desp = {SORATA_EVENT_DESCRIPTION};

    class EventBase
    {
    protected:
        bool trigger_flag;

    public:
        const EventId id;
        const std::string name = event_desp.at(id);
        EventBase(EventId _id) : id(_id) {}
        void trigger() { trigger_flag = true; }
    };

    inline std::vector<std::function<int(EventBase &e)>> listener_regist;
    inline std::array<std::pair<bool, std::vector<int>>, (int)EventId::max> listener_effective;

    template <EventId>
    class Event;

#define EVENT_REGIST(event_id, data_type)                                      \
    template <>                                                                \
    class Event<EventId::event_id> : public EventBase                          \
    {                                                                          \
    public:                                                                    \
        Event() : EventBase(EventId::event_id) {}                              \
        data_type data;                                                        \
                                                                               \
        int notify()                                                           \
        {                                                                      \
            int ret = 0;                                                       \
                                                                               \
            auto &list = listener_effective.at((int)id);                       \
            if (list.first)                                                    \
            {                                                                  \
                for (auto i : list.second)                                     \
                    ret = listener_regist.at(i)(*this);                        \
            }                                                                  \
            else                                                               \
            {                                                                  \
                list.first = true;                                             \
                for (size_t i = 0; i < listener_regist.size(); ++i)            \
                {                                                              \
                    trigger_flag = false;                                      \
                    ret = listener_regist.at(i)(*this);                        \
                    if (trigger_flag)                                          \
                        listener_effective.at((int)id).second.emplace_back(i); \
                }                                                              \
            }                                                                  \
                                                                               \
            return ret;                                                        \
        }                                                                      \
    };

    class EventSupport
    {
    public:
        virtual int notify(EventBase &e) { return 0; }
        EventSupport()
        {
            listener_regist.emplace_back(std::bind(&EventSupport::notify, this, std::placeholders::_1));
        }
    };

#undef SORATA_EVENT_OP
#define SORATA_EVENT_OP(code, type, desp) EVENT_REGIST(code, type)
    SORATA_EVENT_DESCRIPTION

#define EVENT_CASE(id) \
    case id:           \
    {                  \
        e.trigger();   \
        auto &msg = static_cast<sorata::Event<id> &>(e);

#define EVENT_END \
    }             \
    break;
}