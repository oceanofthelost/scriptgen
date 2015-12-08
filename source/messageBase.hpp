/*******************************************************************************
Name            : messageBase.hpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef CONFIG_BASE_ECS260
#define CONFIG_BASE_ECS260

#include <string>
#include "parameters.h"

template<class Derived>
class messageBase
{
     protected:
        std::string filename;
        void printConfig( std::string iniFilename) 
        {
            string filename_tmp = filename +"/"+ "of" +  iniFilename + ".ini";
            ofstream write ( filename_tmp.c_str() ); // Write to a file
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
    public:
        messageBase(){};
        ~messageBase(){};
        parameters MsgParameter;
        #define OF_MESSAGE_TYPE( name ) void name(){cout<<"No User Definition" <<endl;}
        #include "messageType.inc"
        #undef OF_MESSAGE_TYPE
};

#endif