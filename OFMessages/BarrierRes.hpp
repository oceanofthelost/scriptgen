/*******************************************************************************
Name            : barrierRes.hpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef BARRIER_RES_ECS260
#define BARRIER_RES_ECS260

#include <string>
#include "messageBase.hpp"

class BarrierRes : public messageBase<BarrierRes>
{
    public:
        BarrierRes(std::string file)
        {
            filename=file;
        };
        ~BarrierRes(){};

    void Version()
    {
        for(auto i = -128; i<=127; i++)
        {
            MsgParameter.config_barrierReplyVersion = to_string(i);
            printConfig( to_string(i) );
        }
    }
};
#endif