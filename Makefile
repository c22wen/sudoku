CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = sudoku
OBJECTS = main.o cell.o game.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS}  ${DEPENDS}
