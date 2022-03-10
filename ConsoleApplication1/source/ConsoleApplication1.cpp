// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>



int main()
{
    DWORD ProcessID;
    HWND hwnd = FindWindowA(0, ("AssaultCube")); // We will be targetting AssaultCube
    GetWindowThreadProcessId(hwnd, &ProcessID);  // Retrieving the Process ID of assaultCube
    if (hwnd) {
        std::cout << ProcessID << std::endl;
    }
    else {
        std::cout << "unable to get processID" << std::endl;
        return EXIT_FAILURE;
    }
    //
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID); //Making a handle to the process
    
    uintptr_t playerStruct =0x57B0B8; //0x400000 + 0x0017B0B8 -- 40000 is the best address and 0017b0b8 is the offset to the player struct
    int localPlayer = 0;
    uintptr_t ammoOffset = 0x140;
    int ammo = 0;
    if (hProcess == 0) { //if we were not able to get the handle we abort
        std::cout << "OpenProcess failed, Error: " << std::dec << GetLastError() << std::endl;
        return EXIT_FAILURE;
    }
    
    //Follow the pointer to the playerStruct
    BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)playerStruct, &localPlayer, sizeof(localPlayer), NULL);
    std::cout << localPlayer << std::endl;

    //Access the ammo from the pointer result + the offset
    ReadProcessMemory(hProcess, (LPCVOID)(localPlayer + ammoOffset), &ammo, sizeof(ammo), NULL);
    if (rpmReturn == FALSE) {
        std::cout << "GetLast error: "<< std::dec << GetLastError() << std::endl;
        return EXIT_FAILURE;
    }
    //Print out the ammo
    std::cout << ammo << std::endl;
    CloseHandle(hProcess);

    

    return EXIT_SUCCESS;
}



