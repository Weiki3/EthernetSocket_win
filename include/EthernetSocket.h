#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <pcap.h>

#define uint8_t unsigned char
#define uint16_t unsigned short int
#define ETH_ALEN 6

// EtherSock ���
struct EtherSockWin
{
	int protocol; // ����Э��
	pcap_t* fp; // �������
	uint8_t localMacAddr[6]; // ����mac��ַ
	struct bpf_program* fcode; // ���ù��˹���
};

struct ether_header
{
	uint8_t ether_dhost[ETH_ALEN];      // destination eth addr 
	uint8_t ether_shost[ETH_ALEN];      // source ether addr    
	uint16_t ether_type;                 // packet type ID field 
};

typedef struct EtherSockWin EtherSock;

// ����EthernetSocket
// ����Ҫת�� protocol ���ֽ���
// ��Ҫ�����ṩ������ mac ��ַ
EtherSockWin* createEthernetSocket(const char* networkCardName, int protocol, const uint8_t* localMacAddress);

// �ͷ�EthernetSocket
void freeEthernetSocket(EtherSockWin* etherSock);

// ������·�㷢�ͺ����ӿ�
// �ɹ����䷵��0,ʧ�ܷ���1
// ���ĳ��Ȳ�����1500�Ҳ�С��0
int sendOverEthernet(const EtherSockWin* etherSock, const uint8_t* destMacAddress, const uint8_t* packetData, int packetDataLen);

// ������·����ܺ����ӿ�
// �ɹ�����ʵ�ʽ��յ��� packet ����, ʧ�ܷ��� -1
int recvOverEthernet(const EtherSockWin* etherSock, uint8_t* packetBuffer, int packetLen);

// ��ʼ�����ڽ��յ�EtherSock
// ���ù��˹���, �ɹ����� 0��ʧ�ܷ��� 1 
int initRecvEthernetSocket(EtherSockWin* etherSock);

// ����dllλ��
int LoadNpcapDlls();

// ������յ���֡
void frame_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);

// �鿴unsigned char����
void ShowData(unsigned char* d1, int len);

// ��unsigned int����ת��Ϊhex�ַ���
void itox(unsigned int i, char* s);