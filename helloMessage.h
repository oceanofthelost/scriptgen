/*******************************************************************************
Name            : helloMessage.h
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef HELLO_MESSAGE_ECS260
#define HELLO_MESSAGE_ECS260

#include <string>
#include "messageBase.h"

class Hello : public messageBase
{
    public:
        Hello( std::string );
        ~Hello() {};
        void type( );
        void version( );
};

#endif