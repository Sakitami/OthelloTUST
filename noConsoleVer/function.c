#include<time.h>

int queryExsist(int* arr, int num) {
	for (int i = 0; i < 20; i++)
		if (arr[i] == num) return 1;
	return 0;
}

int randomNumber(int max_num) {
    int a;
    srand((unsigned)time(NULL));
    a = rand() % max_num;
    return a;
}

int validNumber(int* arr) {
    int num = 0;
    for (int i = 0; i < 20; i++) {
        if (arr[i] == 0)continue;
        num++;
    }
    return num;
}