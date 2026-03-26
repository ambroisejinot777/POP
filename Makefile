# Definitions de macros

CXX      = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = project.cc game.cc brick.cc ball.cc paddle.cc message.cc tools.cc
OFILES   = $(CXXFILES:.cc=.o)

# Definition de la premiere regle

all: project

project.o : project.cc game.h
	$(CXX) $(CXXFLAGS) -c project.cc -o project.o

game.o : game.cc game.h message.h brick.h ball.h paddle.h
	$(CXX) $(CXXFLAGS) -c game.cc -o game.o

brick.o : brick.cc brick.h message.h
	$(CXX) $(CXXFLAGS) -c brick.cc -o brick.o

ball.o : ball.cc ball.h message.h
	$(CXX) $(CXXFLAGS) -c ball.cc -o ball.o

paddle.o : paddle.cc paddle.h message.h
	$(CXX) $(CXXFLAGS) -c paddle.cc -o paddle.o

message.o : message.cc message.h
	$(CXX) $(CXXFLAGS) -c message.cc -o message.o

tools.o : tools.cc tools.h
	$(CXX) $(CXXFLAGS) -c tools.cc -o tools.o

project : $(OFILES)
	$(CXX) $(OFILES) -o projet


# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ project


# DO NOT DELETE THIS LINE -- make depend depends on it.
project.o: project.cc game.h message.h brick.h tools.h ball.h constants.h
game.o: game.cc game.h message.h brick.h tools.h ball.h constants.h
brick.o: brick.cc brick.h tools.h message.h
ball.o: ball.cc ball.h constants.h tools.h message.h
paddle.o: paddle.cc paddle.h tools.h message.h
message.o: message.cc message.h
tools.o: tools.cc tools.h
