#include<stdio.h>
#include<easyx.h>                 // EasyX图形绘制
#include<conio.h>
#include<mmstream.h>              // 包含多媒体设备接口头文件
#include "guide.c"                // 教程文本
#pragma comment(lib,"winmm.lib")  // 加载静态库

#define CLEARGREEN RGB(123,237,159)
#define CLEARORANGE RGB(243,156,18)
#define CLEARORANGERED RGB(230,126,34)


int chessman(int x, int y, int player);
int playerShow();
int startMenu();
int checkerBoard();
int playMain();

// 棋子生成函数
int chessman(int x, int y, int player)
{
	if (player == 0) {
		setfillcolor(BLACK);
	}
	else if(player == 1) {
		setfillcolor(WHITE);
	}
	else {
		setlinestyle(PS_DOT, 5);
		circle(x * 80 - 20, y * 80 - 20, 25);
		return 1;
	}
	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	solidcircle(x * 80 - 20, y * 80 - 20, 30);
	circle(x * 80 - 20, y * 80 - 20, 25);
	return 0;
}

// 清空棋盘中的某位置的棋子(清除辅助棋子)
int clearChessman(int x, int y)
{
	setfillcolor(CLEARGREEN);
	solidcircle(x * 80 - 20, y * 80 - 20, 30);
	return 0;
}

// 开始游戏界面绘制函数
int playerShow() {
	IMAGE player, titleBkground, step;
	loadimage(&player, "./image/player.png");                // 加载黑白棋右上角状态
	loadimage(&titleBkground, "./image/woolSut.jpg");        // 加载右侧背景图片
	putimage(715, 30, &titleBkground);
	putimage(715, 30, &player);
	settextcolor(BLACK);
	setfillcolor(WHITE);
	setlinecolor(WHITE);
	fillroundrect(715, 170, 1015, 210,10,10);
	settextstyle(20, 0, _T("黑体"), 0, 0, FW_BOLD, true, true, false, 0, 0, 0, 0, 0); // 设置字体样式
	outtextxy(730, 180, "剩余时间：");

	return 0;
}

// 绘制游戏菜单
int startMenu() {
	ExMessage msg;

	IMAGE startGame, gameGuide, AImode;
	loadimage(&startGame, "./image/start.png");
	loadimage(&gameGuide, "./image/guide.png");
	loadimage(&AImode, "./image/AImode.png");

	putimage(715, 170, &startGame);
	putimage(715, 310, &gameGuide);
	putimage(715, 450, &AImode);
	while (1) {
		if (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message) {
			case WM_MOUSEMOVE:
				loadimage(&startGame, "./image/start.png");
				loadimage(&gameGuide, "./image/guide.png");
				loadimage(&AImode, "./image/AImode.png");
				if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 170 && msg.y <= 290) {        // 判断鼠标是否位于“开始游戏”
					loadimage(&startGame, "./image/start_on.png");
				}
				else if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 310 && msg.y <= 430) {   // 判断鼠标是否位于“游戏教程”
					loadimage(&gameGuide, "./image/guide_on.png");
				}
				else if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 450 && msg.y <= 570) {   // 判断鼠标是否位于“人机对战”
					loadimage(&AImode, "./image/AImode_on.png");
				}
				putimage(715, 170, &startGame);
				putimage(715, 310, &gameGuide);
				putimage(715, 450, &AImode);
				break;
			case WM_LBUTTONDOWN:
				if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 170 && msg.y <= 290) {        
					return 1;   // 按下“开始游戏”执行操作1
				}
				else if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 310 && msg.y <= 430) {
					return 2;   // 按下“游戏教程”执行操作2
				}
				else if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 450 && msg.y <= 570) {
					return 3;   // 按下“人机对战”执行操作3
				}
			}
		}
	}

	return 0;
}

