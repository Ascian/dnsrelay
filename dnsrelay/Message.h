#pragma once
#pragma once
#include"Domain.h"
#include"Query.h"
#include"Str.h"
#include"TypeConversion.h"
#include<stdlib.h>


//�жϴ��׽����յ��ı����Ƿ�Ϊquery
inline int isQuery(const Str* message) {
	if (message->string[3] >> 7)
		return 0;
	return 1;
}

//�޸�ID�ֶ�
inline void setId(Str* pQuery, const short id) {
	shortToByte(pQuery->string, id);
}

//�޸�QR�ֶ�
inline void setQr(Str* pQuery, const char qr) {
	pQuery->string[2] |= qr << 7;
}

//�޸�RCODE�ֶ�
inline void setRcode(Str* pQuery, const char rcode) {
	pQuery->string[3] |= rcode & 0x0F;
}

//�޸�TC�ֶ�
inline void setTc(Str* pQuery, const char rcode) {
	pQuery->string[2] |= (rcode << 1) & 0x03;
}

//�޸�ANCOUNT�ֶ�
inline void setAncount(Str* pQuery, const short ancount) {
	shortToByte(pQuery->string + 6, ancount);
}

//��ȡID�ֶ�
inline short getId(const Str* pMessage) {
	return byteToShort(pMessage->string);
}

//��ȡQR�ֶ�
inline int getQr(const Str* pMessage) {
	return (pMessage->string[2] & 0x80) >> 7;
}

//��ȡOPCODE�ֶ�
inline int getOpcode(const Str* pMessage) {
	return (pMessage->string[2] & 0x78) >> 3;
}

//��ȡAA�ֶ�
inline int getAa(const Str* pMessage) {
	return (pMessage->string[2] & 0x04) >> 2;
}

//��ȡTC�ֶ�
inline int getTc(const Str* pMessage) {
	return (pMessage->string[2] & 0x02) >> 1;
}

//��ȡRD�ֶ�
inline int getRd(const Str* pMessage) {
	return pMessage->string[2] & 0x01;
}

//��ȡRA�ֶ�
inline int getRa(const Str* pMessage) {
	return (pMessage->string[3] & 0x80) >> 7;
}

//��ȡRDCODE�ֶ�
inline int getRcode(const Str* pMessage) {
	return pMessage->string[3] & 0x0f;
}

//��ȡQNAME�ֶ�,����ʽ���󷵻�0�����򷵻ز�ѯ����
inline short getQnameAndType(Str* pName, const Str* pMessage) {
	int nameLength = getName(pName, pMessage, 12);
	return byteToShort(pMessage->string + 12 + nameLength);
}

//��ȡQDCOUNT�ֶ�
inline short getQdcount(const Str* pMessage) {
	return byteToShort(pMessage->string + 4);
}

//��ȡANCOUNT�ֶ�
inline short getAncount(const Str* pMessage) {
	return byteToShort(pMessage->string + 6);
}

//��ȡNSCOUNT�ֶ�
inline short getNscount(const Str* pMessage) {
	return byteToShort(pMessage->string + 8);
}

//��ȡARCOUNT�ֶ�
inline short getArcount(const Str* pMessage) {
	return byteToShort(pMessage->string + 10);
}

//��������Ϊtype�ļ�¼
void mergeAnswer(Str* pMessage, const Domain* pDomain, const short type);

//����RDATA��¼,����¼����ΪA��AAAA���ͼ�������������1�����򷵻�0
int saveRdata(Domain* pDomain, const Str* pMessage);