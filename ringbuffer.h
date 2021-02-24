// Ralph Doncaster 2020
// small and efficient ring buffer for embedded systems written in C99 
// buffer size must be a power of 2 up to 128 bytes
// head and tail index range is 2* size 
// buffer is reset if put called when full
// empty condition is when the difference between head and tail == size
// 2020.08.12 v0.1
// 2020.12.19 v0.3 - dropped full check for improved speed

#include <stdint.h>

#ifndef RINGBUFSIZE
#define RINGBUFSIZE 16
#endif

extern uint8_t gRingBuf[RINGBUFSIZE];
// crt initializes globals to 0
static uint8_t ringHead;
static uint8_t ringTail;
static const uint8_t RINGBUFMASK = RINGBUFSIZE - 1;

static inline uint8_t RingCount()
{
    return (ringHead - ringTail);
}

static inline void RingPut(uint8_t val)
{
    gRingBuf[ringHead] = val;
    ringHead = (ringHead + 1) & RINGBUFMASK;
}

// RingCount() should be checked first; no error checking here
static inline uint8_t RingGet()
{
    const uint8_t mask = RINGBUFSIZE - 1;
    uint8_t data =  gRingBuf[ringTail];
    ringTail = (ringTail + 1) & RINGBUFMASK;

    return data;
}

