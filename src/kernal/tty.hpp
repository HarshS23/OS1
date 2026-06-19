#ifndef _KERNAL_TTY_H
#define _KERNAL_TTY_H

#include <stddef.h>

void TerminalInit(void);
void Terminal_Put_Char(char c);
void TerminalWrite(const char* data, size_t size);
void TerminalWriteString(const char* data);




#endif