#include "metronome.h"

int
demar_al(void)
{
    ALCdevice* sortie = alcOpenDevice(NULL);
    
    if(!sortie)
        return 1;
    
    ALCcontext* monde = alcCreateContext(sortie,NULL);
    
    if(!monde)
        return 1;
    if(!alcMakeContextCurrent(monde))
        return 1;
    
    return 0;
}

void
stop_al(void)
{
    ALCcontext* monde = alcGetCurrentContext();
    ALCdevice* sortie = alcGetContextsDevice(monde);
    
    alcMakeContextCurrent(NULL);
    alcDestroyContext(monde);
    alcCloseDevice(sortie);

    return;
}
