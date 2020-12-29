//
// Created by zhuque on 2020/12/16.
//

#ifndef ATMINCSP_RECEIVER_H
#define ATMINCSP_RECEIVER_H
#include "msg.h"
#include "sender.h"
#include "dispatcher.h"
namespace messaging {
    class receiver {
        queue q;    ////< @brief receiver拥有消息队列

    public:
        ////< @note Operator的使用(类型强制转换成员函数)
        ////< @note 类型转换函数的特征：1.类型转换函数定义在源类中
        ////< @note 2.须由operator修饰，函数名称是目标类型名或目标类名
        ////< @note 3.函数没有参数，没有返回值，但是有return语句，在return语句中返回目标类型数据或调用目标类的构造函数
        operator sender() {
            return sender(&q);
        }

        dispatcher wait() {
            return dispatcher(&q);
        }
    };
}

#endif //ATMINCSP_RECEIVER_H
