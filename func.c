#include "head.h"

void tailInsert(pTkWord *pphead ,pTkWord *pptail ,int tkcode ,char *str)//β�巨���뵥��
{
	pTkWord pcur=(pTkWord)malloc(sizeof(TkWord));
	memset(pcur,0,sizeof(pTkWord));
	pcur->tkcode=tkcode;
	strcpy(pcur->word,str);	//����pcur���
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

void printColor(char *str ,int token)//��ӡ��ɫ
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//�ú������ڻ�ȡһ����׼����ľ��
	if (token >= TK_IDENT)
    {
	    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);//��ʶ����ɫ
	}
	else if (token >= KW_CHAR)
	{
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//�ؼ�����ɫ
	}
	else if (token >= TK_CINT)
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//������ɫ
	}
	else
	{
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);//�������ɫ
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

void InitKeywords(pTkWord keywords ,int keywordsLen ,pTkWord *tk_HashTable)//����װ�����й�ϣ����
{
	int i;
	for (i = 0; i < keywordsLen; i++)
	{
		tk_HashTable[elf_hash(keywords[i].word)]=&keywords[i];
	}
}

int elf_hash(char *key)//��ϣ����
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

int getToken(char *str ,pTkWord *tk_HashTable)//�Ե���ƥ��Tokenֵ
{
	int i=0;		//str���±�
	int flag=1;	//0����ѭ��
	int token;
	int hash=elf_hash(str);	//��ϣֵ
	if (NULL==tk_HashTable[hash])	//����ͻ
	{
		while (str[i]!='\0')
		{
			if (!(str[i]>='0' && str[i]<='9'))
			{
				flag=0;
				break;
			}//str[i]��������ʱflag��Ϊ0������whileѭ��
			i++;
		}//while
		if (1==flag)	//������
		{
			token=TK_CINT;	//���ͳ���
		}else if ('\''==str[0])	//���������ҵ����ſ�ͷ
		{
			token=TK_CCHAR;	//�ַ�����
		}else if('\"'==str[0])		//����������˫���ſ�ͷ
		{
			token=TK_CSTR;	//�ַ�������
		}else				//��������
		{
			token=TK_IDENT;	//�ж�Ϊ��ʶ��
		}
		return token;
	}//if  ����ͻ
	token=tk_HashTable[hash]->tkcode;	//��ϣ�����Ѵ��У�ֱ��ȡ��tkcode
}