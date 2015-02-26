CFLAGS = -Wall -L../lib `sdl2-config --libs --cflags` -lSDL2_gfx -lSDL2_image
INC = -I ../inc/
CXX = g++ $(INC)
SRC = $(shell /bin/ls -1 *.cc 2>/dev/null)
BIN = $(SRC:.cc=)
all: $(SRC) $(BIN)

debug: CXX += -DDEBUG -g
debug: DEBUG = debug
debug: $(SRC) $(BIN)

.cc:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[B]   %-20s ... " "$<"
	@$(CXX) -o $@ $< $(CFLAGS) && echo "OK" || echo "FAIL"
else
	$(CXX) -o $@ $< $(CFLAGS)
endif

clean:
	rm -f *.o $(BIN) core
