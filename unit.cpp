#include <iostream>
#include <cstdlib>
#include <cstring>
#include <windows.h>

/*
    To compile use C++11 standard due to usage of std::to_string(), thanks ;)
*/


#define SLEEP_TIME 1
#define DELAY 0

void fire();
void identify_self();
void read_unit_count();

void officer();
void soldier();
void last_soldier();

int ARMY_ID;
int UNIT_ID;
int UNIT_COUNT;

int argc;
char** argv;

HANDLE UnitCreatedCallbackEvent; // OPEN
HANDLE UnitFireCallbackEvent; // CREATE
HANDLE NextUnitCreatedEvent; //CREATE
HANDLE NextUnitFireEvent; // OPEN

int main(int _argc , char** _argv)
{
    // Globals initialization

    argc = _argc;
    argv = _argv;

    // Initializes ARMY_ID and UNIT_ID and sets prompt color

    identify_self();


    if (UNIT_ID == 1) officer();
    else if (UNIT_ID == UNIT_COUNT) last_soldier();
    else soldier();






    Sleep(SLEEP_TIME);

    SetEvent( UnitFireCallbackEvent );

    for (int i = 1; i < UNIT_ID; i++) Sleep(SLEEP_TIME);

    fire();

    CloseHandle(UnitCreatedCallbackEvent);
    CloseHandle(UnitFireCallbackEvent);
    CloseHandle(NextUnitCreatedEvent);
    CloseHandle(NextUnitFireEvent);

    return 0;
}

void identify_self()
{
    // Check if i am an officer

    if (argc == 1)
    {
        // Officer code

        // Sets prompt to yellow on blue

        system("@color 1E");

        srand(GetTickCount());

        ARMY_ID = rand();

        UNIT_ID = 1;

        read_unit_count();

    }

    else
    {
        // Soldier code

        // Sets prompt to white on red

        system("@color 47");

        ARMY_ID = atoi(argv[1]);

        UNIT_ID = atoi(argv[2]);

        UNIT_COUNT = atoi(argv[3]);

    }
}

void soldier()
{
    UnitFireCallbackEvent = CreateEvent(
                                    NULL,
                                    TRUE,
                                    FALSE,
                                    ("AID_" + std::to_string(ARMY_ID) + "_UID_" + std::to_string(UNIT_ID) + "_FIRE").c_str()
                                    );

    UnitCreatedCallbackEvent = OpenEvent(
                                         EVENT_ALL_ACCESS,
                                         FALSE,
                                         ("AID_" + std::to_string(ARMY_ID) + "_UID_" + std::to_string(UNIT_ID) + "_CREATE").c_str()
                                         );

    SetEvent( UnitCreatedCallbackEvent );

    NextUnitCreatedEvent = CreateEvent(
                                       NULL,
                                       TRUE,
                                       FALSE,
                                       ("AID_" + std::to_string(ARMY_ID) + "_UID_" + std::to_string(UNIT_ID + 1) + "_CREATE").c_str()
                                       );

    ShellExecute(
                 NULL,
                 NULL,
                 argv[0],
                 (std::to_string(ARMY_ID) + " " + std::to_string(UNIT_ID + 1) + " " + std::to_string(UNIT_COUNT)).c_str(),
                 NULL,
                 SW_SHOWDEFAULT
                 );

    WaitForSingleObject(
                        NextUnitCreatedEvent,
                        INFINITE
                        );

    NextUnitFireEvent  = OpenEvent(
                                   EVENT_ALL_ACCESS,
                                   FALSE,
                                   ("AID_" + std::to_string(ARMY_ID) + "_UID_" + std::to_string(UNIT_ID + 1) + "_FIRE").c_str()
                                   );

    WaitForSingleObject(
                        NextUnitFireEvent,
                        INFINITE
                        );
}

void last_soldier()
{
    UnitFireCallbackEvent = CreateEvent(
                                    NULL,
                                    TRUE,
                                    FALSE,
                                    ("AID_" + std::to_string(ARMY_ID) + "_UID_" + std::to_string(UNIT_ID) + "_FIRE").c_str()
                                    );

    UnitCreatedCallbackEvent = OpenEvent(
                                         EVENT_ALL_ACCESS,
                                         FALSE,
                                         ("AID_" + std::to_string(ARMY_ID) + "_UID_" + std::to_string(UNIT_ID) + "_CREATE").c_str()
                                         );

    SetEvent( UnitCreatedCallbackEvent );

    Sleep(DELAY);

}

void officer()
{
    UnitFireCallbackEvent = CreateEvent(
                                    NULL,
                                    TRUE,
                                    FALSE,
                                    ("AID_" + std::to_string(ARMY_ID) + "_UID_" + std::to_string(UNIT_ID) + "_FIRE").c_str()
                                    );

    NextUnitCreatedEvent = CreateEvent(
                                       NULL,
                                       TRUE,
                                       FALSE,
                                       ("AID_" + std::to_string(ARMY_ID) + "_UID_" + std::to_string(UNIT_ID + 1) + "_CREATE").c_str()
                                       );

    ShellExecute(
                 NULL,
                 NULL,
                 argv[0],
                 (std::to_string(ARMY_ID) + " " + std::to_string(UNIT_ID + 1) + " " + std::to_string(UNIT_COUNT)).c_str(),
                 NULL,
                 SW_SHOWDEFAULT
                 );

    WaitForSingleObject(
                        NextUnitCreatedEvent,
                        INFINITE
                        );

    NextUnitFireEvent  = OpenEvent(
                                   EVENT_ALL_ACCESS,
                                   FALSE,
                                   ("AID_" + std::to_string(ARMY_ID) + "_UID_" + std::to_string(UNIT_ID + 1) + "_FIRE").c_str()
                                   );

    WaitForSingleObject(
                        NextUnitFireEvent,
                        INFINITE
                        );
}

void fire()
{
    long time = GetTickCount();

    std::cerr
              << "----------------------------------------------\n"
              << "----------------------------------------------\n"
              << "  Unit "
              << UNIT_ID
              << " of army "
              << ARMY_ID
              << " reporting for duty.\n"
              << "----------------------------------------------\n"
              << "  Current time is "
              << time
              << ".\n"
              << "----------------------------------------------\n"
              << "  3...\n      2...\n          1...\n              FAIYAAAA!!!!\n"
              << "----------------------------------------------\n";

    system("PAUSE >NUL");
}

void read_unit_count()
{
    std::cerr
              << "----------------------------------------------\n"
              << "----------------------------------------------\n"
              << "  Officer of army "
              << ARMY_ID
              << " reporting for duty.\n"
              << "----------------------------------------------\n"
              << "  How many rounds we require general?: ";
    std::cin
            >> UNIT_COUNT;
}
