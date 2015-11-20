/*******************************************************************************
Name            : fmenu.cpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#include "menu.h"

#include <string>
#include <set>
#include <iostream>
#include <errno.h>
#include <stdlib.h>

std::set<std::string> OF_Messages = {
    #define OF_MESSAGE( message ) #message,
    #include "messages.inc"
    #undef OF_MESSAGE
};

std::set<std::string> OF_Message_Type = {
    #define OF_MESSAGE_TYPE( messageType ) #messageType,
    #include "messageType.inc"
    #undef OF_MESSAGE_TYPE
};

void checkArgs(int argc, char* argv[] )
{

    if( (argc != 3) )
    {
        std::cout<<"Illegal number of parameters, Format is ./scriptgen {OF Message} {OF Message Type}"<<std::endl;
        printOFMessage();
        printOFMessageType();
        exit(1);
    }

    if(!validArgs(argv))
    {
        std::cout<<"Illegal number of parameters, Format is ./scriptgen {OF Message} {OF Message Type}"<<std::endl;
        printOFMessage();
        printOFMessageType();
        exit(1);
    }
}

void printOFMessage()
{
    std::cout<<"OF Messages:"<<std::endl;
    for(auto it : OF_Messages)
    {
        std::cout<<"\t"<<it<<std::endl;
    }
}

void printOFMessageType()
{
    std::cout<<"OF Message Tye:"<<std::endl;
    for(auto it : OF_Message_Type)
    {
        std::cout<<"\t"<<it<<std::endl;
    }
}

bool validArgs(char* argv[])
{
    auto message = OF_Messages.find( std::string(argv[1]) );
    auto type = OF_Message_Type.find( std::string(argv[2]) );

    // if message or type point to the end of the set then that means that the arguments to the 
    // program are not valid. So return false. Valid means taht both arguments are true. 
    return ( (message == OF_Messages.end() or type == OF_Message_Type.end() ) ? 0 : 1);
}
