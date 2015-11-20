/*******************************************************************************
Name            : scriptgen.cp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
Description     : Inspired by Kashyap Thimmaraju
*******************************************************************************/
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <set>
#include <sys/stat.h>
//#include <sys/types.h>

#include "menu.h"
#include "helloMessage.h"
#include "featReplyMessage.h"

using namespace std;

//create the directory structure that is  needed by this program
void createFolderStructure(char**);
void makeDirectory(const char*);
void createHelloReply(string);
void createHelloVersion(string);

// Gets rid of repetative code
template<class T>
inline void version(const string& filename)
{
    messageBase* tmp = new T( filename );
    tmp -> version();
    delete tmp;
}
template<class T>
inline void type(const string& filename)
{
    messageBase* tmp = new T( filename );
    tmp -> type();
    delete tmp;
}

int main(int argc, char* argv[])
{
    // Makes sure that program received the correct args
    checkArgs(argc, argv);

    //User sets this variable to the whatever directory they want to use. The rest of the
    // directory structure is derived off of the home directory.
    const string HOME = "./home/mininet";
    const string TESTSCRIPTS = HOME + "/fuzzing";
    const string ARGV1_filepath = TESTSCRIPTS + "/" + argv[1];
    const string ARGV2_filepath = ARGV1_filepath + "/" + argv[2];

    createFolderStructure(argv);
// This will go away when a table is used.
    set<string> args(argv+1, argv+3);

// This will change when the table method is implemented. Once all of this can be dynamicly loaded
// the table can be implemented.
    if( inSet(args,"hello") )
    {
        if( inSet(args,"version") )
        {
            version<Hello>(ARGV2_filepath);
        }
        else if ( inSet(args,"type" ) )
        {
            type<Hello>(ARGV2_filepath);
        }
    }
    else if( inSet(args, "featureRes") )
    {
        if( inSet(args,"version") )
        {
            version<FeatureResponse>(ARGV2_filepath);
        }
        else if ( inSet(args,"type" ) )
        {
            type<FeatureResponse> (ARGV2_filepath);
        }
    }
}

void createFolderStructure(char* argv[])
{
    const string HOME = "./home/mininet";
    const string TESTSCRIPTS = HOME + "/fuzzing";
    const string ARGV1_filepath = TESTSCRIPTS + "/" + argv[1];
    const string ARGV2_filepath = ARGV1_filepath + "/" + argv[2];

    makeDirectory( "./home" );
    makeDirectory( HOME.c_str() );
    makeDirectory( "./home/mininet/fuzzing" );
    makeDirectory( ARGV1_filepath.c_str() );
    makeDirectory( ARGV2_filepath.c_str());
}

void makeDirectory(const char* filename)
{
    cout<<filename<<endl;
    if( (mkdir(filename,0777) != 0) && (errno != EEXIST ))
    {
        cout<<"ERROR: "<<filename<<": "<<strerror(errno)<<endl;
        exit(errno);
    }
}
