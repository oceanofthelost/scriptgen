/*******************************************************************************
Name            : menu.h
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 11/19/2015
*******************************************************************************/
#ifndef MENU_ECS260
#define MENU_ECS260

#include <set>
#include <string>

extern std::set<std::string> OF_Messages;
extern std::set<std::string> OF_Message_Type;


void checkArgs(int, char**);
void printOFMessage();
void printOFMessageType();
bool inline inSet(const std::set<std::string>&, const std::string&);
bool validArgs(char**);

#endif
