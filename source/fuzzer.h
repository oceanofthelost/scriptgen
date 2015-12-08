/*******************************************************************************
Name            : fuzzer.h
Author          : Sean Alling
Version         : V0.1
Copyright       : 2015
Creation Date   : 12/7/2015
*******************************************************************************/
#ifndef FUZZER_ECS260
#define FUZZER_ECS260


#include <random>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <string>
#include <chrono>
using namespace std;

int8_t Fuzz8Bit();
uint16_t Fuzz16Bit();
uint32_t Fuzz32Bit();
uint64_t Fuzz64Bit();
uint64_t FuzzNBit(uint8_t bits);
string FuzzString(unsigned length);

#endif