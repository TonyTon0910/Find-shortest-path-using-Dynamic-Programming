#include<stdio.h>

#define INT_MAX 2147483647
#define ARRAY_SIZE 10

int array[ARRAY_SIZE][ARRAY_SIZE];
int memo[ARRAY_SIZE][ARRAY_SIZE];
int color[ARRAY_SIZE][ARRAY_SIZE];

void generateRandomMartix() {
	srand(time(0));
	for (int i = 0; i < ARRAY_SIZE; ++i) {
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			array[i][j] = rand();
		}
	}
}
int findShortestPath(posX,posY) {
	//out of range
	if (posX < 0 || posY < 0)
		return INT_MAX;
	//set (0,0) is init value
	if (posX == 0 && posY == 0)
		return array[0][0];
	//memoization
	if (memo[posX][posY] != -1)
		return memo[posX][posY];
	//dynamic programming to find shortest paths
	int leftNum = findShortestPath(posX - 1, posY);
	int topNum = findShortestPath(posX, posY - 1);
	int total = (leftNum < topNum) ? leftNum + array[posX][posY] : topNum + array[posX][posY];
	memo[posX][posY] = total;
	return total;
}
void init() {
	for (int i = 0; i < ARRAY_SIZE; ++i) {
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			memo[i][j] = -1;//-1 means no data
			color[i][j] = 0;//0 means no color
		}
	}
}
void traceBackColor(posX, posY) {
	if (posX < 0 || posY < 0)
		return;
	color[posX][posY] = 1;
	return (findShortestPath(posX - 1, posY) < findShortestPath(posX, posY - 1)) ? traceBackColor(posX - 1, posY) : traceBackColor(posX, posY - 1);
}
int numOfLength(int num) {
	int count = 0;
	while (1) {
		num /= 10;
		count++;
		if (num == 0)
			return count;
	}
}
void printArray() {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++) {
			if(color[i][j] == 1)
				printf("\033[31m%d", array[i][j]);//red
			else
				printf("\033[37m%d", array[i][j]);//write

			for(int k = 0; k < 8 - numOfLength(array[i][j]); k++)//space
				printf(" ");
		}
		printf("\n");
	}
}
int main() {
	init();
	generateRandomMartix();
	//find shortest path from (0,0) to (ARRAY_SIZE - 1,ARRAY_SIZE - 1)
	findShortestPath(ARRAY_SIZE - 1,ARRAY_SIZE - 1);
	//color the shortest path
	traceBackColor(ARRAY_SIZE - 1, ARRAY_SIZE - 1);
	printArray();
}