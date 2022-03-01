#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 27					//每行最大字节数
 
 /*
 游戏记录、排行榜
 仅记录人机对战模式的排行情况
 游戏记录文件是一个txt，里面是如下格式：
  - <人机对局次数>,<积分>,<玩家名>
 积分计算方法：人机对战一局，如果输了不扣分，赢了的话积分等于棋子数量，积分每局叠加
 下面的函数将文件中的数据格式化为了一个三维字符数组，并且按照积分从大到小排列
 如示例文件，是这样：
 5,20,dog
 1,40,uufly
 2,30,ufdsaf
 8,56,sadas

 那么最后返回的三维数组是如下形式：
{
    {{8}，{56}，{sadas}}，
    {{1}，{40}，{uufly}}，
    {{2}，{30}，{ufdsaf}}，
    {{5}，{20}，{dog}}
}

 需要写什么？
 比较当前玩家名是否在文件中存在，我会传一个字符串给你，你需要比较数据中是否有该玩家，
 如果有，那么对局+1
 如果没有，那么在文件最后加入这个玩家，对局+1
 游戏结束后，我会传一个积分给你，你需要写在文件里


 */
 // 获取排行榜信息，并返回
int main() 
{ 
	FILE *fp;
    FILE *fp1; 
    int count = 1, k = 0;
    int split;
	char strLine[MAX_LINE];	//读取缓冲区
    char playerRanking[50][3][11], tempChar[1][3][11];
	if((fp = fopen("./new.txt","r")) == NULL)	// 判断文件是否存在及可读
	{ 
		printf("Open Falied!"); 
		return -1; 
	} 
    if ((fp1=fopen("./new.txt","a"))==NULL)	// 打开指定文件，如果文件不存在则新建该文件
	{
		printf("Open Failed.\n");
		return -1;
	} 
    // 将每一行的数据按照规则保存在playerRanking中
    for(int i = 0;!feof(fp);i++)	//循环读取每一行，直到文件尾
	{ 
        k = 0;
		fgets(strLine, MAX_LINE, fp); // 将fp所指向的文件一行内容读到strLine缓冲区
		//printf("%s", strLine);
        split = 1;
        for(int j = 0; j < sizeof(strLine);j++){
            if(strLine[j] == ','){
                split++;
                k = 0;
                continue;
            }
            if(strLine[j] == '\0'){
                j = sizeof(strLine);
                continue;
            }
            playerRanking[i][split-1][k] = strLine[j];
            k++;
        }
    }
    int ROW=0;
    for (int row = 0; row<50;row++) {
        if (playerRanking[row][0][0] != '\0') ROW++;
        else if(playerRanking[row][0][0] == '\0') break;
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
	fclose(fp);	 // 关闭读文件
    fclose(fp1); // 关闭写文件
	return 0; 
}

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
char filename[20]=GAMERs;//文件名
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
   FILE *fp = NULL;
 
   fp = fopen("./test.file", "w+");
   fprintf(fp, "This is testing for fprintf...\n");
   fputs("This is testing for fputs...\n", fp);
   fclose(fp);
}
