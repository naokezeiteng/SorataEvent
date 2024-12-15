#include "SorataEvent/event.hpp"
#include <iostream>

class task : public sorata::EventSupport
{
public:
    int notify(sorata::EventBase &e) override
    {
        auto ret = 0;

        switch (e.id)
        {
            EVENT_CASE(sorata::EventId::evnt_a)
            std::cout << "event:" << msg.name << " data:" << msg.data << std::endl;
            EVENT_END

            EVENT_CASE(sorata::EventId::evnt_b)
            std::cout << "event:" << msg.name << " data:" << "enable:" << msg.data.enable << " msg:" << msg.data.msg << std::endl;
            EVENT_END

        default:
            break;
        }

        return ret;
    }
};

int main()
{
    task t;

    sorata::Event<sorata::EventId::evnt_a> e1;
    e1.data = true;
    e1.notify();

    sorata::Event<sorata::EventId::evnt_b> e2;
    e2.data.enable = true;
    e2.data.msg = "example";
    e2.notify();

    return 0;
}