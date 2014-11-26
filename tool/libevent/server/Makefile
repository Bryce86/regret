INCLUDES=
LIBS=-L./ -levent
EXE=evtSrv
CC=gcc

all : $(EXE)

$(EXE) : service.c
	$(CC) $(INCLUDES) $^ -o $@ $(LIBS)

clean:
	rm -f $(EXE)
