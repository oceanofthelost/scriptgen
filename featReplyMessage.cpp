/*******************************************************************************
Name            : featReplyMessa.cpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#include "featReplyMessage.h"

#include <iostream>
#include <errno.h>
#include <stdlib.h>
#include <array>

FeatureResponse::FeatureResponse(string passed)
{
    filename = passed;
}

void FeatureResponse::version()
{
    for(int i = -127; i<=127; i++)
    {
        MsgParameter.config_featuresReplyVersion = to_string(i);
        printConfig( to_string(i) );
    }
}

void FeatureResponse::type()
{
    std::string tmp[] = {"HELLO", "FEATURES_REPLY", "BARRIER_REPLY", "GET_CONFIG_REPLY", "STATS_REPLY", "PACKET_IN"};
    
    for( auto i : tmp)
    {
        MsgParameter.config_featuresReplyType = i;
        printConfig( i );
    }
}

