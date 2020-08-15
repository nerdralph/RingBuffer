// 2020 Ralph Doncaster
// 8051 UART ring buffer for sdcc
#include <8051.h>
#include "ringbuffer.h"

// UART RX ISR in 28 bytes - RingInit must be called from main
void Uart0_ISR(void) __interrupt (SI0_VECTOR) __naked
{
    __asm
    push psw
    push a
	mov	a, _gRing                       // head
	cjne a, (_gRing + 1),02$            // == tail?
    sjmp 03$                            // buffer full
02$:
    add	a, #(_gRingBuf)
   	xch	a, r0
    mov	@r0, sbuf                       // save received byte
    xch	a, r0
    inc _gRingBuf                       // increment head
    anl	_gRingBuf, #(RINGBUFSIZE * 2 - 1)
03$:
    clr ri                              // clear interrupt flag
    pop a
    pop psw
    ret
    __endasm;
}
