#include <iostream>
#include <ctime>
#include <windows.h>

int main()
{
    long time = GetTickCount();

    system("@color 47");

    std::cout
              << "----------------------------------------------\n"
              << "----------------------------------------------\n"
              << "  Soldier #"
              << GetCurrentThreadId()
              << " reporting for duty.\n"
              << "----------------------------------------------\n"
              << "  Current time is "
              << time
              << ".\n"
              << "----------------------------------------------\n"
              << "  3...\n      2...\n          1...\n              FAIYAAAA!!!!\n"
              << "----------------------------------------------\n";

    std::cin.ignore();

    return 0;
}
