#ifndef _TERMINAL_H_
#define _TERMINAL_H_


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void TerminalInit(void);
void TerminalSetColour(uint8_t Colour);
void Terminal_Put_Entry_At(char C, uint8_t Color, size_t x, size_t y);
void Terminal_Put_Char(char c);
void TerminalWrite(const char* data, size_t size);
void TerminalWriteString(const char* data);


#endif