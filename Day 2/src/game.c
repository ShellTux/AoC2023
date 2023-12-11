#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printGame(Game game)
{
	printf("Game: {\n");
	printf(
			"\tid: %d,\n"
			"\tsetsLength: %d\n",
			game.id,
			game.setsLength
	      );

	printf("\tsets: [\n");
	for (int i = 0 ; i < game.setsLength ; ++i) {
		Set set = game.sets[i];

		printf("\t\t");
		printSet(set);
	}
	printf("\t]\n");
	printf("}\n");
}

Game parseGame(char *line)
{
	Game game = {0};

	static const char gameDelimiter[] = ":";
	char *gameSlice = strtok(line, gameDelimiter);
	sscanf(gameSlice, "Game %d", &game.id);

	line = strtok(NULL, gameDelimiter);

	static const char setDelimiter[] = ";";
	char **setSlices = NULL;
	for (
			char *setSlice = strtok(line, setDelimiter);
			setSlice != NULL;
			setSlice = strtok(NULL, setDelimiter)
	    ) {
		game.sets = realloc(game.sets, ++game.setsLength * sizeof(Set));
		setSlices = realloc(
				setSlices,
				game.setsLength * sizeof(char *)
				);
		int setSliceLength = strlen(setSlice);
		int index = game.setsLength - 1;
		setSlices[index] = malloc((setSliceLength + 1) * sizeof(char));
		strncpy(setSlices[index], setSlice, setSliceLength);
	}

	for (int i = 0 ; i < game.setsLength ; ++i) {
		char *setSlice = setSlices[i];
		game.sets[i] = parseSet(setSlice);
	}

	return game;
}

bool isGamePossible(Game game, Set possibleSet)
{
	for (int i = 0 ; i < game.setsLength ; ++i) {
		Set set = game.sets[i];

		if (set.red > possibleSet.red) return false;
		if (set.green > possibleSet.green) return false;
		if (set.blue > possibleSet.blue) return false;
	}

	return true;
}

Set minimalPossibleSet(Game game)
{
	Set minimalSet = {0};

	for (int i = 0 ; i < game.setsLength ; ++i) {
		Set set = game.sets[i];

		if (set.red > minimalSet.red) minimalSet.red = set.red;
		if (set.green > minimalSet.green) minimalSet.green = set.green;
		if (set.blue > minimalSet.blue) minimalSet.blue = set.blue;
	}

	return minimalSet;
}
