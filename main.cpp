#include <cstdio>
#include <string>
#include <windows.h>

HANDLE ghSemaphore;

DWORD WINAPI ThreadProc(LPVOID);

int main() {
    system("@color 47");

    int THREADCOUNT;

    std::printf("---------------------------------------------------\n");
    std::printf("---------------------------------------------------\n");
    std::printf("How many fiery rockets we need, General?: ");
    std::scanf("%d", &THREADCOUNT);
    std::printf("---------------------------------------------------\n");

    HANDLE aThread[THREADCOUNT];
    DWORD ThreadID;
    int i;
    // Create semaphore with initial count of 0 and max count of MAX_SEM_COUNT

    ghSemaphore = CreateSemaphore(
                                  NULL,
                                  0,
                                  THREADCOUNT,
                                  NULL);
    if (ghSemaphore == NULL) {
        std::printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    // Create worker threads

    for (i = 0; i < THREADCOUNT; i++) {
        aThread[i] = CreateThread(
                                  NULL,
                                  0,
                                  (LPTHREAD_START_ROUTINE) ThreadProc,
                                  NULL,
                                  0,
                                  &ThreadID);
        if (aThread[i] == NULL) {
            std::printf("CreateThread error: %d\n", GetLastError());
            return 1;
        }
    }

    // 3... 2... 1... GO! all threads are commanded to run

    if (!ReleaseSemaphore(
                      ghSemaphore,
                      THREADCOUNT,
                      NULL))
    {
        std::printf("ReleaseSemaphore error: %d\n", GetLastError());
    }

    // Wait for all threads to terminate

    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

    // Close thread and semaphore handles

    for (i = 0; i < THREADCOUNT; i++)
        CloseHandle(aThread[i]);

    CloseHandle(ghSemaphore);

    return 0;
}

DWORD WINAPI ThreadProc(LPVOID lpParam) {

    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    //Try to enter semaphore gate.

    dwWaitResult = WaitForSingleObject(
                                       ghSemaphore,
                                       INFINITE);

    // Fire on response

    system("start bin\\Release\\Soldier.exe");

    return 0;

}
