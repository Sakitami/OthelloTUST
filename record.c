#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 27					//每行最大字节数

 // 获取排行榜信息
static char playerRanking[50][3][11];

int rankList()
{
    FILE* fp;
    FILE* fp1;
    int count = 1, k = 0;
    int split;
    char strLine[MAX_LINE];	//读取缓冲区
    //char playerRanking[50][3][11], 
    char tempChar[1][3][11];
    if ((fp = fopen("./new.txt", "r")) == NULL)	// 判断文件是否存在及可读
    {
        printf("Open Falied!");
        return -1;
    }
    if ((fp1 = fopen("./new.txt", "a")) == NULL)	// 打开指定文件，如果文件不存在则新建该文件
    {
        printf("Open Failed.\n");
        return -1;
    }
    // 将每一行的数据按照规则保存在playerRanking中
    for (int i = 0; !feof(fp); i++)	//循环读取每一行，直到文件尾
    {
        k = 0;
        fgets(strLine, MAX_LINE, fp); // 将fp所指向的文件一行内容读到strLine缓冲区
        //printf("%s", strLine);
        split = 1;
        for (int j = 0; j < sizeof(strLine); j++) {
            if (strLine[j] == ',') {
                split++;
                k = 0;
                continue;
            }
            if (strLine[j] == '\0') {
                j = sizeof(strLine);
                continue;
            }
            playerRanking[i][split - 1][k] = strLine[j];
            k++;
        }
    }
    int ROW = 0;
    for (int row = 0; row < 50; row++) {
        if (playerRanking[row][0][0] != '\0') ROW++;
        else if (playerRanking[row][0][0] == '\0') continue;
    }//把每一行全部遍历，遇到有数据的行就记数加一，遇到\0直接结束
    for (int ScoreRow = 0; ScoreRow < ROW; ScoreRow++) {
        for (int scoreIndex = 0; playerRanking[scoreIndex + 1][1][0] != '\0'; scoreIndex++) {
            int score1 = atoi(playerRanking[scoreIndex][1]);
            int score2 = atoi(playerRanking[scoreIndex + 1][1]);
            if (score1 >= score2) continue;
            else {
                for (int _temp = 0; _temp < sizeof(playerRanking[scoreIndex][0]); _temp++)tempChar[0][0][_temp] = playerRanking[scoreIndex][0][_temp];
                for (int _temp2 = 0; _temp2 < sizeof(playerRanking[scoreIndex][1]); _temp2++)tempChar[0][1][_temp2] = playerRanking[scoreIndex][1][_temp2];
                for (int _temp3 = 0; _temp3 < sizeof(playerRanking[scoreIndex][2]); _temp3++)tempChar[0][2][_temp3] = playerRanking[scoreIndex][2][_temp3];
                for (int _temp4 = 0; _temp4 < sizeof(playerRanking[scoreIndex + 1][0]); _temp4++)playerRanking[scoreIndex][0][_temp4] = playerRanking[scoreIndex + 1][0][_temp4];
                for (int _temp5 = 0; _temp5 < sizeof(playerRanking[scoreIndex + 1][1]); _temp5++)playerRanking[scoreIndex][1][_temp5] = playerRanking[scoreIndex + 1][1][_temp5];
                for (int _temp6 = 0; _temp6 < sizeof(playerRanking[scoreIndex + 1][2]); _temp6++)playerRanking[scoreIndex][2][_temp6] = playerRanking[scoreIndex + 1][2][_temp6];
                for (int _temp7 = 0; _temp7 < sizeof(tempChar[0][0]); _temp7++)playerRanking[scoreIndex + 1][0][_temp7] = tempChar[0][0][_temp7];
                for (int _temp8 = 0; _temp8 < sizeof(tempChar[0][1]); _temp8++)playerRanking[scoreIndex + 1][1][_temp8] = tempChar[0][1][_temp8];
                for (int _temp9 = 0; _temp9 < sizeof(tempChar[0][2]); _temp9++)playerRanking[scoreIndex + 1][2][_temp9] = tempChar[0][2][_temp9];
            }
        }
    }

    //printf("%d",atoi(&playerRanking[1][0][0]));
    fclose(fp);	 // 关闭读文件
    fclose(fp1); // 关闭写文件
    return 0;
}

// 获取玩家分数，并返回
int gainPlayerScore(int player) {
    return atoi(&playerRanking[player][1][0]);
}

// 获取玩家对局场次，并返回
int gainPlayerClass(int player) {
    if (playerRanking[player][0][0] == '\0')return 0;
    return atoi(&playerRanking[player][0][0]);
}

// 获取玩家名，并返回
char *gainPlayerName(int player) {
    return playerRanking[player][2];
}

// 清空字符数组
void clearPlayerRanking(void){
    int i = 0;
    for(int i = 0; i < 50;i++){
        strcpy(playerRanking[i][0], "");
        strcpy(playerRanking[i][1], "");
        strcpy(playerRanking[i][2], "");
    }
}
// int main() {
//     rankList();
//     //printf("%d", gainPlayerScore(1));
//     clearPlayerRanking();
//     for (int i = 0; i < 10; i++) {
//         char *names = gainPlayerName(i);
//         printf("%s",names);
//         printf("The %d player\'s Score is %d\n", i, gainPlayerScore(i));
//         printf("The %d player\'s Class is %d\n", i, gainPlayerClass(i));
//     }
//     clearPlayerRanking();
//     return 0;
// }



// const char *tmp = "This string literal is arbitrary";

// 检查字符串中是否有某字符串
// 目前没有用到
// int test2(int argc, char *argv[]){
//     char *ret;

//     ret = strstr(tmp, "iteral");
//     if (ret)
//         printf("found substring at address %p\n", ret);
//     else
//         printf("no substring found!\n");

//     exit(EXIT_SUCCESS);
// }


// 打开并写入文件
// 未完善
typedef struct Gamer//定义玩家的结构
{
    int num;//对局数
    int sum;//积分
    char name[20];//玩家名
    struct Gamer* pnext;
}GAMER;
GAMER* pGamer = NULL;//定义链表的头结点
FILE* fp = NULL;//定义文件指针
//char filename[20] = GAMERs;//文件名
char filename[20];//文件名
//创建链表
void CreateList()
{
    pGamer = (GAMER*)malloc(sizeof(GAMER));
    pGamer->pnext = NULL;
}
void OpenFile()
{
    GAMER* pnew = NULL;
    GAMER* ptemp = NULL;
    CreateList();
    ptemp = pGamer;
    fp = fopen(filename, "a+");
    pnew = (GAMER*)malloc(sizeof(GAMER));
    while (1)
    {
        if (fscanf(fp, "%d\t%d\t%s\n", &pnew->num, &pnew->sum, pnew->name) == EOF)
        {
            free(pnew);
            break;
        }
        pnew->pnext = NULL;
        ptemp->pnext = pnew;
        ptemp = ptemp->pnext;

    }


}


int test()
{
    FILE* fp = NULL;
    fp = fopen("./test.file", "w+");
    fprintf(fp, "This is testing for fprintf...\n");
    fputs("This is testing for fputs...\n", fp);
    fclose(fp);
}
