objects = metronome.o \
	  sound_management.o openal.o

metronome : $(objects) -lm -lsndfile -lopenal
	    cc -o metronome $(objects) -lm -lsndfile -lopenal

$(objects) : metronome.h -lm -lsndfile -lopenal

.PHONY : clean
clean :
	-rm metronome metronome.o sound_management.o openal.o
