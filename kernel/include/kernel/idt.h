#ifndef _IDT_H_
#define _IDT_H_

void IDT_INIT();
void exceptionHandler(void);
void IDT_Set_Discriptor(uint8_t vector, void *ist, uint8_t flags);

#endif 