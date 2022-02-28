#include<easyx.h>                 // EasyXͼ�λ���
#include <stdio.h>
#include<process.h>               // ���߳̿�
#include<stdlib.h>                // ���������
#include<mmstream.h>              // ������ý���豸�ӿ�ͷ�ļ�
#include<string.h>                // ���������
#include "guide.c"                // �̳��ı�
#include "function.c"             // �����߼�����
#include "game.c"                 // ��Ϸ�߼�


#pragma comment(lib,"winmm.lib")  // ���ؾ�̬��

#define CLEARGREEN RGB(123,237,159)
#define CLEARORANGE RGB(243,156,18)
#define CLEARORANGERED RGB(230,126,34)

#define BLACKPLAYER 0
#define WHITEPLAYER 1
#define AVAILABLE 2

#define UL 1
#define UP 2
#define UR 3
#define LEFT 4
#define RIGHT 5
#define DL 6
#define DOWN 7
#define DR 8

int chessman(int x, int y, int player);
int playerShow();
int startMenu();
int checkerBoard();
int playMain();
int guideScanMouse(int leftx, int rightx, int upy, int bottomy, int type);

// ����ʱ��Ϣ
int timeUp = 0;
int endGame = 0;

// �˻���ս��Ϣ
int aiMode = 0;

// ��Ϸ����ʱ�̺߳���
void countDown(void *) {
	int time = 0, second = 0, minute = 10, onGame = 1;
	int endMode = 0;
	while (onGame) {
		// ����ʱ
		if (endGame == 1) {
			onGame = 0;
			endMode = 1;
		}
		if (time == 1000) {
			time = 0;
			if (second != 0) {
				second--;
			}
			else if (minute != 0) {
				second = 59;
				minute--;
			}
			else {
				onGame = 0;
				continue;
			}
			setfillcolor(WHITE);
			setlinecolor(WHITE);
			setlinestyle(PS_SOLID, 7);
			fillroundrect(715, 170, 1015, 210, 10, 10);
			outtextxy(730, 180, "ʣ��ʱ�䣺");
			outtextxy(850, 180, "��   ��");
			outtextxy(837, 180, (char)(minute + 48));
			outtextxy(875, 180, (char)(second / 10 + 48));
			outtextxy(890, 180, (char)(second % 10 + 48));
		}
		else {
			time += 50;
		}

		Sleep(50);
	}
	if (endMode == 0) {
		timeUp = 1;
		setfillcolor(CLEARORANGERED);
		setlinestyle(PS_SOLID, 7);
		setlinecolor(CLEARORANGE);
		fillrectangle(715, 300, 1015, 660);
		settextstyle(50, 0, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false, 0, 0, 0, 0, 0); // ����������ʽ
		setbkmode(TRANSPARENT);
		outtextxy(730, 320, "ʱ�䵽��");
		settextstyle(20, 0, _T("����"), 0, 0, FW_BOLD, false, false, false, 0, 0, 0, 0, 0); // ����������ʽ
		outtextxy(730, 370, "�������⸨�����Ӳ鿴���");
		_endthread();
	}
	else {
		endMode = 0;
		endGame = 0;
		_endthread();
	}

}

// �������ɺ���
int chessman(int x, int y, int player = 2)
{
	IMAGE chessman;
	if (player == BLACKPLAYER) {
		setfillcolor(BLACK);
		loadimage(&chessman, "./image/black.png");
	}
	else if(player == WHITEPLAYER) {
		setfillcolor(WHITE);
		loadimage(&chessman, "./image/white.png");
	}
	else {
		setlinestyle(PS_DOT, 5);
		circle(x * 80 - 20, y * 80 - 20, 25);
		return 1;
	}
	/*setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	solidcircle(x * 80 - 20, y * 80 - 20, 30);
	circle(x * 80 - 20, y * 80 - 20, 25);*/
	putimage(x * 80 - 50, y * 80 - 50, &chessman);
	return 0;
}