// 棋盘生成函数
int checkerBoard()
{
	IMAGE settingBkground, titleBkground;
	loadimage(&settingBkground, "./image/woolSut.jpg");
	loadimage(&titleBkground, "./image/title.png");
	char listNumber[9] = "abcdefgh";
	char lineNumber[9] = "12345678";
	setbkcolor(WHITE); cleardevice();                            // 设置背景颜色
	setfillcolor(CLEARGREEN);settextcolor(CLEARGREEN);           // 设置填充及文字颜色
	setlinestyle(PS_SOLID, 1); setlinecolor(WHITE);
	settextstyle(20, 0, _T("黑体"));
	fillroundrect(20, 20, 660, 660, 5, 5);                       // 加载棋盘背景
	// 绘制棋盘格子及行列号
	for (int i = 0,xPosition = 100,yPosition = 100; i <= 15; i++) {
		if (i <= 7) {
			line(20, xPosition, 660, xPosition);
			xPosition += 80;
			outtextxy(5, 50 + i * 80, lineNumber[i]);
			outtextxy(670, 50 + i * 80, lineNumber[i]);
		}
		else {
			if (i == 15) {
				outtextxy(620, 0, 'h');
				outtextxy(620, 660, 'h');
				break;
			}
			line(yPosition,20,yPosition,660);
			yPosition += 80;
			outtextxy(60 + (i - 8) * 80, 0, listNumber[i - 8]);
			outtextxy(60 + (i - 8) * 80, 660, listNumber[i - 8]);
		}
	}
	// 绘制初始游戏棋子
	chessman(4, 4, 1);chessman(5, 5, 1);
	chessman(4, 5, 0);chessman(5, 4, 0);
	putimage(700, 0, &settingBkground);
	putimage(715, 30, &titleBkground);

	// getchar();
	return 0;
}

// 游戏主函数s
int playMain() {
	IMAGE playerImage;
	loadimage(&playerImage, "./image/player.png");
	int time = 0, second = 59, minute = 9, onGame = 1;
	int player = 0;                                        // 黑方先手
	while (onGame) {
		setlinestyle(PS_SOLID, 7);

		// 倒计时
		if (time == 1000) {
			time = 0;
			if (second == 0 && minute != 0) {
				second = 59;
				minute -= 1;
			}
			else if (minute != 0) {
				second -= 1;
			}
			else if (minute == 0) {
				onGame = 0;
				continue;
			}
			setfillcolor(WHITE);
			setlinecolor(WHITE);
			fillroundrect(715, 170, 1015, 210, 10, 10);
			outtextxy(730, 180, "剩余时间：");
			outtextxy(850, 180, "分   秒");
			outtextxy(837, 180, (char)(minute+48));
			outtextxy(875, 180, (char)(second / 10 + 48));
			outtextxy(890, 180, (char)(second % 10 + 48));
		}			
		else {
				time += 200;
		}
		
		if (player == 0) {
			putimage(715, 30, &playerImage);
			setlinecolor(CLEARORANGE);
			roundrect(715, 30, 1015, 90, 10, 10);
			// int* lists = availableLocation(player+1);
		}

		Sleep(200);
	}
	return 0;
}

// 弹出窗口
int guideWindow(char* guide_window, char* title_window, int type) {
	HWND hnd = GetHWnd();
	if (type == 0) {
		MessageBox(hnd, guide_window, title_window, MB_OK);
	}
	else if (type == 1) {
		return MessageBox(hnd, guide_window, "游戏提示", MB_OKCANCEL);
	}

	return 0;
}

// 检测鼠标消息
int guideScanMouse(int leftx, int rightx, int upy, int bottomy, int type) {
	ExMessage msg2;
	IMAGE nextButton;
	if (type) {
	loadimage(&nextButton, "./image/next.png");
	putimage(760, 550, &nextButton);
	}

	while (1) {
		if (peekmessage(&msg2, EM_MOUSE)) {
			switch (msg2.message) {
			case WM_LBUTTONDOWN:
				if (msg2.x >= leftx && msg2.x <= rightx && msg2.y >= upy && msg2.y <= bottomy) {
					return 1;
				}
				/*if (msg2.x >= 760 && msg2.x <= 960 && msg2.y >= 550 && msg2.y <= 650) {
					return 1;   // 执行操作
				}*/
			}
		}
	}

	return 0;
}


