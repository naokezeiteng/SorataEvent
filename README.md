# SorataEvent
## 定义事件类型
SORATA_EVENT_OP(invalid, char, "invalid")  
事件：invalid  
类型：char  
描述："invalid"  
```
#define SORATA_EVENT_DESCRIPTION                   \
    SORATA_EVENT_OP(invalid, char, "invalid")      \
                                                   \
    SORATA_EVENT_OP(evnt_a, bool, "a")       \
    SORATA_EVENT_OP(evnt_b, START_TASK, "b") \
                                                   \
    SORATA_EVENT_OP(max, char, "max")
```
## 需要事件通知类继承事件支持
```
class task : public sorata::EventSupport
{
public:
    /* 重写事件处理方法 */
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
```
## 发送事件通知
e2.data 的类型由SORATA_EVENT_OP定义而来，不需要显式声明data类型
```
    sorata::Event<sorata::EventId::evnt_b> e2;
    e2.data.enable = true;
    e2.data.msg = "example";
    e2.notify();
```