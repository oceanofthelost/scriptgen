/*******************************************************************************
Name            : helloMessage.cpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#include "helloMessage.h"


#include <string>


Hello::Hello(string passed)
{
    filename = passed;
}

void Hello::version()
{
    for(int i = -127; i<=127; i++)
    {
        MsgParameter.config_helloVersion = to_string(i);
        printConfig( to_string(i) );
    }
}

void Hello::type()
{
    std::string tmp[] = {"HELLO", "FEATURES_REPLY", "BARRIER_REPLY", "GET_CONFIG_REPLY", "STATS_REPLY", "PACKET_IN"};

    for( auto i : tmp)
    {
        MsgParameter.config_helloType = i;
        printConfig( i );
    }
}