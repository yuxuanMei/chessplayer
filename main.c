#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*定义棋手信息结构体*/
enum LEVEL {
	//	"10级","9级","8级","7级","6级","5级","4级","3级","2级","1级" 1-10
	//	"1段","2段","3段","4段","5段","6段","7段","8段" 11-18
	//	"一段","二段","三段","四段","五段","六段","七段","八段","九段 错误信息" 19-27
	shiji = 1, jiuji, baji, qiji, liuji, wuji, siji, sanji, erji, yiji,
	fyiduan, ferduan, fsanduan, fsiduan, fwuduan, fliuduan, fqiduan, fbaduan,
	chuduan, erduan, sanduan, siduan, wuduan, liuduan, qiduan, baduan, jiuduan, wa
};
struct chessplayer {
	/*编号 姓名 身份 段位 积分 数字编号*/
	char num[10], name[128], id[5];
	enum LEVEL level;
	int rating, dnum;
};
int main() {
	/*主要功能函数*/
	void ShowMainMenu();
	void GetFromFile();
	void SaveIntoFile();
	void ShowList();
	void Inquire();
	void Add();
	void Delete();
	void Update();
	void Statistics();
	void Sort();
	void Out();
	/*次要功能函数*/
	char * showlevel();
	int inlevel();
	int option();
	bool check();
	void Inquiresub();
	void Statisticssub();
	bool cmp1();
	bool cmp2();
	
	int nn=0, *n;
	int op;
	struct chessplayer a[100], *p;
	p = a, n = &nn;
	while (1) {
		ShowMainMenu();
		op=option();
		printf("\n");
		switch (op) {
			case 1: GetFromFile(p, n);  	ShowList(p, *n); 		break;
			case 2: SaveIntoFile(p, nn); 	ShowList(p, *n); 		break;
			case 3: ShowList(p, *n); 								break;
			case 4:	Inquire(p, nn);									break;
			case 5:	Add(p, n);										break;
			case 6:	Delete(p, n);									break;
			case 7:	Update(p, nn);									break;
			case 8:	Statistics(p, nn);								break;
			case 9:	Sort(p, nn);									break;
			case 0: Out();											break;
			default:printf("-- 输入错误，请重新输入QwQ --\r\n\n");	break;
		}
	}
	return 0;
}
char * showlevel(enum LEVEL x) {
	switch (x) {
		case shiji:		return "10级";	
		case jiuji:		return "9级"; 	
		case baji:		return "8级"; 	
		case qiji:		return "7级"; 	
		case liuji:		return "6级"; 	
		case wuji:		return "5级"; 	
		case siji:		return "4级"; 	
		case sanji:		return "3级"; 	
		case erji:		return "2级";   
		case yiji:		return "1级";   
		case fyiduan:	return "1段"; 
		case ferduan:	return "2段"; 
		case fsanduan:	return "3段";
		case fsiduan:	return "4段";		
		case fwuduan:	return "5段"; 
		case fliuduan:	return "6段"; 
		case fqiduan:	return "7段"; 
		case fbaduan:	return "8段"; 
		case chuduan:	return "初段";
		case erduan:	return "二段";
		case sanduan:	return "三段";
		case siduan:	return "四段";
		case wuduan:	return "五段";
		case liuduan:	return "六段";
		case qiduan:	return "七段";
		case baduan:	return "八段";
		case jiuduan:	return "九段";
		default:		break;	
	}
	return "错误信息";
}
int inlevel(char x[]) {
	if (strcmp(x, "10级") == 0)  return shiji;
	if (strcmp(x, "9级") == 0)   return jiuji;
	if (strcmp(x, "8级") == 0)   return baji;
	if (strcmp(x, "7级") == 0)   return qiji;
	if (strcmp(x, "6级") == 0)   return liuji;
	if (strcmp(x, "5级") == 0)   return wuji;
	if (strcmp(x, "4级") == 0)   return siji;
	if (strcmp(x, "3级") == 0)   return sanji;
	if (strcmp(x, "2级") == 0)   return erji;
	if (strcmp(x, "1级") == 0)   return yiji;
	if (strcmp(x, "1段") == 0)   return fyiduan;
	if (strcmp(x, "2段") == 0)   return ferduan;
	if (strcmp(x, "3段") == 0)   return fsanduan;
	if (strcmp(x, "4段") == 0)   return fsiduan;
	if (strcmp(x, "5段") == 0)   return fwuduan;
	if (strcmp(x, "6段") == 0)   return fliuduan;
	if (strcmp(x, "7段") == 0)   return fqiduan;
	if (strcmp(x, "8段") == 0)   return fbaduan;
	if (strcmp(x, "初段") == 0)  return chuduan;
	if (strcmp(x, "二段") == 0)  return erduan;
	if (strcmp(x, "三段") == 0)  return sanduan;
	if (strcmp(x, "四段") == 0)  return siduan;
	if (strcmp(x, "五段") == 0)  return wuduan;
	if (strcmp(x, "六段") == 0)  return liuduan;
	if (strcmp(x, "七段") == 0)  return qiduan;
	if (strcmp(x, "八段") == 0)  return baduan;
	if (strcmp(x, "九段") == 0)  return jiuduan;
	return wa;
}
int option(){
	char a[100];
	int i=0;
	while(scanf("%c",&a[i])&&a[i]!='\n') i++;
	if(i>=2) return -1;
	else return (a[0]-'0');
}
void ShowMainMenu() {
	printf("/********  WELCOME TO 围棋棋手管理系统  *********/\r\n");
	printf("     ····················\r\n");
	printf("     ·    [1]  从本地文件导入棋手信息     ·\r\n");
	printf("     ·    [2]  保存棋手信息至本地文件     ·\r\n");
	printf("     ·    [3]  显示棋手信息               ·\r\n");
	printf("     ·    [4]  查询棋手信息               ·\r\n");
	printf("     ·    [5]  增加棋手信息               ·\r\n");
	printf("     ·    [6]  删除棋手信息               ·\r\n");
	printf("     ·    [7]  修改棋手信息               ·\r\n");
	printf("     ·    [8]  统计棋手信息               ·\r\n");
	printf("     ·    [9]  对棋手信息进行排序         ·\r\n");
	printf("     ·    [0]  退出系统                   ·\r\n");
	printf("     ····················\r\n");
	printf("/************************************************/\r\n");
	printf("-- 请选择功能0v0： ");
}
void GetFromFile(struct chessplayer *p, int *n) {
	char tt[50];//暂时存放level
	FILE *fp;
	fp = fopen("playerslist.txt", "r");
	if (fp == NULL) {
		printf("-- 无法打开文件QwQ --\r\n");
		return;
	} else {
		fscanf(fp, "%d\n", n);
		int i;
		for (i = 1; i <= *n; i++, p++) {
			fscanf(fp, "%s %s %s %s %d\n", p->num, p->name, p->id, tt, &p->rating);
			p->level = inlevel(tt);
			p->dnum = (p->num[1] - '0') * 100 + (p->num[2] - '0') * 10 + (p->num[3] - '0');
		}
		printf("导入成功！结果如下o(￣▽￣)ｄ\n");
	}
	fclose(fp);
}
void SaveIntoFile(struct chessplayer *p, int n) {
	if (n == 0) {
		printf("--无数据，还要保存吗O.O?\n--【1】 听我的，保存\n--【2】 听你的，不保存\n--请输入你的选择： ");
		int op;
		op=option();
		printf("\n");
		if (op == 2) return;
	}
	FILE *fp;
	fp = fopen("playerslist.txt", "w");
	fprintf(fp, "%d\n", n);
	int i;
	for (i = 1; i <= n; i++, p++) {
		fprintf(fp, "%s %s %s %s %d\n", p->num, p->name, p->id, showlevel(p->level), p->rating);
	}
	printf("--保存成功!保存结果如下o(￣▽￣)ｄ\n");
	fclose(fp);
}
void ShowList(struct chessplayer *p, int cnt) {
	printf("--------------------------------------------------\n");
	if (cnt == 0) printf("          怎么办鸭，没有数据鸭(·_·)\n");
	else {
		printf("%-10s %-10s %-10s %-10s %-10s\n", "棋手编号", "棋手姓名", "棋手身份", "棋手段位", "等级分");
		int i;
		for (i = 1; i <= cnt; i++, p++) {
			printf("%-10s %-10s %-10s %-10s %-10d\n", p->num, p->name, p->id, showlevel(p->level), p->rating);
		}
	}
	printf("--------------------------------------------------\n\n");
}
void Inquire();
void Inquiresub(struct chessplayer *p, int op, int n) {
	char temp[50];
	char *x[4] = {"身份", "姓名", "段位"};
	int i, num = 0; //num记录有几个目标
	printf("\n--请输入查询的%s： ", x[op - 1]);
	scanf("%s", temp); getchar();
	printf("\n查询结果如下o(￣▽￣)ｄ\n--------------------------------------------------\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "棋手编号", "棋手姓名", "棋手身份", "棋手段位", "等级分");
	for (i = 1; i <= n; i++, p++) {
		char *y[4] = {p->id, p->name, showlevel(p->level)};
		if (strcmp(temp, y[op - 1]) == 0) {
			num++;
			printf("%-10s %-10s %-10s %-10s %-10d\n", p->num, p->name, p->id, showlevel(p->level), p->rating);
		}
	}
	printf("共%d人\n", num);
	if (num == 0) printf("          怎么办鸭，没有数据鸭(·_·)\n");
	printf("--------------------------------------------------\n\n");
}
void Inquire(struct chessplayer *p, int n) {
	printf("--查询什么呢O.O?\n--【1】按棋手身份查询\n--【2】按棋手姓名查询\n");
	printf("--【3】按棋手段位查询\n--【4】退出当前功能\n请输入你的选择： ");
	int op;
	op=option();
	switch (op) {
		case 1:	case 2:	case 3:
			Inquiresub(p, op, n);
			Inquire(p,n);
			break;
		case 4:	printf("\n");	return;
		default:
			printf("-- 输入错误，请重新输入QwQ --\r\n\n");
			break;
	}
}
bool check(struct chessplayer *p){
	if(p->num[0]!='P') return false;
	if(strcmp(p->id,"职业")!=0&&strcmp(p->id,"业余")!=0) return false;
	if(strcmp(p->id,"职业")==0&&(p->level<=fbaduan||p->level>jiuduan)) return false;
	if(strcmp(p->id,"业余")==0&&(p->level<shiji||p->level>fbaduan)) return false;
	else return true;
}
void Add(struct chessplayer *p, int *n) {
	int i, op;
	char tnum[10], tt[50];//暂时存放level;
	printf("--请按以下格式输入1位选手（中间用空格隔开）：\n");
	printf("%s %s %s %s %s\n", "棋手编号", "棋手姓名", "棋手身份", "棋手段位", "等级分");
	p += *n ;
	scanf("%s%s%s%s%d", p->num, p->name, p->id, tt, &p->rating); getchar();
	p->level = inlevel(tt);
	p->dnum = (p->num[1] - '0') * 100 + (p->num[2] - '0') * 10 + (p->num[3] - '0');
	if(!check(p)){
		printf("--输入信息有误，请重新输入o.O\n\n");
		return;
	}

	printf("\n--添加信息为：\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "棋手编号", "棋手姓名", "棋手身份", "棋手段位", "等级分");
	printf("%-10s %-10s %-10s %-10s %-10d\n", p->num, p->name, p->id, showlevel(p->level), p->rating);
	printf("--确认要添加吗O.O?\n--【1】加加加！\n--【2】还是算了吧\n请输入你的选择： ");
	op=option();
	switch (op) {
		case 1:
			strcpy(tnum, p->num);
			for (i = 1, p--; i <= *n; i++, p--) {
				if (strcmp(tnum, p->num) == 0) {
					printf("\n--已有该棋手信息，请重新输入(·_·)\n\n");
					return;
				}
			}
			printf("--添加成功\n\n");
			(*n)++;
			p++;
			SaveIntoFile(p, *n);
			ShowList(p, *n);
			break;
		case 2:		return;
		default:	printf("-- 输入错误，请重新输入QwQ --\r\n\n");	break;
	}
}
void Delete(struct chessplayer *p, int *n) {
	char tnum[10], tname[50];
	int i, flag = 0, op;
	printf("--请输入要删除的棋手编号 棋手姓名： ");
	scanf("%s%s", tnum, tname); getchar();
	for (i = 1; i <= *n; i++, p++) {
		if (strcmp(tnum, p->num) == 0 && strcmp(tname, p->name) == 0) {
			flag = 1;
			break;
		}
	}
	if (!flag) {
		printf("\n--没有该棋手信息鸭，这可怎么办鸭QwQ\n\n");
		return;
	}

	printf("\n--删除信息为：\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "棋手编号", "棋手姓名", "棋手身份", "棋手段位", "等级分");
	printf("%-10s %-10s %-10s %-10s %-10d\n", p->num, p->name, p->id, showlevel(p->level), p->rating);
	printf("--确认要删除吗O.O?\n--【1】删删删！\n--【2】还是算了吧\n请输入你的选择： ");
	op=option();
	struct chessplayer temp;
	switch (op) {
		case 1:
			for (; i < *n; i++, p++) {
				temp = *(p + 1);
				*p = *(p + 1);
				*(p + 1) = temp;
			}
			(*n)--;
			p -= *n;
			printf("删除成功--\n\n");
			SaveIntoFile(p, *n);
			ShowList(p, *n);
			break;
		case 2:		return;
		default:	printf("-- 输入错误，请重新输入QwQ --\r\n\n");	break;
	}
}
void Update(struct chessplayer *p, int n) {
	char tnum[10], tname[50], temp[50], tt[50];
	int i, flag = 0, op, op0, tempnum, t;
	printf("--请输入要修改的棋手编号 棋手姓名： ");
	scanf("%s%s", tnum, tname); getchar();
	for (i = 1; i <= n; i++, p++) {
		if (strcmp(tnum, p->num) == 0 && strcmp(tname, p->name) == 0) {
			flag = 1;
			break;
		}
	}
	if (!flag) {
		printf("\n--没有该棋手信息鸭，这可怎么办鸭QwQ\n\n");
		return;
	}

	printf("\n--修改棋手信息为：\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "棋手编号", "棋手姓名", "棋手身份", "棋手段位", "等级分");
	printf("%-10s %-10s %-10s %-10s %-10d\n", p->num, p->name, p->id, showlevel(p->level), p->rating);
	printf("--修改什么呢O.O?\n--【1】棋手姓名\n--【2】棋手身份\n");
	printf("--【3】棋手段位\n--【4】棋手等级分\nPS：身份段位需一起修改：\n请输入你的选择： ");
	op=option();
	printf("\n--确认要修改吗O.O?\n--【1】改改改！\n--【2】还是算了吧\n请输入你的选择： ");
	op0=option();
	switch (op0) {
		case 1:		break;
		case 2:		return;
		default:	printf("-- 输入错误，请重新输入QwQ --\r\n\n");	return;
	}
	switch (op) {
		case 1:
			printf("\n--请输入修改后的姓名：");
			scanf("%s", temp); getchar();
			strcpy(tt, p->name), strcpy(p->name, temp);
			if(!check(p)){
				printf("--输入信息有误，请重新输入o.O\n\n");
				strcpy(p->name,tt);
				return;
			}
			break;
		case 2:	case 3:
			printf("\n--请输入修改后的身份：");
			scanf("%s", temp); getchar();
			strcpy(tt, p->id), strcpy(p->id, temp);
			printf("\n--请输入修改后的段位：");
			scanf("%s", temp); getchar();
			t = p->level, p->level = inlevel(temp);
			if(!check(p)){
				printf("--输入信息有误，请重新输入o.O\n\n");
				p->level = t;strcpy(p->name,tt);
				return;
			}
			break;
		case 4:
			printf("\n--请输入修改后的等级分：");
			scanf("%d", &tempnum); getchar();
			p->rating = tempnum;
			break;
		default:	printf("\n-- 输入错误，请重新输入QwQ --\r\n\n");	return;
	}
	
	p -= (i - 1);
	printf("\n修改成功--\n\n");
	SaveIntoFile(p, n);
	ShowList(p, n);
}
void Statisticssub(struct chessplayer *p, int op, int n) {
	char temp1[50], temp2[50];
	int i, num = 0;
	if (op == 1) {
		printf("\n--请输入要统计的棋手身份 棋手段位:  ");
		scanf("%s%s", temp1, temp2); getchar();
	}
	printf("\n统计结果如下o(￣▽￣)ｄ\n--------------------------------------------------\n");
	printf("%-10s %-10s %-10s %-10s %-10s\n", "棋手编号", "棋手姓名", "棋手身份", "棋手段位", "等级分");
	for (i = 1; i <= n; i++, p++) {
		if (op == 1 && strcmp(temp1, p->id) == 0 && strcmp(temp2, showlevel(p->level)) == 0) {
			num++;
			printf("%-10s %-10s %-10s %-10s %-10d\n", p->num, p->name, p->id, showlevel(p->level), p->rating);
		}
		if (op == 2 && p->level >= erduan) {
			num++;
			printf("%-10s %-10s %-10s %-10s %-10d\n", p->num, p->name, p->id, showlevel(p->level), p->rating);
		}
		if (op == 3 && strcmp("业余", p->id) == 0) {
			num++;
			printf("%-10s %-10s %-10s %-10s %-10d\n", p->num, p->name, p->id, showlevel(p->level), p->rating);
		}
	}
	printf("共%d人\n", num);
	if (num == 0) printf("          怎么办鸭，没有数据鸭(·_·)\n");
	printf("--------------------------------------------------\n\n");
}
void Statistics(struct chessplayer *p, int n) {
	printf("--统计什么呢O.O?\n--【1】统计某身份某段位棋手总数\n--【2】统计职业二段以上的棋手总数\n");
	printf("--【3】统计业余棋手总数\n--【4】退出当前功能\n请输入你的选择： ");
	int op; //num记录有几个统计信息
	op=option();
	switch (op) {
		case 1:	case 2:	case 3:
			Statisticssub(p, op, n);
			break;
		case 4:		return;
		default:	printf("\n-- 输入错误，请重新输入QwQ --\r\n\n");	break;
	}
}
bool cmp1(struct chessplayer *x, struct chessplayer *y) {
	if (x->rating == y->rating) return x->dnum > y->dnum;
	return x->rating < y->rating;
}
bool cmp2(struct chessplayer *x, struct chessplayer *y) {
	if (x->level == y->level) return x->dnum > y->dnum;
	return x->level < y->level;
}
void Sort(struct chessplayer *p, int n) {
	printf("--统计什么呢O.O?\n--【1】对所有棋手按等级分进行降序排序\n");
	printf("--【2】对职业棋手按段位进行降序排序\n--【3】退出当前功能\n请输入你的选择： ");
	int op, i, j, cnt = 0; //cnt记录有几个统计信息
	struct chessplayer temp, b[100];
	op=option();
	switch (op) {
		case 1:
			for (i = n; i >= 1 ; i--) {
				for (j = 1; j < i ; j++) {
					if (cmp1(p + j - 1, p + j )) {
						temp = *(p + j - 1);
						*(p + j - 1) = *(p + j );
						*(p + j ) = temp;
					}
				}
			}
			printf("\n排序结果如下o(￣▽￣)ｄ\n");
			ShowList(p, n);
			break;
		case 2:
			for (i = 1 ; i <= n ; i++, p++) {
				if (strcmp(p->id, "职业") == 0)b[cnt++] = *p;
			}
			p = b;
			for (i = cnt; i >= 1 ; i--) {
				for (j = 1; j < i ; j++) {
					if (cmp2(p + j - 1, p + j)) {
						temp = *(p + j - 1);
						*(p + j - 1) = *(p + j);
						*(p + j) = temp;
					}
				}
			}
			printf("\n排序结果如下o(￣▽￣)ｄ\n");
			ShowList(p, cnt);
			break;
		case 3:		return;
		default:	printf("\n-- 输入错误，请重新输入QwQ --\r\n\n");	break;
	}
}
void Out() {
	printf("真的要退出吗O.O?\n--【1】退退退！垃圾系统再也不用了！\n--【2】点错了不退了\n请输入你的选择： ");
	int op;
	op=option();
	switch (op) {
		case 1:		printf("感谢您的使用，呜呜呜那我走");	exit(0);
		case 2:		break;
		default:	printf("\n-- 输入错误，请重新输入QwQ --\r\n\n");	break;
	}
}
