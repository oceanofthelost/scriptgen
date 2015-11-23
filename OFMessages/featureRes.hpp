/*******************************************************************************
Name            : featRes.hpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef FEATURE_RES_ECS260
#define FEATURE_RES_ECS260

#include <string>
#include "messageBase.hpp"

class FeatureRes : public messageBase<FeatureRes>
{
    public:
        FeatureRes(std::string file)
        {
            filename=file;
        };
        ~FeatureRes(){};

    void version()
    {
        for(auto i = -128; i<=127; i++)
        {
            MsgParameter.config_featuresReplyVersion = to_string(i);
            printConfig( to_string(i) );
        }
    }
};
#endif