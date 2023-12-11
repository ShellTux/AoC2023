#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RED_CODE "\033[31m"
#define GREEN_CODE "\033[32m"
#define BLUE_CODE "\033[34m"
#define RESET_CODE "\033[0m"

typedef struct {
	int blue;
	int green;
	int red;
} Set;

typedef struct {
	int setsLength;
	Set *sets;
	int id;
} Game;

void printSet(Set set)
{
	printf(
			"{ "
			RED_CODE
			"%d red"
			RESET_CODE
			", "
			GREEN_CODE
			"%d green"
			RESET_CODE
			", "
			BLUE_CODE
			"%d blue"
			RESET_CODE
			"}\n",
			set.red, set.green, set.blue);
}

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

Set parseSet(char *portion)
{
	Set set = {0};

	static const char delimiter[] = ", ";

	int i;
	int number;
	char color;

	for(
			portion = strtok(portion, delimiter), i = 0;
			portion != NULL;
			portion = strtok(NULL, delimiter), ++i
			) {
		if (i % 2 == 0) { // Number
			number = atoi(portion);
		} else {
			color = *portion;

			switch (color) {
				case 'r':
					set.red = number;
					break;
				case 'g':
					set.green = number;
					break;
				case 'b':
					set.blue = number;
					break;
			}
		}
	}

	return set;
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

int cubeConundrum(const char *filepath, Set possibleSet)
{
	int result = 0;

	FILE *stream;
	char *line = NULL;
	size_t length = 0;
	ssize_t nRead;

	stream = fopen(filepath, "r");
	if (stream == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while ((nRead = getline(&line, &length, stream)) != -1) {
		Game game = parseGame(line);

		if (!isGamePossible(game, possibleSet)) continue;

		result += game.id;
	}

	free(line);
	fclose(stream);

	return result;
}

int main(int argc, char *argv[])
{
	const char* inputFilePath = (argc >= 2)
		? argv[1]
		: "input";

	printf("Filename = %s\n", inputFilePath);

	Set possibleSet = {
		.red = 12,
		.green = 13,
		.blue = 14,
	};
	int result = cubeConundrum(inputFilePath, possibleSet);
	printf("Sum of possible games id = %d\n", result);

	return EXIT_SUCCESS;
}
