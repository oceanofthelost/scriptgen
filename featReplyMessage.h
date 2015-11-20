/*******************************************************************************
Name            : featReplyMessa.h
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef FEAT_REPLY_MESSAGE_ECS260
#define FEAT_REPLY_MESSAGE_ECS260

#include <string>
#include "messageBase.h"

class FeatureResponse : public messageBase
{
    public:
        FeatureResponse( std:: string );
        ~FeatureResponse() {};
        void type( );
        void version( );
};
#endif