// ��Ϸ�������Զ����ɸ���
int chessHelper(int x, int y,int number,int direction,int player) {
	/* TODO ���һ��Ч������
	 * ��EasyX��֧��GIF��һ֡
	 * ��Ҫ��һ������Ч������
	 */
	/*IMAGE change;
	if (player == WHITEPLAYER) {
		loadimage(&change, "./image/btw.gif");
	}
	else loadimage(&change, "./image/wtb.gif"); */
	
	switch (direction) {
		case UL:
			for (int i_1 = 1; i_1 <= number; i_1++) {
				x--; y--;
				chessman(x, y, player);
				syncChessBoard(x, y, player);
			}
			break;
		case UP:
			for (int i_2 = 1; i_2 <= number; i_2++) {
				y--;
				chessman(x, y, player);
				syncChessBoard(x, y, player);
			}
			break;
		case UR:
			for (int i_3 = 1; i_3 <= number; i_3++) {
				x++; y--;
				chessman(x, y, player);
				syncChessBoard(x, y, player);
			}
			break;
		case LEFT:
			for (int i_4 = 1; i_4 <= number; i_4++) {
				x--;
				chessman(x, y, player);
				syncChessBoard(x, y, player);
			}
			break;
		case RIGHT:
			for (int i_5 = 1; i_5 <= number; i_5++) {
				x++;
				chessman(x, y, player);
				syncChessBoard(x, y, player);
			}
			break;
		case DL:
			for (int i_6 = 1; i_6 <= number; i_6++) {
				x--; y++;
				chessman(x, y, player);
				syncChessBoard(x, y, player);
			}
			break;
		case DOWN:
			for (int i_7 = 1; i_7 <= number; i_7++) {
				y++;
				chessman(x, y, player);
				syncChessBoard(x, y, player);
			}
			break;
		case DR:
			for (int i_6 = 1; i_6 <= number; i_6++) {
				x++; y++;
				chessman(x, y, player);
				syncChessBoard(x, y, player);
			}
			break;
	}
	return 0;
}

// ��������е�ĳλ�õ�����(�����������)
int clearChessman(int x, int y)
{
	setfillcolor(CLEARGREEN);
	solidcircle(x * 80 - 20, y * 80 - 20, 30);
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
	setlinecolor(WHITE);
	fillroundrect(715, 170, 1015, 210,10,10);
	settextstyle(20, 0, _T("����"), 0, 0, FW_BOLD, false, false, false, 0, 0, 0, 0, 0); // ����������ʽ
	outtextxy(730, 180, "ʣ��ʱ�䣺");	
	outtextxy(850, 180, "��   ��");
	outtextxy(822, 180, (char)(49));
	outtextxy(837, 180, (char)(48));
	outtextxy(875, 180, (char)(48));
	outtextxy(890, 180, (char)(48));
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
	setlinestyle(PS_SOLID, 1); setlinecolor(WHITE);
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
	chessman(4, 4, WHITEPLAYER);chessman(5, 5, WHITEPLAYER);
	chessman(4, 5, BLACKPLAYER);chessman(5, 4, BLACKPLAYER);
	putimage(700, 0, &settingBkground);
	putimage(715, 30, &titleBkground);

	// getchar();
	return 0;
}

