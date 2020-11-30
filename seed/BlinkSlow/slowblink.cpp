#include <cstring>
#include "daisy_seed.h"

static daisy::DaisySeed hw;

int main(void)
{
    bool state = false;
    hw.Configure();
    hw.Init();
    for(;;)
    {
        hw.SetLed(state);
        state = !state;
        dsy_system_delay(500);
    }
}
