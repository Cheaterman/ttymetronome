#include "metronome.h"

void
main_loop(struct timespec *frequency, int mesure, ALint *buffer_high, ALint *buffer_low)
{

    int i;
    ALuint source;
    alGenSources(1,&source);

    if(mesure != 5)
    {
        for(;;)
        {
            for(i = 1 ; i <= mesure ; ++i)
            {
                switch(i)
                {
                    case 1:    source_playbuffer(buffer_high,&source);
                               break;
                    default:    source_playbuffer(buffer_low,&source);
                }
                nanosleep(frequency, NULL);
                source_stop(&source);
            }
        }
    }
    else
    {
        for(;;)
        {
            for(i = 1 ; i <= 8 ; ++i)
            {
                switch(i)
                {
                    case 1:    source_playbuffer(buffer_low,&source);
                               nanosleep(frequency, NULL);
                               source_stop(&source);
                               break;
                    case 2:    source_playbuffer(buffer_low,&source);
                               nanosleep(frequency, NULL);
                               source_stop(&source);
                               break;
                    case 3:    source_playbuffer(buffer_high,&source);
                               nanosleep(frequency, NULL);
                               source_stop(&source);
                               break;
                    case 4:    source_playbuffer(buffer_low,&source);
                               nanosleep(frequency, NULL);
                               source_stop(&source);
                               break;
                    case 5:    source_playbuffer(buffer_low,&source);
                               nanosleep(frequency, NULL);
                               source_stop(&source);
                               break;
                    case 6:    source_playbuffer(NULL,&source);
                               nanosleep(frequency, NULL);
                               source_stop(&source);
                               break;
                    case 7:    source_playbuffer(buffer_high,&source);
                               nanosleep(frequency, NULL);
                               source_stop(&source);
                               break;
                    case 8:    source_playbuffer(NULL,&source);
                               nanosleep(frequency, NULL);
                               source_stop(&source);
                               break;
                    default:    nanosleep(frequency, NULL);
                }
            }
        }
    }
    
    return;
}

int
check_tempo(unsigned int tempo)
{
    if(tempo < 20 || tempo > 5000)
        return 1;
    else
        return 0;
}

int
check_mesure(unsigned int mesure)
{
    if(mesure < 2 || mesure > 5)
        return 1;
    else
        return 0;
}

void
calc_freq(unsigned int tempo, struct timespec *frequency, int mesure)
{

    if(mesure == 5)
        tempo *= 2;

    double tempo_sec = (float)tempo / 60 , sec_par_beat = 1 / (float)tempo_sec;

    if(sec_par_beat >= 1)
    {
        frequency->tv_sec = floor(sec_par_beat);
        frequency->tv_nsec = (sec_par_beat - frequency->tv_sec) * 1000000000;
    }
    else
    {
        frequency->tv_sec = 0;
        frequency->tv_nsec = sec_par_beat * 1000000000;
    }
    return;
}

int
main(int argc, char *argv[])
{

    unsigned int tempo = 0 , mesure = 0;
    struct timespec frequency;
    ALint buffer_high , buffer_low;

    if(argc >= 2)
    {
        if(!check_tempo((strtol(argv[1],NULL,10))))
            tempo = strtol(argv[1],NULL,10);
        if(argc >= 3)
            if(!check_mesure((strtol(argv[2],NULL,10))))
                mesure = strtol(argv[2],NULL,10);
    }

    while(check_tempo(tempo))
    {
        printf("What tempo ? (Minimum : 20)\n");
        scanf("%u",&tempo);
        if(check_tempo(tempo))
            printf("Bad tempo. Enter a tempo higher than 20.\n");
    }

    while(check_mesure(mesure))
    {
        printf("How many beats per mesure ? (2-4, 5 rythmic mesure)\n");
        scanf("%u",&mesure);
        if(check_mesure(mesure))
            printf("Bad amount of beats per mesure. Enter an amount of beats per mesure between 2 and 4 (or 5 for a rythmic mesure).\n");
    }

    start_al();

    calc_freq(tempo, &frequency,mesure);
    
    buffer_load("beep.ogg",&buffer_high);
    buffer_load("beep-low.ogg",&buffer_low);

    main_loop(&frequency,mesure,&buffer_high,&buffer_low);

    stop_al();

    return 0;
}
