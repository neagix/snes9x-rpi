
#ifndef S9XINPUT_H
#define	S9XINPUT_H

extern "C" {
    void S9xProcessEvents(bool block);
    void S9xInitInputDevices();
    void S9xCloseInputDevices();
//    uint32 S9xReadJoypad (int which1_0_to_4);
}

#endif	/* S9XINPUT_H */

