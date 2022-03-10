// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <Windows.h>
#include <iostream>
#include <string>
#include "logger.h"



int main()
{
    DWORD ProcessID;
    HWND hwnd = FindWindowA(0, ("AssaultCube")); // We will be targetting AssaultCube
    GetWindowThreadProcessId(hwnd, &ProcessID);  // Retrieving the Process ID of assaultCube
    if (hwnd) {
        logOut(ProcessID);
    }
    else {
        logOut("unable to get processID");
        
        return EXIT_FAILURE;
    }
    //
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID); //Making a handle to the process
    
    uintptr_t playerStruct =0x57B0B8; //0x400000 + 0x0017B0B8 -- 40000 is the best address and 0017b0b8 is the offset to the player struct
    int localPlayer = 0;
    uintptr_t ammoOffset = 0x140;
    uintptr_t ammoAddress = playerStruct + ammoOffset;
    int ammo = 0;
    if (hProcess == 0) { //if we were not able to get the handle we abort
        logOut("OpenProcess failed, Error: " + GetLastError());
        return EXIT_FAILURE;
    }
    
    //Follow the pointer to the playerStruct
    BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)playerStruct, &localPlayer, sizeof(localPlayer), NULL);
    std::cout << localPlayer << std::endl;

    //Access the ammo from the pointer result + the offset
    ReadProcessMemory(hProcess, (LPCVOID)(localPlayer + ammoOffset), &ammo, sizeof(ammo), NULL);
    if (rpmReturn == FALSE) {
        logOut("GetLast error: " + GetLastError());
        return EXIT_FAILURE;
    }
    //Print out the ammo
    std::string s = "Player's carbine ammo: " + std::to_string(ammo);
    logOut(s);

    int newAmmo = 20;
    WriteProcessMemory(hProcess, (LPVOID)(localPlayer + ammoOffset), &newAmmo, sizeof(ammo), NULL);
    logOut("Player's carbine ammo has been set to: " + std::to_string(newAmmo));

    CloseHandle(hProcess);

    

    return EXIT_SUCCESS;
}


