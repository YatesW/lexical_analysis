#include "head.h"

void tailInsert(pTkWord *pphead ,pTkWord *pptail ,int tkcode ,char *str)//尾插法插入单词
{
	pTkWord pcur=(pTkWord)malloc(sizeof(TkWord));
	memset(pcur,0,sizeof(pTkWord));
	pcur->tkcode=tkcode;
	strcpy(pcur->word,str);	//构建pcur结点
	if (NULL==*pphead)
	{
		*pphead=pcur;
		*pptail=pcur;
	}
	else
	{
		(*pptail)->next=pcur;
		*pptail=pcur;
	}
}

void printColor(char *str ,int token)//打印颜色
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//该函数用于获取一个标准输出的句柄
	if (token >= TK_IDENT)
    {
	    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);//标识符灰色
	}
	else if (token >= KW_CHAR)
	{
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//关键字绿色
	}
	else if (token >= TK_CINT)
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//常量褐色
	}
	else
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);//运算符红色
	}
	if (-1 == str[0]) 
	{
		printf("\n End_Of_File!");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	} 
	else 
	{
		printf("%s", str);
	}
}

void InitKeywords(pTkWord keywords ,int keywordsLen ,pTkWord *tk_HashTable)//单词装入数列哈希数列
{
	int i;
	for (i = 0; i < keywordsLen; i++)
	{
		tk_HashTable[elf_hash(keywords[i].word)]=&keywords[i];
	}
}

int elf_hash(char *key)//哈希函数
{
	int h = 0, g;
	while (*key)
	{
		h = (h << 4) + *key++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MAXKEY;
}

int getToken(char *str ,pTkWord *tk_HashTable)//对单词匹配Token值
{
	int i=0;		//str的下标
	int flag=1;	//0跳出循环
	int token;
	int hash=elf_hash(str);	//哈希值
	if (NULL==tk_HashTable[hash])	//不冲突
	{
		while (str[i]!='\0')
		{
			if (!(str[i]>='0' && str[i]<='9'))
			{
				flag=0;
				break;
			}//str[i]不是数字时flag置为0，跳出while循环
			i++;
		}//while
		if (1==flag)	//是数字
		{
			token=TK_CINT;	//整型常量
		}else if ('\''==str[0])	//不是数字且单引号开头
		{
			token=TK_CCHAR;	//字符常量
		}else if('\"'==str[0])		//不是数字且双引号开头
		{
			token=TK_CSTR;	//字符串常量
		}else				//不是数字
		{
			token=TK_IDENT;	//判定为标识符
		}
		return token;
	}//if  不冲突
	token=tk_HashTable[hash]->tkcode;	//哈希数列已存有，直接取出tkcode
}