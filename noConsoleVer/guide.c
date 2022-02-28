char* guideText(int step) {
	static char step1[] = "�ڰ��壨Ӣ�Reversi�����ֳƷ�ת�塢ƻ�����������壨Othello������һ��˫�˶��ĵ�������Ϸ��";
	static char step2[] = "���ӣ��ڰ�������ÿ���ɺڰ���ɫ��ɣ�һ��ף�һ��ڣ���64�����������������4���������ӳ�Բ���Ρ�\r\n���̣��ڰ���������64�����������ɣ���Ϸ����ʱ����Ҫ���ڸ��ڡ����̿ɷ�Ϊ���ǡ������ߡ��Լ����и������ֽ�����̶���8x8��Ϊ�ձ顣\r\n���ӣ���ʽ�����п���ʹ����������ѡ�ֵ�˼��ʱ�䡣����ʽ�ĶԾ���һ�㲻ʹ�����ӡ�";
	static char step3[] = "���̹���8��8�й�64��\r\n����ʱ�������������4�����÷źڰ������4ö���ӣ�������仯���ڷ��ã���\r\nͨ���������С�˫���������ӡ�ֻҪ���Ӻ���������һö������������һ�����ϣ��ᡢֱ��б�߽Կɣ������Է����ӣ����ܽ��Է�����Щ����ת��Ϊ�Ҽ��������漴�ɣ���\r\n�������һλ�����Ӷ����ܼ�ס���ֵ���һ�����ӣ���Ҫ�ö������ӡ�\r\n��˫���Բ�������ʱ����Ϸ�ͽ������Ӷ��һ��ʤ";
	static char step4[] = "׼�������𣿽���������ʵս��ϰ��";
	switch (step) {
	case 1:
		return step1;
	case 2:
		return step2;
	case 3:
		return step3;
	case 4:
		return step4;
	}
	return step1;
}

char* guideTitleText(int _step) {
	static char title1[] = "Reversi�ڰ���";
	static char title2[] = "�������...(��1������3��)";
	static char title3[] = "���ڹ���...(��2������3��)";
	static char title4[] = "��ʼ�̳�...(��3������3��)";
	switch (_step) {
	case 1:
		return title1;
	case 2:
		return title2;
	case 3:
		return title3;
	case 4:
		return title4;
	}
	return title1;
}
