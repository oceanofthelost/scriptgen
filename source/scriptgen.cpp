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

#include "hello.hpp"
#include "featureRes.hpp"
#include "barrierRes.hpp"
#include "getConfigRes.hpp"
#include "statsRes.hpp"
#include "packetIn.hpp"

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

// These templates will be used to generate the table latter on. 
// This template provides a convient templet inline function 
// that all i need to do is pass a subclass of messageBase and
// a filename and the function below will expand to a function
// call for one of the message tpes that we plan to fuzz. 
#if 0
#define OF_MESSAGE_TYPE( name ) template<class T> \
    inline void name(const string& filename) { \
            messageBase* tmp = new T( filename ); \
            tmp -> name();                     \
            delete tmp;}
#include "messageType.inc"
#undef OF_MESSAGE_TYPE
#endif
int main(int argc, char* argv[])
{

    //    map<pair<string, string>, int> mymap;

    //mymap.insert(make_pair(make_pair("1","2"), 3)); //edited
    //cout << mymap[make_pair("1","2")];
    //    cout<<sizeof(Num_OF_Message_Types)<<endl;
    //    cout<<sizeof(Num_OF_Message)<<endl;
    // Makes sure that program received the correct args  
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
    if( inSet(args,"hello") )
    {
        Hello hello(ARGV2_filepath);
        if( inSet(args,"version") )
        {
            hello.version();
        }
        else if ( inSet(args,"type" ) )
        {
            hello.type();
        }
    }
    else if( inSet(args, "featureRes") )
    {
        FeatureRes featureres(ARGV2_filepath);
        if( inSet(args,"version") )
        {
            featureres.version();
        }
        else if (inSet(args,"capabilities") )
        {
            featureres.capabilities();
        }
    }
    else if( inSet(args, "barrierRes") )
    {
        BarrierRes barrierres(ARGV2_filepath);
        if( inSet(args, "version" ) )
        {
            barrierres.version();
        }
    }
    else if( inSet(args, "getConfigRes") )
    {
        GetConfigRes getconfigres(ARGV2_filepath);
        if( inSet(args, "version") )
        {
            getconfigres.version();
        }
    }
    else if( inSet(args, "statsRes") )
    {
        StatsRes statsres(ARGV2_filepath);
        if( inSet(args, "version") )
        {
            statsres.version();
        }
    }
    else
    {
        cout<<"ERROR: No Definition"<<endl;
    }
}

void makeDirectory(const char* filename)
{
    if( (mkdir(filename,0777) != 0) && (errno != EEXIST ))
    {
        cout<<"ERROR: "<<filename<<": "<<std::strerror(errno)<<endl;
        exit(errno);
    }
}
