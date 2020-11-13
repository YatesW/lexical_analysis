#include "head.h"
int main()
{
	static TkWord keywords[]={
	/* ��������ָ��� */
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
	/* ���� */
	{TK_CINT,NULL,"���ͳ���"},
	{TK_CCHAR,NULL,"�ַ�����"},
	{TK_CSTR,NULL,"�ַ�������"},
	/* �ؼ��� */
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
	/* ��ʶ�� */
	{0}		//Сbug:���������ž���Ϊ��ʶ��
	};

	TkWord *tk_HashTable[MAXKEY]={0};	//���ʵĹ�ϣ��
	int keywordsLen=sizeof(keywords)/sizeof(TkWord);	//�ṹ�������Ա����
	int token;	//���ʵ�tokenֵ
	int i=0;	//ѭ����ȡ�ַ�
	char scanner;	//ɨ���ַ�
	char container[WORDLEN]={0};//��¼�ַ�������
	pTkWord phead=NULL;
	pTkWord ptail=NULL;
	FILE *fp=fopen("Helloworld.txt","r");
	InitKeywords(keywords,keywordsLen,tk_HashTable);
Label1:
	while ((scanner=fgetc(fp))!=EOF)	//���ļ�
	{
		if ('\''==scanner ||'\"'==scanner && 0==i)	//�ַ������ַ�����ͷ
		{
			container[i]=scanner;	//������'��"
			i++;
			while (scanner!='\"' && scanner!='\'')	//��ȡ�ַ������ַ�������
			{
				container[i]=scanner;
				i++;
			}//while �ַ������ַ�������
			container[i]=scanner;	//������'��"
			token=getToken(container,tk_HashTable);
			printColor(container,token);
			tailInsert(&phead,&ptail,token,container);
			memset(container,0,WORDLEN);
			i=0;
			goto Label1;
		}//if  �ַ������ַ�����ͷ
		
		if (scanner>='a' && scanner<='z' || scanner>='A' && scanner<='Z' || scanner>='0' && scanner<='9')//��ĸ�����ֿ�ͷ
		{
			container[i]=scanner;
			i++;
		}else if (scanner==' ' || scanner=='\n' || scanner=='\t')
		{
			if (i!=0)	//���ֵ��ʽ�����־
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
			if (i!=0)	//���������ַ�Ҳ��Ϊ���ʽ���
			{
				token=getToken(container,tk_HashTable);
				printColor(container,token);
				tailInsert(&phead,&ptail,token,container);
				memset(container,0,WORDLEN);
				i=0;
			}
			//i=0  ����ͷλ�ó��������ַ�
			container[i]=scanner;
			token=getToken(container,tk_HashTable);
			printColor(container,token);
			tailInsert(&phead,&ptail,token,container);
			memset(container,0,WORDLEN);
			i=0;
		}//else
	}//while  ���ļ�
	printf("\n");
	system("pause");
}