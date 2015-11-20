Introduction:
The following program will generate *.ini files for OFCProbe. This is based off of the bash script by KASHYAP THIMMARAJU.

To create the executable open a terminal in the containing folder and type "make". This will build the program for your system. To generate the scripts use "./scriptgen X Y" where X and Y are arguments to scriptgen. To find a list of valid arguments type "./scriptgen" as this will make the program display all valid arguments.

If valid arguments are passed to scriptgen then it will generate OFCProbe *.ini files in the directory specified.

There are 3 files that determine how the program operates. They are as follows.

```
messages.inc: Format is as follows "OF_MESSAGE( X )". X contains a OpenFlow message type.

messageType.inc: Format is "OF_MESSAGE_TYPE( X )" where X is the name of one of the fields in a OF message.

params.inc: Format is "PARAM(X,Y,Z)". X is the type of parameter, Y is the name of the parameter, and Z is the default value for the parameter. There are currently 4 types of parameters, config, switchConfig, trafficGenConfig, and modules. Each of these parameters have there multiple parameters associated with them.
```

Expanding the abilities of the program requires little user intervention. If the user would like to add a new parameter then they can add it to the end of param.inc making sure that they fill out all of the required fields. Then run "make" again and now the scriptgen program will be able to generate *.ini files with that parameter. If the user would like to use a different version of the OpenFlow protocol, the user simply replaces the messages.inc with the pmessage names for the newer version of the OpenFlow protocol making sure that they use the same record format. Then run "make" and now scriptgen is configured to generate *.ini files for the newer OpenFlow protocol. The same procedure can be performed for messageType in order to add a new type to the scriptgen program.

Right now the user needs to generate a class that follows the below template in order to have scripgen generate *.ini files. The user will also have to add the header file for this class into the "scriptgen.cpp" file. If a user makes a change to how the system generate the *.ini files the user will have to rerun "make". This is a result of having everything statically linked.


TEMPLATE CLASS

XY.h

```c++
#ifndef XXX_MESSAGE_ECS260
#define XXX_MESSAGE_ECS260

#include <string>
#include "params.h"

class XXX
{
    private:
        std::string filename;
        void printConfig( std::string) ;
        config helloMsgConfig;
    public:
        XXX( std::string );
        void type( );
        void version( );
        ...
};
#endif
```

XY.cpp

```c++
#include "helloMessage.h"
#include <iostream>
#include <errno.h>
#include <stdlib.h>
#include <array>

void XXX::printConfig(string iniFilename)
{
    string filename_tmp = filename +"/"+ "of" +  iniFilename + ".ini";
    ofstream write ( filename_tmp ); // Write to a file
    if( write.is_open() )
    {
           XXXMsgConfig.print( write );
    }
    else
    {
        std::cout<<"Can't open file"<<endl;
        exit(errno);
    }
    write.close();
}

XXX::XXX(string passed)//(string filename)
{
    filename = passed;
}

void XXX::version()
{

}

void XXX::type()
{

}
```

XMessage where X is the name of the OF message for example hello. This would make the file name helloMessage. The first letter is always lowercase. XXX is replaced by the name of the OF message. So for example if this if for the hello message XXX will Hello with the first letter always capitalized. (XXX and XY need the specific alphabetic case for now since the build script is not set up to deal with them otherwise.)


Do not modify the printConfig function. This function generates the ini files. A must implement a function for each of the messageTypes that they want to fuzz. For example the original scriptgen scrip fuzzed version and type. The above program class  implements a function and defines in them the changes from the default config  struct. The config struct contains all of the parameters for the ini files. The user simply changes any of the config parameters and then call printConfig() when they are done making the changes to the config struct. The single argument for the printConfig is a string for the filename that ypu would like to have  the ini file to be named.

For an example implementation look at the helloMessage.h/.cpp and featReplyMessage.h/.cpp files.


NOTE: the config file parameters are accessed as follows.

to access the controllerAddress parameter use the following
config_controlerAddress = "some random address"

The struct is uses the data from the params file to auto generate it self. The param file entries are in the form PARAM( X, Y, Z )
to access any paramer the form of the variable name is X_Y = "whatever you want"
Each variable inside of config is of type string so when assigning a new value to the config struct make sure the RHS is a string object. This form is a little confusing at first but it makes it so the program can be easly modified by the user in trhe *.inc files and the build system will do the rest of the work to generate all of the other parts of the program.

Future Developments:

1. I plan to have the classes dynamically linked so that only the class files need to be recompiled and not the entire scriptgen program.

2. I also plan to make the build system auto detect what version of OF_probe is supplied to it. This way a user simply issues "make" and it will generate the correct version of scriptgen. The scriptgen generated will have _Vx appended to the executable. This will make it so that a user can quickly look at the executable and know for what version of scriptgen the program was compiled for.

3. I plan to clean up the files and organize them into directories. This way I can separate all the files that are needed for a building any of the scriptgen versions. For example there would be a V1, V2, V3 directory that contains the OF specific files for that versions and there would be a common directory that contains all of the files common across all versions of OF.

4. I plan to create a table that is used to look up the generating function for the *.ini files. This way if the user has defined the a generating function then a *.ini file will be created otherwise a error is print to the screen. This can be done by using a base class that each of the message classes overwrite. Then message classes inherit from the base class and overwrite its virtual function for the messageType that will have a custom ini file otherwise a warning is printed to the screen. (this works off the idea of virtual functions and polymorphism)
