/*******************************************************************************
Name            : helloMessage.hpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef HELLO_ECS260
#define HELLO_ECS260

#include <string>
#include "messageBase.hpp"

class Hello : public messageBase<Hello>
{
    public:
        Hello(std::string file)
        {
            filename=file;
        };
        ~Hello(){};
        void Version()
        {
            for(auto i = -128; i<=127; i++)
            {
                MsgParameter.config_helloVersion = to_string(i);
                printConfig( to_string(i) );
            }
        }

        void Type()
        {
            std::string tmp[] = {"HELLO", "FEATURES_REPLY", "BARRIER_REPLY", "GET_CONFIG_REPLY", "STATS_REPLY", "PACKET_IN"};

            for( auto i : tmp)
            {
                MsgParameter.config_helloType = i;
                printConfig( i );
            }
        }
};

#endif