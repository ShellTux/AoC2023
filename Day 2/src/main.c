#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "set.h"
#include "game.h"

void cubeConundrum(
		const char *filepath,
		Set possibleSet,
		int *idPossibleSum,
		int *powerMinimalSum
		)
{
	*idPossibleSum = 0;
	*powerMinimalSum = 0;

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

		Set minimalSet = minimalPossibleSet(game);
		int power = minimalSet.red * minimalSet.green * minimalSet.blue;
		*powerMinimalSum += power;

		if (!isGamePossible(game, possibleSet)) continue;

		*idPossibleSum += game.id;
	}

	free(line);
	fclose(stream);
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

	int sum;
	int power;
	cubeConundrum(inputFilePath, possibleSet, &sum, &power);
	printf("Sum of possible games id = %d\n", sum);
	printf("Sum of power of minimal sets: %d\n", power);

	return EXIT_SUCCESS;
}
