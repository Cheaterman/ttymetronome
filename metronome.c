#include "metronome.h"

void
main_loop(struct timespec *frequence,int mesure,ALint *tampon_high, ALint *tampon_low)
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
                    case 1:    jouerSon(tampon_high,&source);
                               break;
                    default:    jouerSon(tampon_low,&source);
                }
                nanosleep(frequence, NULL);
                stopSon(&source);
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
                    case 1:    jouerSon(tampon_low,&source);
                               nanosleep(frequence, NULL);
                               stopSon(&source);
                               break;
                    case 2:    jouerSon(tampon_low,&source);
                               nanosleep(frequence, NULL);
                               stopSon(&source);
                               break;
                    case 3:    jouerSon(tampon_high,&source);
                               nanosleep(frequence, NULL);
                               stopSon(&source);
                               break;
                    case 4:    jouerSon(tampon_low,&source);
                               nanosleep(frequence, NULL);
                               stopSon(&source);
                               break;
                    case 5:    jouerSon(tampon_low,&source);
                               nanosleep(frequence, NULL);
                               stopSon(&source);
                               break;
                    case 6:    jouerSon(NULL,&source);
                               nanosleep(frequence, NULL);
                               stopSon(&source);
                               break;
                    case 7:    jouerSon(tampon_high,&source);
                               nanosleep(frequence, NULL);
                               stopSon(&source);
                               break;
                    case 8:    jouerSon(NULL,&source);
                               nanosleep(frequence, NULL);
                               stopSon(&source);
                               break;
                    default:    nanosleep(frequence, NULL);
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
calc_freq(unsigned int tempo,struct timespec *frequence,int mesure)
{

    if(mesure == 5)
        tempo *= 2;

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
    ALint tampon_high , tampon_low;

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
        printf("Quel tempo ? (Minimum : 20)\n");
        scanf("%u",&tempo);
        if(check_tempo(tempo))
            printf("Mauvais tempo. Saisissez un tempo supérieur à 20.\n");
    }

    while(check_mesure(mesure))
    {
        printf("Mesures à combien de temps ? (2-4, 5 mesure rythmée)\n");
        scanf("%u",&mesure);
        if(check_mesure(mesure))
            printf("Mauvais nombre de temps par mesure. Saisissez un nombre de temps par mesure compris entre 2 et 4 (ou 5 pour une mesure rythmée).\n");
    }

    demar_al();

    calc_freq(tempo,&frequence,mesure);
    
    chargerSon("bip.ogg",&tampon_high);
    chargerSon("bip-low.ogg",&tampon_low);

    main_loop(&frequence,mesure,&tampon_high,&tampon_low);

    stop_al();

    return 0;
}
