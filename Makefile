DEPS = rps.h
HELPEROBJ = auth.o failonout.o parseqs.o returncodes.o gamefuncs.o

%.o: %.c $(DEPS)
	gcc -c $< -lsqlite3 -o $@


.PHONY: all
all: dbsetup join testlogin startwaiting stopwaiting waitingplayers joinplayer whereami play getoppdecision isnewturn license

join: join.c $(HELPEROBJ) $(DEPS)
	gcc join.c $(HELPEROBJ) -lsqlite3 -o join

testlogin: testlogin.c $(HELPEROBJ) $(DEPS)
	gcc testlogin.c $(HELPEROBJ) -lsqlite3 -o testlogin

startwaiting: startwaiting.c $(HELPEROBJ) $(DEPS)
	gcc startwaiting.c $(HELPEROBJ) -lsqlite3 -o startwaiting

stopwaiting: stopwaiting.c $(HELPEROBJ) $(DEPS)
	gcc stopwaiting.c $(HELPEROBJ) -lsqlite3 -o stopwaiting

dbsetup: dbsetup.c $(DEPS)
	gcc dbsetup.c -lsqlite3 -o dbsetup

waitingplayers: waitingplayers.c $(HELPEROBJ) $(DEPS)
	gcc waitingplayers.c $(HELPEROBJ) -lsqlite3 -o waitingplayers

joinplayer: joinplayer.c $(HELPEROBJ) $(DEPS)
	gcc joinplayer.c $(HELPEROBJ) -lsqlite3 -o joinplayer

whereami: whereami.c $(HELPEROBJ) $(DEPS)
	gcc whereami.c $(HELPEROBJ) -lsqlite3 -o whereami

play: play.c $(HELPEROBJ) $(DEPS)
	gcc play.c $(HELPEROBJ) -lsqlite3 -o play

getoppdecision: getoppdecision.c $(HELPEROBJ) $(DEPS)
	gcc getoppdecision.c $(HELPEROBJ) $(DEPS) -lsqlite3 -o getoppdecision

isnewturn: isnewturn.c $(HELPEROBJ) $(DEPS)
	gcc isnewturn.c $(HELPEROBJ) -lsqlite3 -o isnewturn

license: license.c $(DEPS)
	gcc license.c -o license
