// Ralph Doncaster 2020
// ring buffer test returns 0 for pass, 255 for fail

#include "ringbuffer.h"

// use a volatile so the compiler doesn't optimize it away
volatile uint8_t testcount;

int main()
{
    // try putting one more than buffer size
    // buffer should wrap and end with a count of 1
    testcount = 0;
    uint8_t end = testcount + RINGBUFSIZE + 1;
    for (uint8_t i = 0; i < end; i++) RingPut(i);

    if (RingCount() == 1 && RingGet() == end-1)
        return 0;
    else
        return 255;
}
