#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
    int interval; // time interval between clicks in milliseconds
    bool isRunning = false; // flag to indicate if the autoclicker is running
    
    cout << "Enter the time interval between clicks in milliseconds: ";
    cin >> interval;
    
    while (true) {
        if (GetAsyncKeyState(VK_F6) & 0x8000) { // check if F6 key is pressed
            isRunning = true;
        }
        
        if (GetAsyncKeyState(VK_F7) & 0x8000) { // check if F7 key is pressed
            isRunning = false;
        }
        
        if (isRunning) {
            // simulate left mouse button click
            INPUT input;
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            SendInput(1, &input, sizeof(INPUT));
            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            SendInput(1, &input, sizeof(INPUT));
            
            // wait for the specified interval before clicking again
            Sleep(interval);
            
            // prevent the system from going to sleep while the autoclicker is running
            SetThreadExecutionState(ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED | ES_CONTINUOUS);
        } else {
            // restore the system power settings if the autoclicker is not running
            SetThreadExecutionState(ES_CONTINUOUS);
        }
    }
    
    return 0;
}
