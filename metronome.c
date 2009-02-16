#include "metronome.h"

int
isalsa()
{
    if(system("which ossplay &> /dev/null") && system("which aplay &> /dev/null")) // Ne trouve ni aplay ni ossplay
        return -1;
    else if(system("which ossplay &> /dev/null")) // Ne trouve pas ossplay
        return 1;
    else if(system("which aplay &> /dev/null")) // Ne trouve pas aplay
        return 0;
    else
    {
        printf("ALSA et OSS détectés : utilisation d'OSS par défaut.\n");
        return 0;
    }
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
    else if(alsa == 1)
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
main_loop(struct timespec *frequence,int alsa,int mesure)
{

    int i;

    if(alsa != -1)
    {
        for(;;)
        {
            for(i = 1 ; i <= mesure ; ++i)
            {
                nanosleep(frequence, NULL);
                bip(alsa,i);
            }
        }
    } else
        printf("Ce métronome a besoin d'aplay ou d'ossplay pour fonctionner.\n"
               "(Solution avec fichier de configuration et lecteur personnalisé à venir...)\n");
    return;
}

int
check_tempo(unsigned int tempo)
{
    if(tempo < 20 || tempo > 250)
        return 1;
    else
        return 0;
}

int
check_mesure(unsigned int mesure)
{
    if(mesure < 2 || mesure > 4)
        return 1;
    else
        return 0;
}

void
calc_freq(unsigned int tempo,struct timespec *frequence)
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

    unsigned int tempo = 0 , mesure = 0;
    struct timespec frequence;

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
        printf("Quel tempo ? (Minimum : 20, maximum : 250)\n");
        scanf("%u",&tempo);
        if(check_tempo(tempo))
            printf("Mauvais tempo. Saisissez un tempo compris entre 20 et 250.\n");
    }

    while(check_mesure(mesure))
    {
        printf("Mesures à combien de temps ? (2-4)\n");
        scanf("%u",&mesure);
        if(check_mesure(mesure))
            printf("Mauvais nombre de temps par mesure. Saisissez un nombre de temps par mesure compris entre 2 et 4.\n");
    }

    calc_freq(tempo,&frequence);
    main_loop(&frequence,isalsa(),mesure);

    return 0;
}
