#include<stdio.h>
#include<easyx.h>                 // EasyXͼ�λ���
#include<conio.h>
#include<mmstream.h>              // ������ý���豸�ӿ�ͷ�ļ�
#pragma comment(lib,"winmm.lib")  // ���ؾ�̬��

#define CLEARGREEN RGB(123,237,159)
#define CLEARORANGE RGB(243,156,18)


int chessman(int x, int y, int player);
int playerShow();
int startMenu();
int checkerBoard();
int playMain();

// �������ɺ���
int chessman(int x, int y, int player)
{
	if (player == 0) {
		setfillcolor(BLACK);
	}
	else {
		setfillcolor(WHITE);
	}

	solidcircle(x * 80 - 20, y * 80 - 20, 30);
	circle(x * 80 - 20, y * 80 - 20, 25);
	return 0;
}
// ��ʼ��Ϸ������ƺ���
int playerShow() {
	IMAGE player, titleBkground, step;
	loadimage(&player, "./image/player.png");                // ���غڰ������Ͻ�״̬
	loadimage(&titleBkground, "./image/woolSut.jpg");        // �����Ҳ౳��ͼƬ
	putimage(715, 30, &titleBkground);
	putimage(715, 30, &player);
	settextcolor(BLACK);
	setfillcolor(WHITE);
	fillroundrect(715, 170, 1015, 210,10,10);
	settextstyle(20, 0, _T("����"), 0, 0, FW_BOLD, true, true, false, 0, 0, 0, 0, 0); // ����������ʽ
	outtextxy(730, 180, "ʣ��ʱ�䣺");

	return 0;
}

// ������Ϸ�˵�
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
				if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 170 && msg.y <= 290) {        // �ж�����Ƿ�λ�ڡ���ʼ��Ϸ��
					loadimage(&startGame, "./image/start_on.png");
				}
				else if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 310 && msg.y <= 430) {   // �ж�����Ƿ�λ�ڡ���Ϸ�̡̳�
					loadimage(&gameGuide, "./image/guide_on.png");
				}
				else if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 450 && msg.y <= 570) {   // �ж�����Ƿ�λ�ڡ��˻���ս��
					loadimage(&AImode, "./image/AImode_on.png");
				}
				putimage(715, 170, &startGame);
				putimage(715, 310, &gameGuide);
				putimage(715, 450, &AImode);
				break;
			case WM_LBUTTONDOWN:
				if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 170 && msg.y <= 290) {        
					return 1;   // ���¡���ʼ��Ϸ��ִ�в���1
				}
				else if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 310 && msg.y <= 430) {
					return 2;   // ���¡���Ϸ�̡̳�ִ�в���2
				}
				else if (msg.x >= 715 && msg.x <= 1015 && msg.y >= 450 && msg.y <= 570) {
					return 3;   // ���¡��˻���ս��ִ�в���3
				}
			}
		}
	}

	return 0;
}

// �������ɺ���
int checkerBoard()
{
	IMAGE settingBkground, titleBkground;
	loadimage(&settingBkground, "./image/woolSut.jpg");
	loadimage(&titleBkground, "./image/title.png");
	char listNumber[9] = "abcdefgh";
	char lineNumber[9] = "12345678";
	setbkcolor(WHITE); cleardevice();                            // ���ñ�����ɫ
	setfillcolor(CLEARGREEN);settextcolor(CLEARGREEN);           // ������估������ɫ
	settextstyle(20, 0, _T("����"));
	fillroundrect(20, 20, 660, 660, 5, 5);                       // �������̱���
	// �������̸��Ӽ����к�
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
	// ���Ƴ�ʼ��Ϸ����
	chessman(4, 4, 1);chessman(5, 5, 1);
	chessman(4, 5, 0);chessman(5, 4, 0);
	putimage(700, 0, &settingBkground);
	putimage(715, 30, &titleBkground);

	// getchar();
	return 0;
}

// ��Ϸ������s
int playMain() {
	IMAGE playerImage;
	loadimage(&playerImage, "./image/player.png");
	int time = 0, second = 59, minute = 9, onGame = 1;
	int player = 0;                                        // �ڷ�����
	while (onGame) {
		setlinestyle(PS_SOLID, 7);

		// ����ʱ
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
			outtextxy(730, 180, "ʣ��ʱ�䣺");
			outtextxy(850, 180, "��   ��");
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

int main()
{

	initgraph(1024, 680);
	checkerBoard();
	
	// ��Ϸ�˵�
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
			break;
		case 3:
			mciSendString("open ./music/clickButton.mp3 alias Button", 0, 0, 0);
			mciSendString("play Button", 0, 0, 0);
			break;
	}
	getchar();
	closegraph();
	return 0;
}