/*******************************************************************************
Name            : messageBase.h
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef CONFIG_BASE_ECS260
#define CONFIG_BASE_ECS260

#include <string>
#include "parameters.h"

class messageBase
{
    protected:
        std::string filename;
        void printConfig( std::string) ;
    public:
        messageBase();
        virtual ~messageBase();
        parameters MsgParameter;
        #define OF_MESSAGE_TYPE( name ) virtual void name();
        #include "messageType.inc"
        #undef OF_MESSAGE_TYPE
};

#endif