// ������������Ϣ
int gameScanMouse() {
	ExMessage msg3;
	while (1) {
		if (peekmessage(&msg3, EM_MOUSE)) {
			switch (msg3.message) {
				case WM_LBUTTONDOWN:
					if (msg3.y >= 20 && msg3.y <= 100) {
						if (msg3.x >= 20 && msg3.x <= 100) return 11;
						if (msg3.x >= 101 && msg3.x <= 180) return 12;
						if (msg3.x >= 181 && msg3.x <= 260) return 13;
						if (msg3.x >= 261 && msg3.x <= 340) return 14;
						if (msg3.x >= 341 && msg3.x <= 420) return 15;
						if (msg3.x >= 421 && msg3.x <= 500) return 16;
						if (msg3.x >= 501 && msg3.x <= 580) return 17;
						if (msg3.x >= 581 && msg3.x <= 660) return 18;
					}
					else if (msg3.y >= 101 && msg3.y <= 180) {
						if (msg3.x >= 20 && msg3.x <= 100) return 21;
						if (msg3.x >= 101 && msg3.x <= 180) return 22;
						if (msg3.x >= 181 && msg3.x <= 260) return 23;
						if (msg3.x >= 261 && msg3.x <= 340) return 24;
						if (msg3.x >= 341 && msg3.x <= 420) return 25;
						if (msg3.x >= 421 && msg3.x <= 500) return 26;
						if (msg3.x >= 501 && msg3.x <= 580) return 27;
						if (msg3.x >= 581 && msg3.x <= 660) return 28;
					}
					else if (msg3.y >= 181 && msg3.y <= 260) {
						if (msg3.x >= 20 && msg3.x <= 100) return 31;
						if (msg3.x >= 101 && msg3.x <= 180) return 32;
						if (msg3.x >= 181 && msg3.x <= 260) return 33;
						if (msg3.x >= 261 && msg3.x <= 340) return 34;
						if (msg3.x >= 341 && msg3.x <= 420) return 35;
						if (msg3.x >= 421 && msg3.x <= 500) return 36;
						if (msg3.x >= 501 && msg3.x <= 580) return 37;
						if (msg3.x >= 581 && msg3.x <= 660) return 38;
					}
					else if (msg3.y >= 261 && msg3.y <= 340) {
						if (msg3.x >= 20 && msg3.x <= 100) return 41;
						if (msg3.x >= 101 && msg3.x <= 180) return 42;
						if (msg3.x >= 181 && msg3.x <= 260) return 43;
						if (msg3.x >= 261 && msg3.x <= 340) return 44;
						if (msg3.x >= 341 && msg3.x <= 420) return 45;
						if (msg3.x >= 421 && msg3.x <= 500) return 46;
						if (msg3.x >= 501 && msg3.x <= 580) return 47;
						if (msg3.x >= 581 && msg3.x <= 660) return 48;
					}
					else if (msg3.y >= 341 && msg3.y <= 420) {
						if (msg3.x >= 20 && msg3.x <= 100) return 51;
						if (msg3.x >= 101 && msg3.x <= 180) return 52;
						if (msg3.x >= 181 && msg3.x <= 260) return 53;
						if (msg3.x >= 261 && msg3.x <= 340) return 54;
						if (msg3.x >= 341 && msg3.x <= 420) return 55;
						if (msg3.x >= 421 && msg3.x <= 500) return 56;
						if (msg3.x >= 501 && msg3.x <= 580) return 57;
						if (msg3.x >= 581 && msg3.x <= 660) return 58;
					}
					else if (msg3.y >= 421 && msg3.y <= 500) {
						if (msg3.x >= 20 && msg3.x <= 100) return 61;
						if (msg3.x >= 101 && msg3.x <= 180) return 62;
						if (msg3.x >= 181 && msg3.x <= 260) return 63;
						if (msg3.x >= 261 && msg3.x <= 340) return 64;
						if (msg3.x >= 341 && msg3.x <= 420) return 65;
						if (msg3.x >= 421 && msg3.x <= 500) return 66;
						if (msg3.x >= 501 && msg3.x <= 580) return 67;
						if (msg3.x >= 581 && msg3.x <= 660) return 68;
					}
					else if (msg3.y >= 501 && msg3.y <= 580) {
						if (msg3.x >= 20 && msg3.x <= 100) return 71;
						if (msg3.x >= 101 && msg3.x <= 180) return 72;
						if (msg3.x >= 181 && msg3.x <= 260) return 73;
						if (msg3.x >= 261 && msg3.x <= 340) return 74;
						if (msg3.x >= 341 && msg3.x <= 420) return 75;
						if (msg3.x >= 421 && msg3.x <= 500) return 76;
						if (msg3.x >= 501 && msg3.x <= 580) return 77;
						if (msg3.x >= 581 && msg3.x <= 660) return 78;
					}
					else if (msg3.y >= 581 && msg3.y <= 660) {
						if (msg3.x >= 20 && msg3.x <= 100) return 81;
						if (msg3.x >= 101 && msg3.x <= 180) return 82;
						if (msg3.x >= 181 && msg3.x <= 260) return 83;
						if (msg3.x >= 261 && msg3.x <= 340) return 84;
						if (msg3.x >= 341 && msg3.x <= 420) return 85;
						if (msg3.x >= 421 && msg3.x <= 500) return 86;
						if (msg3.x >= 501 && msg3.x <= 580) return 87;
						if (msg3.x >= 581 && msg3.x <= 660) return 88;
					}
			}
		}
	}
}

