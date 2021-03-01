FLAGS += -Wall -Werror --std=c++17
USER_DIR_S = build
EXECUTABLE = bin/program

.PHONY: all clean start

$(EXECUTABLE): $(USER_DIR_S)/main.o $(USER_DIR_S)/libsc.a $(USER_DIR_S)/libmyTerm.a $(USER_DIR_S)/libmyBigChars.a $(USER_DIR_S)/libprint.a
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

$(USER_DIR_S)/myBigChars.o: src/header/myBigChars.cpp
	g++ $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libmyBigChars.a: $(USER_DIR_S)/myBigChars.o
	ar rc $(USER_DIR_S)/libmyBigChars.a $(USER_DIR_S)/myBigChars.o

$(USER_DIR_S)/libprint.a: $(USER_DIR_S)/print.o
	ar rc $(USER_DIR_S)/libprint.a $(USER_DIR_S)/print.o

$(USER_DIR_S)/print.o: src/header/print.cpp
	g++ $(FLAGS) -c $^ -o $@

start:
	./bin/program

remake:
	make clean
	make
	make start

show_my_term:
	./myTerm.sh

clean:
	rm -rf $(USER_DIR_S)/*.o
	rm -rf bin/*
	rm -rf build/*
