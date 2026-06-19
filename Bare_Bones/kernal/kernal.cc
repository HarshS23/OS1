#include "String/string.hh"
#include "Terminal/terminal.hh"
#include "VGA/vga.hh"

//Kernal Main fuctions 
extern "C" void KernalMain(void){
    // initlize Terminal 
    TerminalInit();

    // Writing a string 
    TerminalWriteString("\n[OKAY] KERNAL RUNNING\n");
}

