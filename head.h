#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <windows.h>

#define MAXKEY 1000	//哈希表长度
#define WORDLEN 50	//申请用于储存单词的字符串长度

typedef struct TkWord{	//包含单词信息
	int tkcode;	//token值
	struct TkWord *next;
	char word[50];	//单词内容
}TkWord,*pTkWord;

enum e_TokenCode // 0~43
{
	/*运算符及分隔符*/
	TK_PLUS,			//+加号
	TK_MINUS,		//-减号
	TK_STAR,			// * 星号
	TK_DIVIDE,		// / 除号
	TK_MOD,			// % 求余运算符
	TK_EQ,			// == 等于号
	TK_NEQ,			// != 不等于号
	TK_LT,			// < 小于号
	TK_LEQ,			// <= 小于等于号
	TK_GT,			// > 大于号
	TK_GEQ,			// >= 大于等于号
	TK_ASSIGN,		// = 赋值运算符 
	TK_POINTSTO,		// -> 指向结构体成员运算符
	TK_DOT,			// . 结构体成员运算符
	TK_AND,         // & 地址与运算符
	TK_OPENPA,		// ( 左圆括号
	TK_CLOSEPA,		// ) 右圆括号
	TK_OPENBR,		// [ 左中括号
	TK_CLOSEBR,		// ] 右中括号
	TK_BEGIN,		// { 左大括号
	TK_END,			// } 右大括号
	TK_SEMICOLON,	// ; 分号    
	TK_COMMA,		// , 逗号
	TK_ELLIPSIS,		// ... 省略号
	TK_EOF,			// 文件结束符

    /* 常量 */
    TK_CINT,			// 整型常量
    TK_CCHAR,		// 字符常量
    TK_CSTR,			// 字符串常量

	/* 关键字 */
	KW_CHAR,			// char关键字
	KW_SHORT,		// short关键字
	KW_INT,			// int关键字
	KW_VOID,			// void关键字  
	KW_STRUCT,		// struct关键字   
	KW_IF,			// if关键字
	KW_ELSE,			// else关键字
	KW_FOR,			// for关键字
	KW_CONTINUE,		// continue关键字
	KW_BREAK,		// break关键字   
	KW_RETURN,		// return关键字
	KW_SIZEOF,		// sizeof关键字
	//不常用
	KW_ALIGN,		// __align关键字	
	KW_CDECL,		// __cdecl关键字 standard c call
	KW_STDCALL,     // __stdcall关键字 pascal c call

	/* 标识符 */
	TK_IDENT
};

void tailInsert(pTkWord *pphead ,pTkWord *pptail ,int tkcode ,char *str);//尾插法插入单词
void printColor(char *str ,int token);//打印颜色
void InitKeywords(pTkWord keywords ,int keywordsLen ,pTkWord *tk_HashTable);//单词装入数列哈希数列
int elf_hash(char *key);//哈希函数
int getToken(char *str ,TkWord **tk_HashTable);//对单词匹配Token值