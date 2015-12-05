#Introduction

The following program is used to generate the *.ini files used by OFCProbe. These *.ini files are used to pass configuration parameters to OFCProbe while it is running. I have based this C++ version of scriptgen off of the BASH version developed by Kashyap Thimmaraju. The C++ version makes it simple to add new config parameters to to add a new field to fuzz. 

#Folder Structure

.
├── Generator
│   ├── fileGenerator.cpp
│   └── *.ini
├── Makefile
├── README.md
├── settings
│   ├── messages.inc
│   ├── messageType.inc
│   └── params.inc
└── source
    ├── menu.cpp
    ├── menu.h
    ├── messageBase.hpp
    ├── parameters.h
    └── scriptgen.cpp

#Setup

To start using scriptgen there are three files that need t be set up. 

##Setup Files

1. messages.inc
* This file contains the names of the OF messages to fuzz.
*  Messages are in the following form. OF_MESSAGE(X). X is the OF message. The supported messages can be fund at the following http://flowgrammable.org/sdn/openflow/message-layer/.
2.  messagType.inc
* Message Type specifies the field of a OF message. These are the fields tat will be fuzzed. The following is the for specifying a messageType parameter. OF_MESSAGE_TYPE(X) where X is the name of the message field. 
3. params.inc
* This file contains the parameter names that are placed into the OFCProbe. All of these parameters have the following for. PARAM(PARAMETER TYPE ,NAME , PARAMETER VALUE ) PARAMETER TYPE is of type class of parameter, NAME is the name of the parameter, and PARAMETER VALUE is the default value of the parameter.
* Format is "PARAM(X,Y,Z)". X is the type of parameter, Y is the name of the parameter, and Z is the default value for the parameter. There are currently 4 types of parameters, config, switchConfig, trafficGenConfig, and modules. 
 
 A user manually fills in these files. After these files are created it is now possible to use the scriptgen program. 

#Usage

 1. Follow the steps in the setup section. 
 2. Open a terminal in the scriptgen directory. Type "make generate" into the terminal.
 3. Doing this will generate all of the source files that scriptgen need to compile. This command generates a C++ template class for each of the messages that are specified in messages.inc settings file. These C++ class files are placed into the "Generator" directory.
 4.  Now with the C++ class files generated the they can be configured to fuzz the correct field. Inside of each class file there are member functions that specify the field to fuzz. 
 * By default the config files that are generated will contain the default parameters that were specified in the params.inc settings file. 
 * A user can overwrite the parameters through the MsgParameter struct. The struct members are all of type string so when overwriting the MsgParameters make sure to set it equal to a string value. 
 5. With the functions filled in in the C++ classes for the OF messages reopen a terminal to the scriptgen directory. 
 6. Type "make" into the terminal. 
 7. Issuing the above commands will have compiled the scriptgen program. 
 8. To use scriptgen type "./scriptgen" and a menu will appear describing how to use it. 
 

#Adding New Parameters
Expanding the abilities of the program requires little user intervention. If the user would like to add a new parameter then they can add it to the end of param.inc making sure that they fill out all of the required fields. Then run "make" again and now scriptgen will be able to generate *.ini files with that parameter. If the user would like to use a different version of the OpenFlow protocol, the user simply replaces the messages.inc with the pmessage names for the newer version of the OpenFlow protocol making sure that they use the same record format. Then run "make" and now scriptgen is configured to generate *.ini files for the newer OpenFlow protocol. The same procedure can be performed for messageType in order to add a new type to the scriptgen program.

#Examples
There are example implementation of filling in the *.hp class files in ./OFMessages 


NOTE: the config file parameters are accessed as follows.

to access the controllerAddress parameter use the following
config_controlerAddress = "some random address"

The struct is uses the data from the params file to auto generate it self. The param file entries are in the form PARAM( X, Y, Z ) to access any paramer the form of the variable name is X_Y = "whatever you want"
Each variable inside of config is of type string so when assigning a new value to the config struct make sure the RHS is a string object. This form is a little confusing at first but it makes it so the program can be easly modified by the user in trhe *.inc files and the build system will do the rest of the work to generate all of the other parts of the program.

#Future Developments

1. Have the classes dynamically linked so that only the class files need to be recompiled and not the entire scriptgen program.

2. Make the build system auto detect what version of OF_probe is supplied to it. This way a user simply issues "make" and it will generate the correct version of scriptgen. The scriptgen executable will have _Vx appended to the executable. This will make it so that a user can quickly look at the executable and know for what version of scriptgen the program was compiled for.

3.Clean up the files and organize them into directories. This way all the files that are needed for building any of the scriptgen versions can be separated. For example there would be a V1, V2, V3 directory that contains the OF specific files for that versions and there would be a common directory that contains all of the files common across all versions of OF.

4. Create a table that is used to look up the generating function for the *.ini files. This way if the user has defined the a generating function then a *.ini file will be created otherwise a error is print to the screen. This can be done by using a base class that each of the message classes overwrite. Then message classes inherit from the base class and overwrite its virtual function for the messageType that will have a custom ini file otherwise a warning is printed to the screen. (this works off the idea of virtual functions and polymorphism)
