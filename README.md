# RingBuffer
a tiny ring buffer in C for embedded systems

This implemenation uses the full buffer capacity, with a simple data structure of a 1-byte head and tail index and an array.  The code conforms to the C99 standard, and is optimized for size (code and data). Compiled with avr-gcc 5.4.0 for an ATtiny13, rintgest compiles to 152 bytes of code.  The RingPut function is as simple as possible, and is ideal for use in a receive ISR.

## Usage
In one C file, declare a global RingBuffer gRingBuf:
'RingBuffer gRingBuf;'
To change the default buffer size from 16 bytes, define RINGBUFSIZE to a power of two.  The maximum size is 128 bytes.

