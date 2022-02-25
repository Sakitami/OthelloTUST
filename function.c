int queryExsist(int a[20], int num) {
	static int _i, _exist = -1;
	for (_i = 0; _i < 20; _i++) {
		if (a[_i] == num) {
			_exist = _i;
			break;
		}
	}
	if (_exist >= 0) {
		return 1;
	}
	else {
		return 0;
	}
}