#include "set.h"

#include <stdbool.h>

typedef struct {
	int setsLength;
	Set *sets;
	int id;
} Game;

void printGame(Game game);
Game parseGame(char *line);
bool isGamePossible(Game game, Set possibleSet);
Set minimalPossibleSet(Game game);
