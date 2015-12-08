/*******************************************************************************
Name            : scriptgen.cp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
Description     : Inspired by Kashyap Thimmaraju
*******************************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <errno.h>
#include <set>
#include <map>
#include <sys/stat.h>
//#include <sys/types.h>
#include <utility>
#include "menu.h"

#include "OFMessages.h"

using namespace std;

//create the directory structure that is  needed by this program
void makeDirectory(const char*);
void createHelloReply(string);
void createHelloVersion(string);

// Simple function taht helps with cutting down repetition
bool inline inSet(const set<string>& a, const string& b)
{
    return a.end() != a.find(b);
}


template<typename T>
void test(T* passed,set<string> args)
{
    if (false)
    {
        // This is needed to get the below macro expansion to work. 
    }
    #define OF_MESSAGE_TYPE( name ) else if( inSet(args, #name) ) { \
         passed -> name(); }
    #include "messageType.inc"
    #undef OF_MESSAGE_TYPE
}





int main(int argc, char* argv[])
{
    checkArgs(argc, argv);


    //User sets this variable to the whatever directory they want to use. The rest of the
    // directory structure is derived off of the home directory.

    const string ROOT = "./home";
    const string HOME = ROOT + "/mininet";
    const string TESTSCRIPTS = HOME + "/fuzzing";
    const string ARGV1_filepath = TESTSCRIPTS + "/" + argv[1];
    const string ARGV2_filepath = ARGV1_filepath + "/" + argv[2];

    makeDirectory( ROOT.c_str() );
    makeDirectory( HOME.c_str() );
    makeDirectory( TESTSCRIPTS.c_str() );
    makeDirectory( ARGV1_filepath.c_str() );
    makeDirectory( ARGV2_filepath.c_str() );

    // This will go away when a table is used.
    set<string> args(argv+1, argv+3);

    // This will change when the table method is implemented. Once all of this can be dynamicly loaded
    // the table can be implemented.

    if (false)
    {
        // This is needed to get the below macro expansion to work. 
    }
    #define OF_MESSAGE( name ) else if( inSet(args, #name) ) { \
    name var(ARGV2_filepath); \
    test<name>(&var,args); }
    #include "messages.inc"
    #undef OF_MESSAGE


}

void makeDirectory(const char* filename)
{
    if( (mkdir(filename,0777) != 0) && (errno != EEXIST ))
    {
        cout<<"ERROR: "<<filename<<": "<<std::strerror(errno)<<endl;
        exit(errno);
    }
}
