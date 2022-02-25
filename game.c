#include<math.h>

/*
 * DO NOT USE THIS FILE!
 * 不要使用这个文件编写程序！
 * 这只是实例文件，写核心游戏代码的同学
 * 请在github上的core分支提交内容！！！
 */
#define UL 1
#define UP 2
#define UR 3
#define LEFT 4
#define RIGHT 5
#define DL 6
#define DOWN 7
#define DR 8

typedef int* avaPointer;

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

// 检查该位置是否有效(可放置棋子)
int validPosition(int i, int j)
{
    if (i < 0 || i >= 8 || j < 0 || j >= 8) return 0;
    return 1;
}

// 检查棋子间距离
int distance(int i1, int j1, int i2, int j2)
{
    int di = abs(i1 - i2), dj = abs(j1 - j2);
    if (di > 0) return di;
    return dj;
}

int avaLocation(int i, int j, int player, int direction)
{
    if (!validPosition(i, j)) return 0;           // 若为无效位置，则跳过检查
    if (chessBoard[i][j] != 0) return 0;          // 若该位置有棋子，则跳过检查

    //int opposingPlayer = (player + 1) % 2;        // 对方棋子
    int opposingPlayer;
    if (player = 1)opposingPlayer = 2;
    else { opposingPlayer = 1; }


    int iCheck = i - 1, jCheck = j - 1;
    switch (direction) {
        case UL:
            // 测试 上左 方向是否夹住棋子
            while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
            {
                iCheck -= 1;
                jCheck -= 1;
            }
            if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
                return 1;
            // return 0;
        case UP:
            // 测试 上 方向是否夹住棋子
            iCheck = i - 1, jCheck = j;
            while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
                iCheck -= 1;

            if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
                return 1;
            // return 0;
        case UR:
            // 测试 上右 方向是否夹住棋子
            iCheck = i - 1, jCheck = j + 1;
            while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
            {
                iCheck -= 1;
                jCheck += 1;
            }
            if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
                return 1;
            // return 0;
        case LEFT:
            // 测试 左 方向是否夹住棋子
            iCheck = i, jCheck = j - 1;
            while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
                jCheck -= 1;

            if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
                return 1;
            // return 0;
        case RIGHT:
            // 测试 右 方向是否夹住棋子
            iCheck = i, jCheck = j + 1;
            while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
                jCheck += 1;

            if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
                return 1;
            // return 0;
        case DL:
            // 测试 下左 方向是否夹住棋子
            iCheck = i + 1, jCheck = j - 1;
            while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
            {
                iCheck += 1;
                jCheck -= 1;
            }
            if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
                return 1;
            // return 0;
        case DOWN:
            // 测试 下 方向是否夹住棋子
            iCheck = i + 1, jCheck = j;
            while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
                iCheck += 1;

            if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
                return 1;
            // return 0;
        case DR:
            // 测试 下右 方向是否夹住棋子
            iCheck = i + 1, jCheck = j + 1;
            while (validPosition(iCheck, jCheck) && chessBoard[iCheck][jCheck] == opposingPlayer)
            {
                iCheck += 1;
                jCheck += 1;
            }
            if (validPosition(iCheck, jCheck) && distance(i, j, iCheck, jCheck) > 1 && chessBoard[iCheck][jCheck] == player)
                return 1;
            
    }
    return 0;
}