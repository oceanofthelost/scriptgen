/*******************************************************************************
Name            : packetIn.hpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef PACKETIN_ECS260
#define PACKETIN_ECS260

#include <string>
#include "messageBase.hpp"

class PacketIn : public messageBase<PacketIn>
{
    public:
        PacketIn(std::string file)
        {
            filename=file;
        };
        ~PacketIn(){};

    void Version()
    {
        for(auto i = -128; i<=127; i++)
        {
            MsgParameter.config_pktInVersion = to_string(i);
            printConfig( to_string(i) );
        }
    }
};
#endif