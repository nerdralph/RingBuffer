// Ralph Doncaster 2020
// small and efficient ring buffer for embedded systems written in C99 
// buffer size must be a power of 2 up to 128 bytes
// head and tail index range is 2* size 
// full condition is head == tail, then any added are dropped
// empty condition is when the difference between head and tail == size
// 2020.08.12 v0.1

#include <stdint.h>

#ifndef RINGBUFSIZE
#define RINGBUFSIZE 16
#endif

typedef struct {
    uint8_t head;
    uint8_t tail;
    uint8_t buf[RINGBUFSIZE];
} RingBuf;

extern RingBuf gRingBuf;

inline void RingInit()
{
    //gRingBuf.tail = 0;                // crt zeros globals
    gRingBuf.head = RINGBUFSIZE;
}

inline uint8_t RingCount()
{
    // to understand the math behind RingCount
    // https://www.approxion.com/circular-adventures-viii-the-eternal-quest-for-mod-like-behavior/ 
    return (gRingBuf.head - gRingBuf.tail + RINGBUFSIZE) & (RINGBUFSIZE * 2 - 1);
}

inline void RingPut(uint8_t val)
{
    if (gRingBuf.head == gRingBuf.tail)
        return;                         // full
    gRingBuf.buf[gRingBuf.head & (RINGBUFSIZE -1)] = val;
    gRingBuf.head = (gRingBuf.head + 1) & (RINGBUFSIZE * 2 - 1);
}

// RingCount() should be checked first; no error checking here
inline uint8_t RingGet()
{
    uint8_t data =  gRingBuf.buf[gRingBuf.tail & (RINGBUFSIZE - 1)];
    gRingBuf.tail = (gRingBuf.tail + 1) & (RINGBUFSIZE * 2 - 1);
    return data;
}

