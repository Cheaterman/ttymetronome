/* Rien qu'un tout petit programme pour tester time.h et son usage, voire définir des fonctions pour plus tard...

Ce code est intégralement sous license BSD.*/

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sndfile.h>
#include <AL/al.h>
#include <AL/alc.h>

int demar_al(void);
void stop_al(void);
void chargerSon(char* nomFichier,ALint* tampon);
void jouerSon(ALint* tampon,ALuint* source);
void stopSon(ALuint* source);
