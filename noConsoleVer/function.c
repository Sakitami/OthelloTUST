int queryExsist(int* arr, int num) {
	for (int i = 0; i < 20; i++)
		if (arr[i] == num) return 1;
	return 0;
}
