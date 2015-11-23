/*******************************************************************************
Name            : parameters.h
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef PARAMS_H_ECS260
#define PARAMS_H_ECS260

#include <string>
#include <cstdint>
#include <fstream>
using namespace std;


// X macros are be used here
struct parameters
{
    #define PARAM(a, b, c) string a##_##b = #c;
    #include "params.inc"
    #undef PARAM

    void print(ofstream& file)
    {
        #define PARAM(a, b, c) file<<#a<<"."<<#b<<" = "<<a##_##b<<endl;
        #include "params.inc"
        #undef PARAM
    }
};

struct Num_OF_Message_Types
{
	#define OF_MESSAGE_TYPE( name ) uint8_t name;
	#include "messageType.inc"
	#undef OF_MESSAGE_TYPE
};

struct Num_OF_Message
{
	#define OF_MESSAGE( name ) uint8_t name;
	#include "messages.inc"
	#undef OF_MESSAGE
};




#endif