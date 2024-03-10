CC = g++
CFLAGS = -Wall -g


target = connectAgent

all : $(target)

$(target) : main.o
	$(CC) $(CFLAGS) --std c++11  -o $(target)  main.o #ssh-agent.o openSSHKey.o

main.o: main.cpp ssh-agent.h openSSHKey.h
	$(CC) $(CFLAGS) -c main.cpp

ssh-agent.o: ssh-agent.cpp ssh-agent.h #openSSHKey.h 
	$(CC) $(CFLAGS) -c ssh-agent.cpp

openSSHKey.o :  openSSHKey.cpp openSSHKey.h #config.h
#	$(CC) $(CFLAGS) -c opensSHKey.cpp

clean : 
	rm $(target) *.o

