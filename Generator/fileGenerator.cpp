/*******************************************************************************
Name            : barrierRes.hpp
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/

#include <string>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <fstream>
#include <set>
#include <cerrno>

using namespace std;


string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%m/%d/%Y", &tstruct);
    return buf;
}

void printHeader(ofstream& file, string input)
{
    string className = input + ".hpp";
    file<<"/*******************************************************************************"<<endl;
    file<<"Name"<<"            : "<<className<<endl;
    file<<"Author          : Sean Alling"   <<endl;
    file<<"Version         : V0.1"          <<endl;
    file<<"Copyright       : 2015"          <<endl;
    file<<"reation Date    : "<<currentDateTime()<<endl;
    file<<"*******************************************************************************/"<<endl;
}

void printHeaderGaurds(ofstream& file, string input)
{
    string ifndef = "#ifndef ";
    string define = "#define ";
    transform(input.begin(), input.end(), input.begin(), ::toupper);

    file<<ifndef + input + "_ECS260"<<endl;
    file<<define + input + "_ECS260"<<endl;
}
void printIncludes(ofstream& file)
{
    file<<"#include <string>"<<endl;
    file<<"#include \"fuzzer.h\""<<endl;
    file<<"#include \"messageBase.hpp\""<<endl;
}

void printClassStart(ofstream& file, string input)
{
    input[0] = toupper(input[0]);
    string className = "class " + input + " : public messageBase<" + input + ">";

    file<<className<<endl;
    file<<"{"       <<endl;
    file<<"\t"      <<"public:"<<endl;
    file<<"\t\t"    <<input<<"(std::string file)"<<endl;
    file<<"\t\t"    <<"{"<<endl;
    file<<"\t\t\t"  <<"filename=file;"<<endl;
    file<<"\t\t"   <<"};"<<endl;
    file<<"\t\t~"   <<input<<"(){};"<<endl;

}

void printClassEnd(ofstream& file)
{
    file<<"};"<<endl;
    file<<"#endif"<<endl;
}

void printFunction(ofstream& file, string input)
{
    string functionName = "void " + input +"()";

    file<<"\t\t"    <<functionName<<endl;
    file<<"\t\t"    <<"{"<<endl;
    file<<"\t\t\t"  <<"cout<<\"No User Definition\"<<endl;"<<endl;
    file<<"\t\t"    <<"}"<<endl;
}

void generate( const string& filename )
{
    string filepath = "./Generator/" + filename + ".hpp";
    ofstream write( filepath.c_str() );
    if( write.is_open() )
    {
        printHeader(write, filename);
        printHeaderGaurds(write, filename);
        printIncludes(write);
        printClassStart(write, filename);

        #define OF_MESSAGE_TYPE( messageType ) printFunction(write, #messageType);
        #include "messageType.inc"
        #undef OF_MESSAGE_TYPE
        printClassEnd(write);
    }
    else
    {
        std::cout<<"Can't open file"<<endl;
        exit(errno);
    }
    write.close();
}

void generateHeader()
{
    string filepath = "./Generator/OFMessages.h";
    ofstream write( filepath.c_str() );
    if( write.is_open() )
    {
        string inc = "#include \"";
        #define OF_MESSAGE( name ) write<<inc<<#name<<".hpp\""<<endl;
        #include "messages.inc"
        #undef OF_MESSAGE
    }
    else
    {
        std::cout<<"Can't open file"<<endl;
        exit(errno);
    }
    write.close();
}

int main()
{

    // Call the generate function for evry one of the OF messages. This will 
    // produce the *.hpp files/ 
    #define OF_MESSAGE( message ) generate( string( #message ) );
    #include "messages.inc"
    #undef OF_MESSAGE

    // Generate the header file that contains all of the aove *.hpp files.
    generateHeader();
}