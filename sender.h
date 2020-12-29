//
// Created by zhuque on 2020/12/16.
//

#ifndef ATMINCSP_SENDER_H
#define ATMINCSP_SENDER_H
////< @brief 是对消息队列的简单包装，只允许消息被压入
////< @brief 复制sender的实例仅复制指向队列的指针，而非队列本身
#include "msg.h"
namespace messaging {
    class sender {
        queue *q;
    public:
        sender() : q(nullptr) {}

        explicit sender(queue *q_) : q(q_) {}

        template<typename Message>
        void send(const Message &msg) {
            if (q) {
                q->push(msg);
            }
        }
    };
}


#endif //ATMINCSP_SENDER_H
