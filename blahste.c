/*
 * Copyright (c) 2024, Quantius Benignus
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @file blahste.c
 * @brief A simple X11 client to "fake/simulate" either "CTRL+V" key press or middle mouse button click.
 *
 * This program can be used in the 'wsi' script to immediatelly paste the transcribed text in the currently active window. 
 * If the Clipboard is used, the text will be pasted under the keyboard carret.
 * If the PRIMARY selection is used a middle mouse button click will be simulated and the text pasted at the position of the mouse pointer.
 * Compile with "gcc -Wall -O3 -I/usr/include/X11 blahste.c -o blahste -lX11 -lXtst" for example
 * Required libraries are typically preinstalled (on a X11 based desktop). They are libX11-dev and libXtst-dev.
 * Please, note that this simple code may not work across all keyboard layouts. In some edge cases, adjustments may be needed to the key codes.
 * 
 * @author Quantius Benignus
 * @date 2024/07/14
 */

#include <stdio.h>
#include <getopt.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

int main(int argc, char *argv[])
{
    Display *display;
    int major, f_event, f_err;
    int simulate_middle_click = 0;

    // Parse command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "p")) != -1) {
        switch (opt) {
            case 'p':
                simulate_middle_click = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-p]\n", argv[0]);
                return 1;
        }
    }

    display = XOpenDisplay(NULL);
    if (!display) {
        perror("Cannot open display");
        return 1;
    }
    
    if (!XQueryExtension(display, "XTEST", &major, &f_event, &f_err)) {
        perror("X11 XTEST extension is not available");
        return 1;
    }

    if (simulate_middle_click) {
        // Simulate the middle mouse button click
        XTestFakeButtonEvent(display, Button2, True, CurrentTime);
        XTestFakeButtonEvent(display, Button2, False, CurrentTime);
    } else {
        char vcode = XKeysymToKeycode(display, XK_V);
        char ccode = XKeysymToKeycode(display, XK_Control_L);
        // Simulate the "Control_L" key press
        XTestFakeKeyEvent(display, ccode, True, 0);
        // Simulate the "V" key press
        XTestFakeKeyEvent(display, vcode, True, 1);
        // Simulate the "V" key release
        XTestFakeKeyEvent(display, vcode, False, 1);
        // Simulate the "Control_L" key release
        XTestFakeKeyEvent(display, ccode, False, 1);
    }

    XFlush(display);

    if (XCloseDisplay(display) != 0) {
        perror("Failed to close display!\n");
        return 1;
    }
    
    return 0;
}
