# RingBuffer
a tiny ring buffer in C for embedded systems

This implemenation uses the full buffer capacity, with a simple data structure of a 1-byte head and tail index and an array.  The code conforms to the C99 standard, and is optimized for size (code and data). For both AVR and 8051, rintgest compiles to less than 200 bytes of code.  The RingPut function is as simple as possible, and is ideal for use in a receive ISR.

8051UART.c contains an implementation of RingPut in a serial receive intterrupt handler using inline 8051 assembler.

## Usage
In one C file, define gRing and gRingBuf:
```c
RingBuf gRing;
uint8_t gRingBuf[RINGBUFSIZE];
```
A sample definition is in ringbuffer.c.  To change the default buffer size from 16 bytes, define RINGBUFSIZE to a power of two.  The maximum size is 128 bytes.
