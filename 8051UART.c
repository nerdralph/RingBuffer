// 2020 Ralph Doncaster
// 8051 UART ring buffer for sdcc with ring buffer in iram
// 202008 untested beta
#include <8051.h>
#include "ringbuffer.h"

// UART RX ISR in 31 bytes - RingInit must be called from main
void Uart0_ISR(void) __interrupt (SI0_VECTOR) __naked
{
    __asm
    jb ti, 04$                          // ignore transmit interrupt 
    push psw
    push a
    mov	a, _ringHead
    add	a, #(_gRingBuf)
   	xch	a, r0
    mov	@r0, sbuf                       // save received byte
    xch	a, r0
    inc _ringHead
    anl	_gRingBuf, #(RINGBUFSIZE - 1)
03$:
    clr ri                              // clear interrupt flag
    pop a
    pop psw
04$:
    clr ti
    reti
    __endasm;
}
