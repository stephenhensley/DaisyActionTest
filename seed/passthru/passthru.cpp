#include <cstring>
#include "daisy_seed.h"

static daisy::DaisySeed hw;

void passthru(float **in, float **out, size_t size)
{
    memcpy(out, in, size * 2 * sizeof(in[0][0]));
}

int main(void)
{
    bool state = false;
    hw.Configure();
    hw.Init();
    hw.StartAudio(passthru);
    for(;;)
    {
        hw.SetLed(state);
        state = !state;
        dsy_system_delay(250);
    }
}
