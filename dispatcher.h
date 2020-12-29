//
// Created by zhuque on 2020/12/16.
//

#ifndef ATMINCSP_DISPATCHER_H
#define ATMINCSP_DISPATCHER_H
#include "msg.h"
#include "TemplateDispatcher.h"
namespace messaging {
    class close_queue{};

    class dispatcher {
        queue *q;
        bool chained;

        dispatcher(const dispatcher&)=delete;   ////< @note 禁止拷贝构造
        dispatcher& operator=(const dispatcher&)=delete; ////< @note 禁止拷贝赋值

        template<typename Dispatcher, typename Msg, typename Func>
        friend class TemplateDispatcher;

        void wait_and_dispatch() {
            for(;;) {
                auto msg = q->wait_and_pop();
                dispatch(msg);
            }
        }

        bool dispatch(const std::shared_ptr<message_base> &msg) {
            ////< @note wrapped_message<close_queue>说明wrapped_message中
            ////< @note 的typename Msg是close_queue类型的
            if (dynamic_cast<wrapped_message<close_queue>*>(msg.get())) {
                throw close_queue();
            }
            return false;
        }

    public:
        dispatcher(dispatcher &&other) : q(other.q), chained(other.chained) {
            other.chained = true;   ////< @attention 用右值构造，把右值的chained置为true
        }

        explicit dispatcher(queue *q_) : q(q_), chained(false) {}

        ////< @note 用于处理特定类型的消息
        template<typename Message, typename Func>   ////< @note 模板参数列表
        TemplateDispatcher<dispatcher, Message, Func> ////< @note 返回值
        handle(Func &&f) {  ////< @note 函数体
            return TemplateDispatcher<dispatcher, Message, Func>(
                    q, this, std::forward<Func>(f));
        }

        ////< @attention 防止移入的对象等待消息?
        ~dispatcher() noexcept(false) { ////< @note 可能抛出异常
            if (!chained) {
                wait_and_dispatch();
            }
        }
    };
}

#endif //ATMINCSP_DISPATCHER_H