// 游戏教程主函数
int guideMain() {
	IMAGE arrow;
	char confirm[] = "确认要开始游戏教程吗？";
	char titleConfirm[] = "游戏提示";
	if (guideWindow(confirm, titleConfirm, 1) == IDCANCEL) {
		return 1;
	}
	else{
		for (int i = 1; i <= 4; i++) {
		guideWindow(guideText(i), guideTitleText(i), 0);
		}

	}
	playerShow();
	setfillcolor(CLEARORANGERED);
	fillrectangle(715, 300, 1015, 660);
	settextcolor(WHITE);
	settextstyle(20, 0, _T("黑体"), 0, 0, FW_BOLD, false, false, false, 0, 0, 0, 0, 0); // 设置字体样式
	setlinestyle(PS_SOLID, 7);
	setlinecolor(CLEARORANGE);
	roundrect(715, 30, 1015, 90, 10, 10);   // 绘制上方黑棋回合
	setbkmode(TRANSPARENT);
	loadimage(&arrow, "./image/LEFT.png");
	setfillcolor(CLEARORANGERED);
	fillrectangle(715, 300, 1015, 660);
	setlinestyle(PS_DOT, 5);
	chessman(4, 3, 2); chessman(3, 4, 2);
	chessman(6, 5, 2); chessman(5, 6, 2);
	outtextxy(730, 320, "左侧为游戏棋盘，您将在这里");
	outtextxy(730, 340, "操作棋子。每次下棋前会有辅");
	outtextxy(730, 360, "助提示，告知您应如何落子。");
	outtextxy(730, 380, "每局游戏开始时，会有四颗固");
	outtextxy(730, 400, "定棋子。");
	putimage(830, 500, &arrow);
	guideScanMouse(760, 960, 550, 650, 1);
	loadimage(&arrow, "./image/UP.png");
	setfillcolor(CLEARORANGERED);
	setlinestyle(PS_SOLID, 7);
	fillrectangle(715, 300, 1015, 660);
	outtextxy(730, 320, "上侧棕色部分为当前玩家，被");
	outtextxy(730, 340, "橙色框圈起的部分为下棋玩家");
	outtextxy(730, 360, "。白色框表示所剩余的时间，");
	outtextxy(730, 380, "每局游戏有10分钟的时间，当");
	outtextxy(730, 400, "剩余时间为零时，游戏结束。");
	putimage(830, 500, &arrow);
	guideScanMouse(760, 960, 550, 650, 1);
	loadimage(&arrow, "./image/LEFT.png");
	setfillcolor(CLEARORANGERED);
	setlinestyle(PS_SOLID, 7);
	fillrectangle(715, 300, 1015, 660);	
	putimage(830, 500, &arrow);
	outtextxy(730, 320, "请点击左侧棋盘中的3D格子。");
	guideScanMouse(260, 340, 180, 260, 0);
	chessman(4, 3, 0); chessman(4, 4, 0);
	clearChessman(3, 4); clearChessman(6, 5); clearChessman(5, 6);
	loadimage(&arrow, "./image/UP.png");
	setfillcolor(CLEARORANGERED);
	setlinestyle(PS_SOLID, 7);
	setlinecolor(CLEARORANGE);
	fillrectangle(715, 300, 1015, 660);
	playerShow();	
	setlinestyle(PS_SOLID, 7);
	setlinecolor(CLEARORANGE);
	setfillcolor(CLEARORANGERED);
	settextstyle(20, 0, _T("黑体"), 0, 0, FW_BOLD, false, false, false, 0, 0, 0, 0, 0);
	roundrect(715, 90, 1015, 150, 10, 10);
	fillrectangle(715, 300, 1015, 660);
	chessman(5, 3, 2); chessman(3, 5, 2); chessman(3, 3, 2);
	outtextxy(730, 320, "恭喜！您成功的完成了第一步");
	outtextxy(730, 340, "。上方的橙色框移动到了白棋");
	outtextxy(730, 360, "的位置，这表示现在是白棋玩");
	outtextxy(730, 380, "家的落子时间。我们看看白棋");
	outtextxy(730, 400, "如何操作。");
	putimage(830, 500, &arrow);
	guideScanMouse(760, 960, 550, 650, 1);
	chessman(3, 3, 1); clearChessman(5, 3); clearChessman(3, 5); chessman(4, 4, 1);
	loadimage(&arrow, "./image/Correct.png");
	setfillcolor(CLEARORANGERED);
	setlinestyle(PS_SOLID, 7);
	setlinecolor(CLEARORANGE);
	fillrectangle(715, 300, 1015, 660);
	outtextxy(730, 320, "恭喜！您已完成了本教程的所");
	outtextxy(730, 340, "有内容。点击下面的“下一步");
	outtextxy(730, 360, "”按钮即可退出本教程。");
	putimage(830, 500, &arrow);
	guideScanMouse(760, 960, 550, 650, 1);
	return 0;
}

int main()
{
	
	initgraph(1024, 680);
	HWND title_Main = GetHWnd();
	SetWindowText(title_Main, "Reversi黑白棋");  // 修改窗口标题
	while (1) {
		checkerBoard();

		// 游戏菜单
		switch (startMenu()) {
		case 1:
			mciSendString("open ./music/clickButton.mp3 alias Button", 0, 0, 0);
			mciSendString("play Button", 0, 0, 0);
			playerShow();
			playMain();
			break;
		case 2:
			mciSendString("open ./music/clickButton.mp3 alias Button", 0, 0, 0);
			mciSendString("play Button", 0, 0, 0);
			guideMain();
			break;
		case 3:
			mciSendString("open ./music/clickButton.mp3 alias Button", 0, 0, 0);
			mciSendString("play Button", 0, 0, 0);
			break;
		}
}

	getchar();
	closegraph();
	return 0;
}