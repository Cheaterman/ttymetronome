#include "metronome.h"

void
chargerSon(char* nomFichier,ALint* tampon)
{
    SF_INFO infosFichier;
    SNDFILE* fichier = sf_open(nomFichier,SFM_READ,&infosFichier);

    if(!fichier)
        printf("Impossible de charger le fichier son %s !\n",nomFichier);

    ALsizei nbSamples = (ALsizei)(infosFichier.channels * infosFichier.frames);
    ALsizei sampleRate = (ALsizei)(infosFichier.samplerate);
    ALshort samples[nbSamples];
    sf_read_short(fichier,samples,nbSamples);

    sf_close(fichier);

    ALenum type;
    switch(infosFichier.channels)
    {
        case 1:    type = AL_FORMAT_MONO16;    break;
        case 2:    type = AL_FORMAT_STEREO16;    break;
    }

    alGenBuffers(1,tampon);

    alBufferData(*tampon,type,samples,nbSamples * sizeof(ALushort), sampleRate);

    if(alGetError())
        printf("Erreur interne d'OpenAL !\n");
    
    return;
}
    
void
jouerSon(ALint* tampon,ALuint* source)
{
    if(!tampon)
        return;
    alSourcei(*source,AL_BUFFER,*tampon);
    alSourcePlay(*source);

    if(alGetError())
        printf("Erreur interne d'OpenAL !\n");

    return;
}

void
stopSon(ALuint* source)
{
    alSourceStop(*source);

    if(alGetError())
        printf("Erreur interne d'OpenAL !\n");

    return;
}
