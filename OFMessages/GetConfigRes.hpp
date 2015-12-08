/*******************************************************************************
Name            : GetConfigRes.hpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef GET_CONFIG_RES_ECS260
#define GET_CONFIG_RES_ECS260

#include <string>
#include "messageBase.hpp"

class GetConfigRes : public messageBase<GetConfigRes>
{
    public:
        GetConfigRes(std::string file)
        {
            filename=file;
        };
        ~GetConfigRes(){};

    void Version()
    {
        for(auto i = -128; i<=127; i++)
        {
            MsgParameter.config_getConfReplyVersion = to_string(i);
            printConfig( to_string(i) );
        }
    }
};
#endif