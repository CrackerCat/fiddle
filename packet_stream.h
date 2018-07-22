#pragma once
#include "stdafx.h"

typedef struct
{
	unsigned char packet[1500];    //һ�����������ݰ���������ͷ��������
	int packet_len;   //���ݰ�����Ч����   ��freadʱ���õ�
	int ID;        //����ID��������ʱ�丳ֵ���������������
} PAC;

struct Stream_list          //������������
{
	UINT32 src_addr;
	UINT32 dst_addr;
	UINT16 src_port;
	UINT16 dst_port;   //ip�Ͷ˿���Ϊ���ĵ�һ��ʶ

	int stream_ID;  //ID��Ϊ���ĵڶ���ʶ  ��Ϊ��ͬ��ip�Ͷ˿��п��ܵڶ��ν������ӡ�

	//STREAM stream;     //������  �����д�Ű�ID  ���鲻�������
	//PAC packet[135];
	int packet[200];     //������   �����ݰ���id����ʶ����ʡ�ռ䡣
	int packet_number;       //��������
	
	struct Stream_list *next;
	//PAC packet[100]
};
typedef struct Stream_list STREAM_LIST;

struct Stream      //���ݰ�������   ����  ������
{
	unsigned char packet[1500];
	int packet_len;
	struct Stream *next;
	
};
typedef struct Stream STREAM;