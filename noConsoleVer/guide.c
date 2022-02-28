char* guideText(int step) {
	static char step1[] = "黑白棋（英语：Reversi），又称翻转棋、苹果棋或奥赛罗棋（Othello），是一种双人对弈的棋类游戏。";
	static char step2[] = "棋子：黑白棋棋子每颗由黑白两色组成，一面白，一面黑，共64个（包括棋盘中央的4个）。棋子呈圆饼形。\r\n棋盘：黑白棋棋盘由64格的正方格组成，游戏进行时棋子要下在格内。棋盘可分为“角”、“边”以及“中腹”。现今的棋盘多以8x8较为普遍。\r\n棋钟：正式比赛中可以使用棋钟限制选手的思考时间。非正式的对局中一般不使用棋钟。";
	static char step3[] = "棋盘共有8行8列共64格。\r\n开局时，棋盘正中央的4格先置放黑白相隔的4枚棋子（亦有求变化相邻放置）。\r\n通常黑子先行。双方轮流落子。只要落子和棋盘上任一枚己方的棋子在一条线上（横、直、斜线皆可）夹著对方棋子，就能将对方的这些棋子转变为我己方（翻面即可）。\r\n如果在任一位置落子都不能夹住对手的任一颗棋子，就要让对手下子。\r\n当双方皆不能下子时，游戏就结束，子多的一方胜";
	static char step4[] = "准备好了吗？接下来进行实战演习！";
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
	static char title1[] = "Reversi黑白棋";
	static char title2[] = "关于棋具...(第1个，共3个)";
	static char title3[] = "关于规则...(第2个，共3个)";
	static char title4[] = "开始教程...(第3个，共3个)";
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
