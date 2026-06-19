#ifndef _VGA_H
#define _VGA_H

#include <stdint.h>


// definitions 
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000


// Hardware Text mode color constants 
enum VGAColors {
    VGA_BLACK = 0,
    VGA_BLUE = 1, 
    VGA_GREEN = 2,
    VGA_CYAN = 3, 
    VGA_RED = 4, 
    VGA_MAGENTA = 5, 
    VGA_BROWN = 6, 
    VGA_LIGHT_GRAY = 7, 
    VGA_DARK_GRAY = 8, 
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10, 
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12, 
    VGA_LIGHT_MAGENTA = 13, 
    VGA_LIGHT_BROWN = 14, 
    VGA_LIGHT_WHITE = 15
};

static inline uint8_t vga_entry_color(enum VGAColors ForeGround, enum VGAColors BackGround){

    return ForeGround | (BackGround << 4 ); // shift background color value by 4 bits, then OR the Foreground color to the back 
    // of the byte. therefore we get both color information in 1 byte 
    // ex. background  = 0, foreground = 1, then background = 0000 (black) 0001 (blue) --> 0000 00001

}

static inline uint16_t vga_entry(unsigned char uc , uint8_t colour){
    return (uint16_t) uc | (uint16_t) (colour << 8);

}

#endif