// final_test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"




void print() {

	PURPLE();  //��ɫ����
	printf("please input the operation��\n");
	printf("ץ��: -fiddle \n");
	printf("���Ӧ��������̣� -divert\n");
	printf("����ץ���� -stopfiddle\n");
	printf("ֹͣ��ϣ� -stopdivert\n");
	printf("�˳��� -quit\n");
	printf("������б� -showlist\n");
	putchar('\n');
	WHITE();
}


int main()
{
	
	

	char s[11];    //�û��ʼ������ 

	HANDLE fiddle_handle;             //�߳̾��
	HANDLE divert_handle;
	unsigned int fiddle_threadid;    //�̵߳�id
	unsigned int divert_threadid;

	int  fiddle_command = 0;         //�����̵߳Ľ���
	int  divert_command = 0;

	print();  //��ӡ�û�����ѡ��

	while (scanf_s("%s",s,11), s != NULL) {
		
		if (strcmp(s, "fiddle") == 0) {    //��ʼ��׽�߳�
			char filter[100];
			//int com;
			printf("please input the filter: \n");
			fgets(s, 2, stdin);     //�������з�
			fgets(filter, 100, stdin);
			
			//scanf("%s", filter);
			printf("fiddle :%s\n", filter);
			fiddle_command = 1;
			agrclist grclist = { filter ,fiddle_command }, *pmagrclist;
			pmagrclist = &grclist;
			fiddle_handle = (HANDLE)_beginthreadex(NULL, 0, &fiddle, pmagrclist, 0, &fiddle_threadid);
			//_beginthread(netdump, 0, pmagrclist);
			printf("fiddle is starting!\n");
			putchar('\n');
		}
		else if (strcmp(s, "stopfiddle") == 0) {   //ֹͣ��׽�߳�
			if (fiddle_command == 0) {
				printf("�߳�û��������\n");
			}
			else {
				fiddle_command = 0;		 //�����ȴ�
				printf("�����ĵȴ������ڰ�ȫ�˳�������������\n");
				WaitForSingleObject(fiddle_handle, INFINITE);  //�ȴ��߳̽���
				printf("fiddle thread is end!\n");

				PURPLE();
				printf("�Ƿ�Ҫ�����ļ������� -save  ������ -notsave\n");
				WHITE();
				char issave[8];
				scanf_s("%s", issave,8);
				if (strcmp("save", issave) == 0) {
					PURPLE();
					printf("�������ļ����� -xxx\n");
					WHITE();
					char filename[20];
					scanf_s("%s", filename,20); //ȱ��һ���ж�
					rename("tmp.pcap", filename);
					printf("success save \n");
					//rename("tmp.pcap",strcat(filename,".pcap"));
				}
				else if (strcmp("notsave", issave) == 0) {
					system("del tmp.pcap");
				}
				else {
					printf("������Ч,Ĭ�ϲ�����\n");
					system("del tmp.pcap");
				}
				printf("stopfiddle success \n");
			}
		}
		else if (strcmp(s, "divert") == 0) {    //��ʼ���Ӧ��
			char filter[100];
			printf("please input the filter: \n");
			fgets(s, 2, stdin);     //�������з�
			fgets(filter, 100, stdin);
		
			//scanf("%s", filter);
			printf("divert :%s\n", filter);
			divert_command = TRUE;
			agrclist grclist = { filter ,divert_command }, *pmagrclist;
			pmagrclist = &grclist;
			//_beginthread(divert, 0, pmagrclist);
			divert_handle = (HANDLE)_beginthreadex(NULL, 0, &divert, pmagrclist, 0, &divert_threadid);
			putchar('\n');

		}
		else if (strcmp(s, "stopdivert") == 0) {   //ֹͣ��׽�߳�
			if (divert_command == TRUE) {
				divert_command = FALSE;
				printf("�����ĵȴ������ڰ�ȫ�˳�������������\n");
				printf("divert thread is end!\n");
				WaitForSingleObject(fiddle_handle, INFINITE);  //�ȴ��߳̽���
				printf("stopdivert success \n");
			}
			else {
				printf("�߳�û������\n");
			}
			
		}
		else if (strcmp(s, "quit") == 0) {   //ֹͣ�����̣߳���������		
			if (fiddle_command == 1) {
				fiddle_command = FALSE;
				WaitForSingleObject(fiddle_handle, INFINITE);  //�ȴ��߳̽���
			}
			if (divert_command == 1) {
				divert_command = FALSE;
				WaitForSingleObject(divert_handle, INFINITE);  //�ȴ��߳̽���
			}
			printf("quit\n");
			exit(0);
		}
		else if (strcmp(s, "showlist") == 0) {   //��ʼ��׽����չʾ���б�
			char operation[15];
			PURPLE();
			printf("����Ҫ���еĲ���: ���ѱ����ļ� -open�����²�����ļ�: -refiddle, ��������-update , ������һ��; -back \n");
			WHITE();
			while (scanf_s("%s", operation,15), operation != NULL) {
				if (strcmp("open", operation) == 0) {
					printf("�ҵ������ļ���");
					find_file();

					PURPLE();
					printf("����Ҫ�򿪵��ļ���: -*.pcap ,������һ�㣺 -back \n");
					WHITE();
					char filename[10];

					scanf_s("%s", filename,10);
					if (strcmp("back", filename) == 0) {
						break;
					}
					else {
						STREAM_LIST * sl = read_packet(filename);
						if (sl == NULL) {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
							printf("��Ǹ��û���ҵ�������\n");
							putchar('\n');
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							break;
						}
						show_stream_list(sl);
						char vorb[7];
						PURPLE();
						printf("�鿴ĳ���������� -view, ������������ -update, ������һ�㣺 -back \n");
						WHITE();
						while (scanf_s("%s", vorb,7), vorb != NULL) {
							if (strcmp("view", vorb) == 0) {
								int stream;
								STREAM_LIST * cur = sl;  //sl�ı���
								STREAM_LIST * aim = NULL;
								printf("������ID�� -xxxxxxxxxx \n");
								if (scanf_s("%d", &stream), stream != NULL) {
									while (cur != NULL) {
										if (cur->stream_ID == stream) {
											aim = cur;
											//free(cur);
											break;
										}
										cur = cur->next;
									}
									if (aim == NULL) {
										printf("û��������\n");
									}
									else {
										show_stream(filename, *aim);
										SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
									}
								}
							}
							else if (strcmp("back", vorb) == 0) {
								break;
							}
							else if (strcmp("update", vorb) == 0) {
								//start capture
								char filename[9] = "tmp.pcap";
								STREAM_LIST * sl = read_packet(filename);
								show_stream_list(sl);
								putchar('\n');
								//continue;
							}
							else {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
								printf("������Ч��������һ��\n");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
								break;
							}
							PURPLE();
							printf("�鿴ĳ���������� -view, ������������ -update, ������һ�㣺 -back \n");
							WHITE();
						}
						putchar('\n');
					}
				}
				else if (strcmp("refiddle", operation) == 0) {
					if (fiddle_command == 1) {

					}
					else {
						char filter[100];
						//int com;
						printf("please input the filter: \n");
						fgets(s, 2, stdin);     //�������з�
						fgets(filter, 100, stdin);
						//scanf("%s", filter);
						printf("fiddle :%s\n", filter);
						fiddle_command = 1;
						agrclist grclist = { filter ,fiddle_command }, *pmagrclist;
						pmagrclist = &grclist;
						//_beginthread(netdump, 0, pmagrclist);
						fiddle_handle = (HANDLE)_beginthreadex(NULL, 0, &fiddle, pmagrclist, 0, &fiddle_threadid);
						printf("fiddle is starting!\n");
						putchar('\n');
					}
					//start capture
					char filename[] = "tmp.pcap";
					STREAM_LIST * sl = read_packet(filename);
					show_stream_list(sl);
					putchar('\n');
					//continue;
				}
				else if (strcmp("back", operation) == 0) {
					putchar('\n');
					break;
				}
				else if (strcmp("update", operation) == 0) {
					//start capture
					char filename[9] = "tmp.pcap";
					STREAM_LIST * sl = read_packet(filename);
					show_stream_list(sl);
					putchar('\n');
					//continue;
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
					printf("������Ч������ѡ��\n");
					putchar('\n');
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					PURPLE();
					printf("����Ҫ���еĲ���: ���ļ� -open���������²���: -refiddle , ��������-update ,������һ�㣺 -back\n");
					WHITE();
					continue;
				}
				PURPLE();
				printf("����Ҫ���еĲ���: ���ļ� -open���������²���: -refiddle , ��������-update ,������һ�㣺 -back\n");
				WHITE();
			}
		}
		else {             //��Ч�����������
			PURPLE();
			printf("������Ч����������\n");
			putchar('\n');
			WHITE();
		}
		print();
	}

	return 0;
}

int find_file() {      //�����ҵ����ļ��ĸ���
	int i = 0;
	struct _finddata_t fileinfo;
	intptr_t  fHandle;
	if ((fHandle = _findfirst("*.pcap", &fileinfo)) == -1L)
	{
		printf("��ǰĿ¼��û��pcap�ļ�\n");
		return 0;
	}
	else {
		do {
			i++;
			printf("�ҵ��ļ�:%s,�ļ���С��%d\n", fileinfo.name, fileinfo.size);
		} while (_findnext(fHandle, &fileinfo) == 0);
	}
	_findclose(fHandle);
	return i;
}



