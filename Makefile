objects = metronome.o \
	  jouer_son.o openal.o

metronome : $(objects) -lm -lsndfile -lopenal
	    cc -o metronome $(objects) -lm -lsndfile -lopenal

$(objects) : metronome.h -lm -lsndfile -lopenal

.PHONY : clean
clean :
	-rm metronome metronome.o jouer_son.o openal.o
