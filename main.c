#include "head.h"
int main()
{
	static TkWord keywords[]={
	/* 运算符及分隔符 */
	{TK_PLUS,NULL,"+"},
	{TK_MINUS,NULL,"-"},
	{TK_STAR,NULL,"*"},
	{TK_DIVIDE,NULL,"/"},
	{TK_MOD,NULL,"%"},
	{TK_EQ,NULL,"=="},
	{TK_NEQ,NULL,"!="},
	{TK_LT,NULL,"<"},
	{TK_LEQ,NULL,"<="},
	{TK_GT,NULL,">"},
	{TK_GEQ,NULL,">="},
	{TK_ASSIGN,NULL,"="},
	{TK_POINTSTO,NULL,"->"},
	{TK_DOT,NULL,"."},
	{TK_AND,NULL,"&"},
	{TK_OPENPA,NULL,"("},
	{TK_CLOSEPA,NULL,")"},
	{TK_OPENBR,NULL,"["},
	{TK_CLOSEBR,NULL,"]"},
	{TK_BEGIN,NULL,"{"},
	{TK_END,NULL,"}"},
	{TK_SEMICOLON,NULL,";"},
	{TK_COMMA,NULL,","},
	{TK_ELLIPSIS,NULL,"..."},
	{TK_EOF,NULL,"End_Of_File"},
	/* 常量 */
	{TK_CINT,NULL,"整型常量"},
	{TK_CCHAR,NULL,"字符常量"},
	{TK_CSTR,NULL,"字符串常量"},
	/* 关键字 */
	{KW_CHAR,NULL,"char"},
	{KW_SHORT,NULL,"short"},
	{KW_INT,NULL,"int"},
	{KW_VOID,NULL,"void"},
	{KW_STRUCT,NULL,"struct"},
	{KW_IF,NULL,"if"},
	{KW_ELSE,NULL,"else"},
	{KW_FOR,NULL,"for"},
	{KW_CONTINUE,NULL,"continue"},
	{KW_BREAK,NULL,"break"},
	{KW_RETURN,NULL,"return"},
	{KW_SIZEOF,NULL,"sizeof"},
	{KW_ALIGN,NULL,"__align"},
	{KW_CDECL,NULL,"__cdecl"},
	{KW_STDCALL,NULL,"__stdcall"},
	/* 标识符 */
	{0}		//小bug:将其他符号均视为标识符
	};

	TkWord *tk_HashTable[MAXKEY]={0};	//单词的哈希表
	int keywordsLen=sizeof(keywords)/sizeof(TkWord);	//结构体数组成员个数
	int token;	//单词的token值
	int i=0;	//循环读取字符
	char scanner;	//扫描字符
	char container[WORDLEN]={0};//记录字符串内容
	pTkWord phead=NULL;
	pTkWord ptail=NULL;
	FILE *fp=fopen("Helloworld.txt","r");
	InitKeywords(keywords,keywordsLen,tk_HashTable);
Label1:
	while ((scanner=fgetc(fp))!=EOF)	//读文件
	{
		if ('\''==scanner ||'\"'==scanner && 0==i)	//字符或者字符串开头
		{
			container[i]=scanner;	//读入左'或"
			i++;
			while (scanner!='\"' && scanner!='\'')	//读取字符或者字符串内容
			{
				container[i]=scanner;
				i++;
			}//while 字符或者字符串内容
			container[i]=scanner;	//读入右'或"
			token=getToken(container,tk_HashTable);
			printColor(container,token);
			tailInsert(&phead,&ptail,token,container);
			memset(container,0,WORDLEN);
			i=0;
			goto Label1;
		}//if  字符或者字符串开头
		
		if (scanner>='a' && scanner<='z' || scanner>='A' && scanner<='Z' || scanner>='0' && scanner<='9')//字母或数字开头
		{
			container[i]=scanner;
			i++;
		}else if (scanner==' ' || scanner=='\n' || scanner=='\t')
		{
			if (i!=0)	//出现单词结束标志
			{
				token=getToken(container,tk_HashTable);
				printColor(container,token);
				tailInsert(&phead,&ptail,token,container);
				memset(container,0,WORDLEN);
				i=0;
			}
			printf("%c",scanner);
		}else
		{
			if (i!=0)	//出现其他字符也视为单词结束
			{
				token=getToken(container,tk_HashTable);
				printColor(container,token);
				tailInsert(&phead,&ptail,token,container);
				memset(container,0,WORDLEN);
				i=0;
			}
			//i=0  即开头位置出现其他字符
			container[i]=scanner;
			token=getToken(container,tk_HashTable);
			printColor(container,token);
			tailInsert(&phead,&ptail,token,container);
			memset(container,0,WORDLEN);
			i=0;
		}//else
	}//while  读文件
	printf("\n");
	system("pause");
}