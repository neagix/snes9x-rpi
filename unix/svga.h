/* 
 * File:   sdlvideo.h
 * Author: neagix
 *
 * Created on January 20, 2013, 10:41 PM
 */

#ifndef SVGA_H
#define	SVGA_H

extern "C" {
    void S9xPerformUpdate(int x, int y, int w, int h);
    void S9xInitDisplay(int /*argc*/, char ** /*argv*/);
    void S9xDeinitDisplay();
}

#endif	/* RPIVIDEO_H */

