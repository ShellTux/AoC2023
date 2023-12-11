#ifndef __SET_H
#define __SET_H

#define RED_CODE "\033[31m"
#define GREEN_CODE "\033[32m"
#define BLUE_CODE "\033[34m"
#define RESET_CODE "\033[0m"

typedef struct {
	int blue;
	int green;
	int red;
} Set;

void printSet(Set set);
Set parseSet(char *portion);

#endif // !__SET_H
