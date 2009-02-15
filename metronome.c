#include "metronome.h"

int
isalsa()
{
    if(system("which ossplay &> /dev/null"))
        return 1;
    else
        return 0;
}


void
bip(int alsa,int beat)
{

/*    float buffer[2048];
    SNDFILE *bip_pointer;
    SF_INFO bip_info;
    char bip[] = "bip.wav";

    bip_pointer = sf_open(bip,SFM_READ,&bip_info);
    sf_read_float(bip_pointer,buffer,2048);
    sf_close(bip_pointer);*/
    
    if(!alsa)
    {
        switch(beat)
        {
            case 1:    system("ossplay -q bip.wav &");    break;
            default:    system("ossplay -q bip-low.wav &");    break;
        }
    }
    else
    {
        switch(beat)
        {
            case 1:    system("aplay -q bip.wav &");    break;
            default:    system("aplay -q bip-low.wav &");   break;
        }
    }
    return;
}


void
main_loop(struct timespec *frequence,int alsa)
{

    int i;

    for(;;)
    {
        for(i = 1 ; i <= 4 ; ++i)
        {
            nanosleep(frequence, NULL);
            bip(alsa,i);
        }
    }
    return;
}

int
check_tempo(unsigned char tempo)
{
    if(tempo < 20 || tempo > 250)
        return 1;
    else
        return 0;
}

void
calc_freq(unsigned char tempo,struct timespec *frequence)
{

    double tempo_sec = (float)tempo / 60 , sec_par_beat = 1 / (float)tempo_sec;
    
    if(sec_par_beat >= 1)
    {
        frequence->tv_sec = floor(sec_par_beat);
        frequence->tv_nsec = (sec_par_beat - frequence->tv_sec) * 1000000000;
    }
    else
    {
        frequence->tv_sec = 0;
        frequence->tv_nsec = sec_par_beat * 1000000000;
    }
    return;
}


int
main(int argc,char *argv[])
{
    
    unsigned char tempo;
    struct timespec frequence;
    
    do
    {
        printf("Quel tempo ? (Minimum : 20, maximum : 250)\n");
        scanf("%u",&tempo);
        if(check_tempo(tempo))
            printf("Mauvais tempo. Saisissez un tempo compris entre 20 et 250.\n");
    } while(check_tempo(tempo));

    calc_freq(tempo,&frequence);

    main_loop(&frequence,isalsa());

    return 0;
}
