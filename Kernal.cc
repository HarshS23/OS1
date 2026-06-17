// Kernal Routines to set up memeory management, paging, etc

#include <stdbool.h>
#include <stddef.h>
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

// size_t represents integers in bytes 
size_t strlen(const char *str){
    size_t length = 0;
    while(*str != '\0'){
        length++;
        str++;
    }

    return length;
}


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

}

void TerminalWrite(const char* data, size_t size){
    
    for(size_t i = 0; i < size; i++){
        Terminal_Put_Char(data[i]);
    }
}

void TerminalWriteString(const char* data){
    TerminalWrite(data, strlen(data));

}


extern "C" void KernalMain(void){
    // initlize Terminal 
    TerminalInit();

    // Writing a string 
    TerminalWriteString("\n Kernal Output String");
}