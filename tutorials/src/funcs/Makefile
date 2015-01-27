CFLAGS = -Wall
INC = -I ../../inc
AR = ar
CXX = g++ $(CFLAGS) $(INC) 
SRC = $(shell /bin/ls -1 *.cc 2>/dev/null)
OBJ = $(SRC:.cc=.o)
LIB = $(shell /bin/pwd | /bin/sed 's/^.*\///')
all: $(SRC) $(OBJ) lib

debug: CXX += -DDEBUG -g
debug: DEBUG = debug
debug: $(SRC) $(OBJ) lib

.cc.o:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[B]   %-20s ... " "$<"
	@$(CXX) -c $< && echo "OK" || echo "FAIL"
else
	$(CXX) -c $<
endif

lib:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[L]   %-20s ... " "$<"
	@$(AR) rcs ../../lib/lib$(LIB).a $(OBJ) && echo "SUCCESS" || echo "FAIL"
else
	$(AR) rcs ../../lib/lib$(LIB).a $(OBJ)
endif


clean:
	rm -f *.o $(OBJ) core
