SHELL = /bin/bash -e
INC = -I inc/
CXXFLAGS = -Wall 
OPTS =
CXX = g++ $(CXXFLAGS) $(OPTS) $(INC)
OBJ = 
AR = ar
DEBUG = 
LIBS = src
UNIT = testing
ALL = $(LIBS) testing
BIN = 
default: libs testing
debug: libs-debug testing-debug

libs-debug: CXX += -DDEBUG -g
libs-debug: DEBUG = debug
libs-debug: libs

libs:
	@for i in $(LIBS); do make -C $$i $(DEBUG); echo; done
	@echo

testing-debug: CXX += -DDEBUG -g
testing-debug: DEBUG = debug
testing-debug: testing

testing:
	@for i in $(UNIT); do make -C $$i $(DEBUG); echo; done
	@echo

clean:
	@for i in $(ALL); do make -C $$i clean; done
	@rm -f lib/*

copy:
	mkdir -p ~/src/data/EoCE/ll_oop_reimp
	cp -av /var/public/data/fall2013/EoCE/ll_oop_reimp/* ~/src/data/EoCE/ll_oop_reimp/

help:
	@echo
	@echo "*************[ recycled from Matt's datastructs class yo! ]*************"
	@echo "** make                     - build everything                        **"
	@echo "** make debug               - build everything with debug symbols     **"
	@echo "**                                                                    **"
	@echo "** make testing             - build unit tests                        **"
	@echo "** make testing-debug       - build unit tests with debugging symbols **"
	@echo "** make libs                - build all supporting libraries          **"
	@echo "** make libs-debug          - build all libraries with debug symbols  **"
	@echo "**                                                                    **"
	@echo "** make clean               - clean; remove all objects/compiled code **"
	@echo "** make help                - this information                        **"
	@echo "************************************************************************"
