SHELL = /bin/bash -e
INC = -I ../inc/
CFLAGS = -Wall 
OPTS =
CXX = g++ $(CFLAGS) $(OPTS) $(INC)
PARTS = $(shell /bin/ls -1Ad * | grep -v 'Makefile')
DEBUG = 
default: libs

debug: CXX += -DDEBUG -g
debug: DEBUG = debug
debug: libs

libs:
	@for i in $(PARTS); do make -C $$i $(DEBUG); echo; done
	@echo

clean:
	@for i in $(PARTS); do make -C $$i clean; done
	@rm -f ${LIB}
