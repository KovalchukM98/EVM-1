FLAGS += -Wall -Werror --std=c++17
USER_DIR_S = build
EXECUTABLE = bin/program

.PHONY: all clean

$(EXECUTABLE): $(USER_DIR_S)/main.o $(USER_DIR_S)/libsc.a
	g++ $(FLAGS) -o $@ $^ -Lbuild -lsc

$(USER_DIR_S)/main.o: src/main.cpp
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/sc.o: src/header/sc.cpp
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libsc.a: $(USER_DIR_S)/sc.o
	ar rc $(USER_DIR_S)/libsc.a $(USER_DIR_S)/sc.o

start:
	./bin/program

clean:
	rm -rf $(USER_DIR_S)/*.o
	rm -rf bin/*