// ��Ϸ������
int playMain() {
	IMAGE playerImage;
	loadimage(&playerImage, "./image/player.png");
	int player = 0, checkPlayer = 1, onGame = 1;              // �ڷ�����
	int chessmanNumber = 4, blackScore = 2, whiteScore = 2;   // ���ּ�������ʾ��ر���
	int avaList[20] = {}, avaCoordinate[20][2] = {};
	int avaListCycle = 0, avaCoordinateCycle = 0;
	int number, clickPoint = 0;
	_beginthread(countDown, 0, NULL);
	setfillcolor(WHITE);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 7);
	fillroundrect(715, 220, 1015, 260, 10, 10);
	settextstyle(20, 0, _T("����"), 0, 0, FW_BOLD, false, false, false, 0, 0, 0, 0, 0); // ����������ʽ
	outtextxy(730, 235, "���壺");
	outtextxy(850, 235, "���壺");
	mciSendString("open ./music/chessMan.mp3 alias chessMan", 0, 0, 0);
	while (onGame) {
		setlinestyle(PS_SOLID, 7);
		putimage(715, 30, &playerImage);
		setlinecolor(CLEARORANGE);		
		if (player == BLACKPLAYER) roundrect(715, 30, 1015, 90, 10, 10);
		else if (player == WHITEPLAYER) roundrect(715, 90, 1015, 150, 10, 10);
		outtextxy(785, 235, (char)(blackScore / 10 + 48));
		outtextxy(800, 235, (char)(blackScore % 10 + 48));
		outtextxy(905, 235, (char)(whiteScore / 10 + 48));
		outtextxy(920, 235, (char)(whiteScore % 10 + 48));
		// ���ɸ�������
		for (int i = 0; i <= 7; i++) {
			for (int j = 0; j <= 7; j++) {
				if (avaLocation(i,j,player+1,1)) {
					chessman(j + 1, i + 1, 2);
					avaCoordinate[avaCoordinateCycle][0] = j + 1;
					avaCoordinate[avaCoordinateCycle][1] = i + 1;
					avaCoordinateCycle++;
					avaList[avaListCycle++] = (i + 1) * 10 + j + 1;
				}
			}
		}
		if (avaList[0]) {
			while (1) {
				if(!aiMode) clickPoint = gameScanMouse();
				else if (player == WHITEPLAYER) {
						Sleep(1000);
						// ��ȡavaList�еĳ��ȣ�����Ч�����ִ���clickPoint
						clickPoint = avaList[randomNumber(validNumber(avaList))];
					}
				else{ clickPoint = gameScanMouse(); }
				if (timeUp == 1) {
					onGame = 0;
					break;
				}
				if (queryExsist(avaList, clickPoint)) {
					chessmanNumber++;
					// �����������
					for (int cyc = 0; cyc <= avaCoordinateCycle; cyc++) {
						clearChessman(avaCoordinate[cyc][0], avaCoordinate[cyc][1]);
					}
					chessman(clickPoint % 10, clickPoint / 10, player);
					mciSendString("close chessMan", 0, 0, 0);
					mciSendString("open ./music/chessMan.mp3 alias chessMan", 0, 0, 0);
					mciSendString("play chessMan", 0, 0, 0);
					
					for (int _i = 1; _i <= 8; _i++) {
						_i = avaLocation((clickPoint / 10) - 1, (clickPoint % 10) - 1, player + 1, _i);
						number = reverseChessman((clickPoint / 10) - 1, (clickPoint % 10) - 1, player + 1, _i);
						chessHelper(clickPoint % 10, clickPoint / 10, number, _i, player);
						if (_i == 0) break;
					}
				syncChessBoard(clickPoint % 10, clickPoint / 10, player);
				break;
				}
			}
		}
		else {
			// ���Է��Ƿ�Ҳ�������
			if (player == BLACKPLAYER)checkPlayer = WHITEPLAYER;
			else { checkPlayer = BLACKPLAYER; }
			for (int i = 0; i <= 7; i++) {
				for (int j = 0; j <= 7; j++) {
					if (avaLocation(i, j, checkPlayer + 1, 1)) {
						avaCoordinate[avaCoordinateCycle][0] = j + 1;
						avaCoordinate[avaCoordinateCycle][1] = i + 1;
						avaCoordinateCycle++;
						avaList[avaListCycle++] = (i + 1) * 10 + j + 1;
					}
				}
			}
			if (!avaList[0]) onGame = 0;
		}

		memset(avaList, 0, sizeof avaList);
		memset(avaCoordinate, 0, sizeof avaCoordinate);
		avaCoordinateCycle = 0; avaListCycle = 0;
		

		if (player == BLACKPLAYER)player = WHITEPLAYER;
		else { player = BLACKPLAYER; }
		blackScore = checkWinner(1);
		whiteScore = checkWinner(2);
		//printnumber();  // ������	
	}
	timeUp = 0;  // ����ʱ��
	setfillcolor(CLEARORANGERED);
	setlinecolor(CLEARORANGE);
	setlinestyle(PS_SOLID, 7);
	fillrectangle(715, 300, 1015, 660);
	settextstyle(50, 0, _T("����"), 0, 0, FW_EXTRABOLD, false, false, false, 0, 0, 0, 0, 0); // ����������ʽ
	setbkmode(TRANSPARENT);
	outtextxy(730, 320, "��ϲ��");
	fillrectangle(730, 500, 1000, 600);
	if (checkWinner(3) == 0) {
		outtextxy(730, 370, "��ʤ����");
		outtextxy(730, 420, "  ������ң�");
	}
	else if (checkWinner(3) == 1) {
		outtextxy(730, 370, "��ʤ����");
		outtextxy(730, 420, "  ������ң�");
	}
	else {
		outtextxy(730, 370, "����Ϊ");
		outtextxy(730, 420, "   ƽ�֣�");
	}
	outtextxy(730, 525, "  ���˵�");
	endGame = 1;
	guideScanMouse(730, 1000, 500, 600, 0);
	resetChessBoard();
	// printnumber();
	return 0;
}

// ��������
int guideWindow(char* guide_window, char* title_window, int type) {
	HWND hnd = GetHWnd();
	if (type == 0) {
		MessageBox(hnd, guide_window, title_window, MB_OK);
	}
	else if (type == 1) {
		return MessageBox(hnd, guide_window, "��Ϸ��ʾ", MB_OKCANCEL);
	}

	return 0;
}

// ��Ϸ�̳̽����������Ϣ
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
				if (msg2.x >= leftx && msg2.x <= rightx && msg2.y >= upy && msg2.y <= bottomy) return 1;
			}
		}
	}

	return 0;
}

// ��Ϸ�̳�������
int guideMain() {
	IMAGE arrow;
	char confirm[] = "ȷ��Ҫ��ʼ��Ϸ�̳���";
	char titleConfirm[] = "��Ϸ��ʾ";
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
	settextstyle(20, 0, _T("����"), 0, 0, FW_BOLD, false, false, false, 0, 0, 0, 0, 0); // ����������ʽ
	setlinestyle(PS_SOLID, 7);
	setlinecolor(CLEARORANGE);
	roundrect(715, 30, 1015, 90, 10, 10);   // �����Ϸ�����غ�
	setbkmode(TRANSPARENT);
	loadimage(&arrow, "./image/LEFT.png");
	setfillcolor(CLEARORANGERED);
	fillrectangle(715, 300, 1015, 660);
	setlinestyle(PS_DOT, 5);
	chessman(4, 3, AVAILABLE); chessman(3, 4, AVAILABLE);
	chessman(6, 5, AVAILABLE); chessman(5, 6, AVAILABLE);
	outtextxy(730, 320, "���Ϊ��Ϸ���̣�����������");
	outtextxy(730, 340, "�������ӡ�ÿ������ǰ���и�");
	outtextxy(730, 360, "����ʾ����֪��Ӧ������ӡ�");
	outtextxy(730, 380, "ÿ����Ϸ��ʼʱ�������ĿŹ�");
	outtextxy(730, 400, "�����ӡ�");
	putimage(830, 500, &arrow);
	guideScanMouse(760, 960, 550, 650, 1);
	loadimage(&arrow, "./image/UP.png");
	setfillcolor(CLEARORANGERED);
	setlinestyle(PS_SOLID, 7);
	fillrectangle(715, 300, 1015, 660);
	outtextxy(730, 320, "�ϲ���ɫ����Ϊ��ǰ��ң���");
	outtextxy(730, 340, "��ɫ��Ȧ��Ĳ���Ϊ�������");
	outtextxy(730, 360, "����ɫ���ʾ��ʣ���ʱ�䣬");
	outtextxy(730, 380, "ÿ����Ϸ��10���ӵ�ʱ�䣬��");
	outtextxy(730, 400, "ʣ��ʱ��Ϊ��ʱ����Ϸ������");
	putimage(830, 500, &arrow);
	guideScanMouse(760, 960, 550, 650, 1);
	loadimage(&arrow, "./image/LEFT.png");
	setfillcolor(CLEARORANGERED);
	setlinestyle(PS_SOLID, 7);
	fillrectangle(715, 300, 1015, 660);	
	putimage(830, 500, &arrow);
	outtextxy(730, 320, "������������е�3D���ӡ�");
	guideScanMouse(260, 340, 180, 260, 0);
	chessman(4, 3, BLACKPLAYER); chessman(4, 4, BLACKPLAYER);
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
	settextstyle(20, 0, _T("����"), 0, 0, FW_BOLD, false, false, false, 0, 0, 0, 0, 0);
	roundrect(715, 90, 1015, 150, 10, 10);
	fillrectangle(715, 300, 1015, 660);
	chessman(5, 3, AVAILABLE); chessman(3, 5, AVAILABLE); chessman(3, 3, AVAILABLE);
	outtextxy(730, 320, "��ϲ�����ɹ�������˵�һ��");
	outtextxy(730, 340, "���Ϸ��ĳ�ɫ���ƶ����˰���");
	outtextxy(730, 360, "��λ�ã����ʾ�����ǰ�����");
	outtextxy(730, 380, "�ҵ�����ʱ�䡣���ǿ�������");
	outtextxy(730, 400, "��β�����");
	putimage(830, 500, &arrow);
	guideScanMouse(760, 960, 550, 650, 1);
	chessman(3, 3, WHITEPLAYER); clearChessman(5, 3); clearChessman(3, 5); chessman(4, 4, WHITEPLAYER);
	loadimage(&arrow, "./image/Correct.png");
	setfillcolor(CLEARORANGERED);
	setlinestyle(PS_SOLID, 7);
	setlinecolor(CLEARORANGE);
	fillrectangle(715, 300, 1015, 660);
	outtextxy(730, 320, "��ϲ����������˱��̵̳���");
	outtextxy(730, 340, "�����ݡ��������ġ���һ��");
	outtextxy(730, 360, "����ť�����˳����̡̳�");
	putimage(830, 500, &arrow);
	guideScanMouse(760, 960, 550, 650, 1);
	return 0;
}

int main()
{
	
	initgraph(1024, 680);
	HWND title_Main = GetHWnd();
	SetWindowText(title_Main, "Reversi�ڰ���");  // �޸Ĵ��ڱ���
	mciSendString("open ./music/clickButton.mp3 alias Button", 0, 0, 0);
	mciSendString("open ./music/backGroundMusic.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
	while (1) {
		checkerBoard();

		// ��Ϸ�˵�
		switch (startMenu()) {
		case 1:
			mciSendString("close Button", 0, 0, 0);
			mciSendString("open ./music/clickButton.mp3 alias Button", 0, 0, 0);
			mciSendString("play Button", 0, 0, 0);
			playerShow();
			playMain();
			break;
		case 2:
			mciSendString("close Button", 0, 0, 0);
			mciSendString("open ./music/clickButton.mp3 alias Button", 0, 0, 0);
			mciSendString("play Button", 0, 0, 0);
			guideMain();
			break;
		case 3:
			mciSendString("close Button", 0, 0, 0);
			mciSendString("open ./music/clickButton.mp3 alias Button", 0, 0, 0);
			mciSendString("play Button", 0, 0, 0);
			aiMode = 1;
			playerShow();
			playMain();
			aiMode = 0;
			break;
		}
}
	closegraph();
	return 0;
}