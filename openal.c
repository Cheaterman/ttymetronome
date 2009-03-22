#include "metronome.h"

int
start_al(void)
{
    ALCdevice* output = alcOpenDevice(NULL);
    
    if(!output)
        return 1;
    
    ALCcontext* world = alcCreateContext(output, NULL);
    
    if(!world)
        return 1;
    if(!alcMakeContextCurrent(world))
        return 1;
    
    return 0;
}

void
stop_al(void)
{
    ALCcontext* world = alcGetCurrentContext();
    ALCdevice* output = alcGetContextsDevice(world);
    
    alcMakeContextCurrent(NULL);
    alcDestroyContext(world);
    alcCloseDevice(output);

    return;
}
