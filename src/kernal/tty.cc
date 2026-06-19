#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <tty.hpp>

#include "vga.h"



size_t TerminalRow;
size_t TerminalColumn;
uint8_t TerminalColour;
uint16_t* TerminalBuffer = (uint16_t*) VGA_MEMORY;

void TerminalInit(void){
    TerminalRow = 0;
    TerminalColumn = 0;
    TerminalColour = vga_entry_color(VGA_LIGHT_GRAY, VGA_BLACK);

    for(size_t x = 0; x < VGA_WIDTH; x++){
        for(size_t y = 0; y < VGA_HEIGHT; y++){
            const size_t index = y * VGA_WIDTH + x; 
            TerminalBuffer[index] = vga_entry(' ', TerminalColour);
        }
    }

}

void TerminalSetColour(uint8_t Colour){
    TerminalColour = Colour;
}

void Terminal_Put_Entry_At(char C, uint8_t Color, size_t x, size_t y){
    const size_t index = y * VGA_WIDTH + x; 
    TerminalBuffer[index] = vga_entry(C, Color);
}

void Terminal_Put_Char(char c){
    Terminal_Put_Entry_At(c, TerminalColour, TerminalColumn, TerminalRow);
    if(++TerminalColumn == VGA_HEIGHT){
        TerminalColumn = 0;
        if(++TerminalRow == VGA_WIDTH){
            TerminalRow = 0;
        }
    }

    if(c == '\n'){
        TerminalRow++;
        TerminalColumn = 0;
    }


}

void TerminalWrite(const char* data, size_t size){
    
    for(size_t i = 0; i < size; i++){
        Terminal_Put_Char(data[i]);
    }
}

void TerminalWriteString(const char* data){
    TerminalWrite(data, strlen(data));

}


