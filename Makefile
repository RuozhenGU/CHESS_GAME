#!/bin/bash
CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD -Werror=vla
EXEC = chess
OBJECTS = graphicaldisplay.o window.o board.o cell.o textdisplay.o score.o piece.o king.o queen.o knight.o bishop.o rook.o pawn.o player.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean




