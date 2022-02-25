#include<math.h>

/*
 * DO NOT USE THIS FILE!
 * ��Ҫʹ������ļ���д����
 * ��ֻ��ʵ���ļ���д������Ϸ�����ͬѧ
 * ����github�ϵ�core��֧�ύ���ݣ�����
 */
#define UL 1
#define UP 2
#define UR 3
#define LEFT 4
#define RIGHT 5
#define DL 6
#define DOWN 7
#define DR 8

static int chessBoard[8][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,2,1,0,0,0},
    {0,0,0,1,2,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};

// ������
/*int printnumber() {

    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++)
            printf("%d", chessBoard[i][j]);
        printf("\n");
    }
    printf("\n---");

        return 0;
}*/

// ���̸�λ
int resetChessBoard() {
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (i == 3 && j == 3 || i == 4 && j == 4)chessBoard[i][j] = 2;
            else if (i == 3 && j == 4 || i == 4 && j == 3)chessBoard[i][j] = 1;
            else chessBoard[i][j] = 0;
        }
    }
    return 0;
}

// ͬ����������
int syncChessBoard(int x, int y, int player) {

    chessBoard[y - 1][x - 1] = player + 1;
    return 0;
}

// ����λ���Ƿ���Ч(�ɷ�������)
int validPosition(int i, int j)
{
    if (i < 0 || i >= 8 || j < 0 || j >= 8) return 0;
    return 1;
}

// ������Ӽ����
int distance(int i1, int j1, int i2, int j2)
{
    int di = abs(i1 - i2), dj = abs(j1 - j2);
    if (di > 0) return di;
    return dj;
}

// ���ĳλ���Ƿ���Է�������
int avaLocation(int i, int j, int player, int direction)
{
    if (!validPosition(i, j)) return 0;           // ��Ϊ��Чλ�ã����������
    if (chessBoard[i][j] != 0) return 0;          // ����λ�������ӣ����������

    //int opposingPlayer = (player + 1) % 2;        // �Է�����
    int opposingPlayer;
    if (player == 1)opposingPlayer = 2;
    else { opposingPlayer = 1; }


    int iCheck = i - 1, jCheck = j - 1;
    switch (direction) {
    case UL:
        // ���� ���� �����Ƿ��ס����
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck -= 1;
            jCheck -= 1;
        }
        if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
            return 1;
        // return 0;
    case UP:
        // ���� �� �����Ƿ��ס����
        iCheck = i - 1, jCheck = j;
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
            iCheck -= 1;

        if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
            return 2;
        // return 0;
    case UR:
        // ���� ���� �����Ƿ��ס����
        iCheck = i - 1, jCheck = j + 1;
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck -= 1;
            jCheck += 1;
        }
        if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
            return 3;
        // return 0;
    case LEFT:
        // ���� �� �����Ƿ��ס����
        iCheck = i, jCheck = j - 1;
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
            jCheck -= 1;

        if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
            return 4;
        // return 0;
    case RIGHT:
        // ���� �� �����Ƿ��ס����
        iCheck = i, jCheck = j + 1;
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
            jCheck += 1;

        if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
            return 5;
        // return 0;
    case DL:
        // ���� ���� �����Ƿ��ס����
        iCheck = i + 1, jCheck = j - 1;
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck += 1;
            jCheck -= 1;
        }
        if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
            return 6;
        // return 0;
    case DOWN:
        // ���� �� �����Ƿ��ס����
        iCheck = i + 1, jCheck = j;
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
            iCheck += 1;

        if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
            return 7;
        // return 0;
    case DR:
        // ���� ���� �����Ƿ��ס����
        iCheck = i + 1, jCheck = j + 1;
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck += 1;
            jCheck += 1;
        }
        if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
            return 8;

    }
    return 0;
}

// ���ĳ������Ը��Ƕ�������
int reverseChessman(int i, int j, int player, int direction) {
    int opposingPlayer;
    int iCheck = i, jCheck = j;
    int number = 0;
    if (player == 1) opposingPlayer = 2;
    else { opposingPlayer = 1; }

    switch (direction) {
    case UL:
        iCheck = i - 1; jCheck = j - 1;
        while (chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck -= 1;
            jCheck -= 1;
            number++;
        }
        return number;
        break;
    case UP:
        iCheck = i - 1, jCheck = j;
        while (chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck -= 1;
            number++;
        }
        return number;
        break;
    case UR:
        iCheck = i - 1, jCheck = j + 1;
        while (chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck -= 1;
            jCheck += 1;
            number++;
        }
        return number;
        break;
    case LEFT:
        iCheck = i, jCheck = j - 1;
        while (chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            jCheck -= 1;
            number++;
        }
        return number;
        break;
    case RIGHT:
        iCheck = i, jCheck = j + 1;
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            jCheck += 1;
            number++;
        }
        return number;
        break;
    case DL:
        iCheck = i + 1, jCheck = j - 1;
        while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck += 1;
            jCheck -= 1;
            number++;
        }
        return number;
        break;
    case DOWN:
        iCheck = i + 1, jCheck = j;
        while (chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck += 1;
            number++;
        }

        return number;
    case DR:
        iCheck = i + 1, jCheck = j + 1;
        while (chessBoard[iCheck][jCheck] == opposingPlayer)
        {
            iCheck += 1;
            jCheck += 1;
            number++;
        }
        return number;
        break;
    }
    return 0;
}

// ���Ӯ��
int checkWinner() {
    int blackScore, whiteScore, numbers;
    for (int player = 1; player <= 2; player++) {
        numbers = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (chessBoard[i][j] == player)numbers++;
        if (player == 1)blackScore = numbers;
        else whiteScore = numbers;
    }
    if (whiteScore < blackScore)return 0;
    else if (whiteScore > blackScore)return 1;
    else return 2;
}