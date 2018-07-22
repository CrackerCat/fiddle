// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include <windivert.h>
#include "divert.h"
#include "packet_stream.h"

#include <process.h>         //���߳�

#include <pcap.h>
#include <direct.h>          //�����ļ�·������ȡ�ļ����µ��ļ�


#define MAXBUF 1500

struct agrclist {         //�̴߳��νṹ��   һ���ǹ����̵߳Ĺ����ַ���  һ�����̵߳�ֹͣ������
	char *filter;
	BOOL &command;
};

#define PURPLE() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
#define WHITE() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#define RED() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED );
#define BLUE() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_BLUE);
#define GREEN() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN );
#define CYAN() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_GREEN | FOREGROUND_BLUE);
#define YELLOW() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);


unsigned __stdcall  fiddle(void *argv);    //ץ��
unsigned __stdcall divert(void *argv);      //���
STREAM_LIST * read_packet(char *packet);   //�����ݰ�����������     
BOOL add2Stream(PAC p, STREAM_LIST &s);       //�ж�һ�����Ƿ�����һ����
STREAM_LIST* create_stream(PAC p, STREAM_LIST* sl);     //����һ��������
void show_stream_list(STREAM_LIST *sl);         //չʾ������һ��������������
void show_stream(char *path,STREAM_LIST sl);       //չʾ
STREAM * select_packet_from_file(char *path,int *c, int x);      //���ļ���ѡ���
void show_packets(STREAM *s);                //չʾһ�����ݰ�
int find_file();

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
