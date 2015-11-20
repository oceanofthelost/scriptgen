/*******************************************************************************
Name            : messageBase.cpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#include "messageBase.h"
#include <iostream>
#include <string>
#include <stdlib.h>


#include <errno.h>
#include <sstream>
#warning "REMOVE THE FOLLOWING ON LINUX. FIX IS FOR CYGWIN"
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


messageBase::~messageBase()
{

}
messageBase::messageBase()
{

}

//The argument passed withh become the filename for the ini file generated. 
void messageBase::printConfig(string iniFilename)
{
    string filename_tmp = filename +"/"+ "of" +  iniFilename + ".ini";
    ofstream write ( filename_tmp ); // Write to a file
    // makes sure the file is open. If so we write to it
    if( write.is_open() )
    {
           MsgParameter.print( write );
    }
    else
    {
        std::cout<<"Can't open file"<<endl;
        exit(errno);
    }
    write.close();
}

// Auto generates a default implementation for all of the fields that can be fuzzed. 
#define OF_MESSAGE_TYPE( name ) void messageBase::name () { std::cout<<"No User Definition"<<std::endl; }
#include "messageType.inc"
#undef OF_MESSAGE_TYPE