#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <windows.h>

#define MAXKEY 1000	//��ϣ����
#define WORDLEN 50	//�������ڴ��浥�ʵ��ַ�������

typedef struct TkWord{	//����������Ϣ
	int tkcode;	//tokenֵ
	struct TkWord *next;
	char word[50];	//��������
}TkWord,*pTkWord;

enum e_TokenCode // 0~43
{
	/*��������ָ���*/
	TK_PLUS,			//+�Ӻ�
	TK_MINUS,		//-����
	TK_STAR,			// * �Ǻ�
	TK_DIVIDE,		// / ����
	TK_MOD,			// % ���������
	TK_EQ,			// == ���ں�
	TK_NEQ,			// != �����ں�
	TK_LT,			// < С�ں�
	TK_LEQ,			// <= С�ڵ��ں�
	TK_GT,			// > ���ں�
	TK_GEQ,			// >= ���ڵ��ں�
	TK_ASSIGN,		// = ��ֵ����� 
	TK_POINTSTO,		// -> ָ��ṹ���Ա�����
	TK_DOT,			// . �ṹ���Ա�����
	TK_AND,         // & ��ַ�������
	TK_OPENPA,		// ( ��Բ����
	TK_CLOSEPA,		// ) ��Բ����
	TK_OPENBR,		// [ ��������
	TK_CLOSEBR,		// ] ��������
	TK_BEGIN,		// { �������
	TK_END,			// } �Ҵ�����
	TK_SEMICOLON,	// ; �ֺ�    
	TK_COMMA,		// , ����
	TK_ELLIPSIS,		// ... ʡ�Ժ�
	TK_EOF,			// �ļ�������

    /* ���� */
    TK_CINT,			// ���ͳ���
    TK_CCHAR,		// �ַ�����
    TK_CSTR,			// �ַ�������

	/* �ؼ��� */
	KW_CHAR,			// char�ؼ���
	KW_SHORT,		// short�ؼ���
	KW_INT,			// int�ؼ���
	KW_VOID,			// void�ؼ���  
	KW_STRUCT,		// struct�ؼ���   
	KW_IF,			// if�ؼ���
	KW_ELSE,			// else�ؼ���
	KW_FOR,			// for�ؼ���
	KW_CONTINUE,		// continue�ؼ���
	KW_BREAK,		// break�ؼ���   
	KW_RETURN,		// return�ؼ���
	KW_SIZEOF,		// sizeof�ؼ���
	//������
	KW_ALIGN,		// __align�ؼ���	
	KW_CDECL,		// __cdecl�ؼ��� standard c call
	KW_STDCALL,     // __stdcall�ؼ��� pascal c call

	/* ��ʶ�� */
	TK_IDENT
};

void tailInsert(pTkWord *pphead ,pTkWord *pptail ,int tkcode ,char *str);//β�巨���뵥��
void printColor(char *str ,int token);//��ӡ��ɫ
void InitKeywords(pTkWord keywords ,int keywordsLen ,pTkWord *tk_HashTable);//����װ�����й�ϣ����
int elf_hash(char *key);//��ϣ����
int getToken(char *str ,TkWord **tk_HashTable);//�Ե���ƥ��Tokenֵ