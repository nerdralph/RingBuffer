// Ralph Doncaster 2020
// ring buffer test returns 0 for pass, 255 for fail

#include "ringbuffer.h"

RingBuf gRingBuf;

volatile uint8_t testcount;

int main()
{
    RingInit();
    // try putting one more than buffer size
    uint8_t end = testcount + RINGBUFSIZE + 1;
    for (uint8_t i = 0; i <= end; i++) RingPut(i);
    int result = 0;
    while (RingCount()) result += RingGet();
    int goal = RINGBUFSIZE * (RINGBUFSIZE / 2 - 1) + (RINGBUFSIZE / 2);
    if (result == goal)
        return 0;
    else
        return 255;

}
