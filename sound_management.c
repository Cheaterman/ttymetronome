#include "metronome.h"

void
buffer_load(char* filename, ALint* buffer)
{
    SF_INFO file_infos;
    SNDFILE* file = sf_open(filename, SFM_READ, &file_infos);

    if(!file)
        printf("Unable to load the soundfile %s ! Ensure to be in the same directory as the ttymetronome binary.\n", filename);

    ALsizei sample_number = (ALsizei)(file_infos.channels * file_infos.frames);
    ALsizei samplerate = (ALsizei)(file_infos.samplerate);
    ALshort samples[sample_number];
    sf_read_short(file,samples,sample_number);

    sf_close(file);

    ALenum type;
    switch(file_infos.channels)
    {
        case 1:    type = AL_FORMAT_MONO16;    break;
        case 2:    type = AL_FORMAT_STEREO16;    break;
    }

    alGenBuffers(1,buffer);

    alBufferData(*buffer,type,samples,sample_number * sizeof(ALushort), samplerate);

    if(alGetError())
        printf("Internal OpenAL error !\n");
    
    return;
}
    
void
source_playbuffer(ALint* buffer,ALuint* source)
{
    if(!buffer)
        return;
    alSourcei(*source,AL_BUFFER,*buffer);
    alSourcePlay(*source);

    if(alGetError())
        printf("Internal OpenAL error !\n");

    return;
}

void
source_stop(ALuint* source)
{
    alSourceStop(*source);

    if(alGetError())
        printf("Internal OpenAL error !\n");

    return;
}
