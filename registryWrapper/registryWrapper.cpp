#include <iostream>
#include "wrapper.h"

int main()
{
    Wrapper CWrapper;
    CWrapper.RegWrite(L"HKCU\\SOFTWARE\\Example", L"MyValue", 0x666, REG_BINARY);

    return EXIT_SUCCESS;
}