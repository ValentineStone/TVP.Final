#include <cstdio>
#include <windows.h>

#define MAX_SEM_COUNT 12
#define THREADCOUNT 12

HANDLE ghSemaphore;

DWORD WINAPI ThreadProc(LPVOID);

int main() {
    HANDLE aThread[THREADCOUNT];
    DWORD ThreadID;
    int i;

    // Create semaphore with initial and max counts of MAX_SEM_COUNT

    ghSemaphore = CreateSemaphore(
                                  NULL,
                                  MAX_SEM_COUNT,
                                  MAX_SEM_COUNT,
                                  NULL);
    if (ghSemaphore == NULL) {
        std::printf("CreateSemaphore error: %d\n",GetLastError());
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
            std::printf("CreateThread error: %d\n",GetLastError());
            return 1;
        }
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
    BOOL bContinue = TRUE;

    while(bContinue) {

        //Try to enter semaphore gate.

        dwWaitResult = WaitForSingleObject(
                                           ghSemaphore,
                                           INFINITE);
        switch (dwWaitResult) {

            // The semaphore object was signaled
            case WAIT_OBJECT_0:
                // TODO: Preform task
                std::printf("Thread %d: wait succeeded\n",GetCurrentThreadId());

                bContinue = FALSE;

                // Simulate thread spending time on task
                Sleep(500);

                // Release the semaphore when task is finished

                if (!ReleaseSemaphore(
                                      ghSemaphore,
                                      1,
                                      NULL)) {
                    std::printf("ReleaseSemaphore error: %d\n",GetLastError());
                }
                break;

            // The semaphore was nonsignaled, so a time-out occurred.
            case WAIT_TIMEOUT:
                std::printf("Thread %d: wait timed out\n",GetCurrentThreadId());
                break;
        }
    }
    return TRUE;

}
