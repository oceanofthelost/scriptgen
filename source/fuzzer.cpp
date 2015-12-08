#include "fuzzer.h" 

#include <random>
#include <string>
using namespace std;

static unsigned seed = chrono::system_clock::now().time_since_epoch().count();
static default_random_engine generator(seed);
static uniform_int_distribution<uint8_t>  ran8Bit (0,UINT8_MAX);
static uniform_int_distribution<uint16_t> ran16Bit(0,UINT16_MAX);
static uniform_int_distribution<uint32_t> ran32Bit(0,UINT32_MAX);
static uniform_int_distribution<uint64_t> ran64Bit(0,UINT64_MAX);

int8_t Fuzz8Bit()
{
    return ran8Bit(generator);
}

uint16_t Fuzz16Bit()
{
    return ran16Bit(generator);
}
uint32_t Fuzz32Bit()
{
    return ran32Bit(generator);
}
uint64_t Fuzz64Bit()
{
    return ran64Bit(generator);
}

uint64_t FuzzNBit(uint8_t bits)
{
    assert(bits<=64);
    uniform_int_distribution<uint64_t> ranNBit(0,pow(2,bits)-1);
    return ranNBit(generator);
}

string FuzzString(uint64_t length)
{
    string result;
    for(uint64_t i = 0; i< length; i++)
    {
        result = result + (char)Fuzz8Bit();
    }
    return result;
}