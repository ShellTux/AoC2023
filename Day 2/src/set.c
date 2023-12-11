#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
