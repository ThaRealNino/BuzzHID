#define MAX_STR 255
#define WINVER 0x0500

#include <stdio.h>
#include <iostream>
#include "hidapi.h"
#include "stdlib.h"
#include <windows.h>
#include "stdbool.h"

using namespace std;

void sendKeyInputNino(unsigned char key);

int main()
{
    int res;
    unsigned char buf[65];
    hid_device *handle;

    handle = hid_open(0x054c, 0x1000, NULL);

    hid_set_nonblocking(handle, 1);

    buf[0] = 0x00;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    buf[3] = 0xFF;
    buf[4] = 0xFF;
    buf[5] = 0xFF;

    hid_write(handle, buf, 6);

    while(true) {
        res = hid_read(handle, buf, 65);

        if(res < 0) {
            break;
        } else {

                if (!((int)buf[0]==0 && (int)buf[1]==0 && (int)buf[2]==0 && (int)buf[3]==0 && (int)buf[4]==240 && (int)buf[5]==255)){
                    if (!((int)buf[0]==0 && (int)buf[1]==255 && (int)buf[2]==255 && (int)buf[3]==255 && (int)buf[4]==255 && (int)buf[5]==255)){
                        if((int)buf[2]==1 && (int)buf[3]==0 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD0);
                        }
                        if((int)buf[2]==16 && (int)buf[3]==0 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD1);
                        }
                        if((int)buf[2]==8 && (int)buf[3]==0 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD2);
                        }
                        if((int)buf[2]==4 && (int)buf[3]==0 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD3);
                        }
                        if((int)buf[2]==2 && (int)buf[3]==0 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD4);
                        }
                        if((int)buf[2]==32 && (int)buf[3]==0 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD5);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==2 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD6);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==1 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD7);
                        }
                        if((int)buf[2]==128 && (int)buf[3]==0 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD8);
                        }
                        if((int)buf[2]==64 && (int)buf[3]==0 && (int)buf[4]==240) {
                            sendKeyInputNino(VK_NUMPAD9);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==4 && (int)buf[4]==240) {
                            sendKeyInputNino(0x30);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==64 && (int)buf[4]==240) {
                            sendKeyInputNino(0x31);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==32 && (int)buf[4]==240) {
                            sendKeyInputNino(0x32);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==16 && (int)buf[4]==240) {
                            sendKeyInputNino(0x33);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==8 && (int)buf[4]==240) {
                            sendKeyInputNino(0x34);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==128 && (int)buf[4]==240) {
                            sendKeyInputNino(0x35);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==0 && (int)buf[4]==248) {
                            sendKeyInputNino(0x36);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==0 && (int)buf[4]==244) {
                            sendKeyInputNino(0x37);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==0 && (int)buf[4]==242) {
                            sendKeyInputNino(0x38);
                        }
                        if((int)buf[2]==0 && (int)buf[3]==0 && (int)buf[4]==241) {
                            sendKeyInputNino(0x39);
                        }
                    }
            }
        }

        Sleep(300);
    }

    hid_close(handle);

    return 0;
}

void sendKeyInputNino(unsigned char key) {

        INPUT ip;
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        ip.ki.wVk = VK_CONTROL;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));

        ip.ki.wVk = key;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));

        ip.ki.wVk = key;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));

        ip.ki.wVk = VK_CONTROL;
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
}
