FLAGS += -Wall -Werror --std=c++17
USER_DIR_S = build
EXECUTABLE = bin/program

.PHONY: all clean start

$(EXECUTABLE): $(USER_DIR_S)/main.o $(USER_DIR_S)/libsc.a
	g++ $(FLAGS) -o $@ $^ -Lbuild -lsc

$(USER_DIR_S)/main.o: src/main.cpp
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/sc.o: src/header/sc.cpp
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libsc.a: $(USER_DIR_S)/sc.o
	ar rc $(USER_DIR_S)/libsc.a $(USER_DIR_S)/sc.o

$(USER_DIR_S)/myTerm.o: src/header/myTerm.cpp
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libmyTerm.a: $(USER_DIR_S)/myTerm.o
	ar rc $(USER_DIR_S)/libmyTerm.a $(USER_DIR_S)/myTerm.o

start:
	./bin/program

remake:
	make clean
	make
	make start

clean:
	rm -rf $(USER_DIR_S)/*.o
	rm -rf bin/*