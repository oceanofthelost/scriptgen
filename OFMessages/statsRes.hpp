/*******************************************************************************
Name            : statsRes.hpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef STATS_RES_ECS260
#define STATS_RES_ECS260

#include <string>
#include "messageBase.hpp"

class StatsRes : public messageBase<StatsRes>
{
    public:
        StatsRes(std::string file)
        {
            filename=file;
        };
        ~StatsRes(){};

    void version()
    {
        for(auto i = -128; i<=127; i++)
        {
            MsgParameter.config_statsReplyVersion = to_string(i);
            printConfig( to_string(i) );
        }
    }
};
#endif