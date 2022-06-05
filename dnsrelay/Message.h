#pragma once
#pragma once
#include"Domain.h"
#include"Query.h"
#include"Str.h"
#include"TypeConversion.h"
#include<stdlib.h>


//判断从套接字收到的报文是否为query
inline int isQuery(const Str* message) {
	if (message->string[3] >> 7)
		return 0;
	return 1;
}

//修改ID字段
inline void setId(Str* pQuery, const short id) {
	shortToByte(pQuery->string, id);
}

//修改QR字段
inline void setQr(Str* pQuery, const char qr) {
	pQuery->string[2] |= qr << 7;
}

//修改RCODE字段
inline void setRcode(Str* pQuery, const char rcode) {
	pQuery->string[3] |= rcode & 0x0F;
}

//修改TC字段
inline void setTc(Str* pQuery, const char rcode) {
	pQuery->string[2] |= (rcode << 1) & 0x03;
}

//修改ANCOUNT字段
inline void setAncount(Str* pQuery, const short ancount) {
	shortToByte(pQuery->string + 6, ancount);
}

//读取ID字段
inline short getId(const Str* pMessage) {
	return byteToShort(pMessage->string);
}

//读取QR字段
inline int getQr(const Str* pMessage) {
	return (pMessage->string[2] & 0x80) >> 7;
}

//读取OPCODE字段
inline int getOpcode(const Str* pMessage) {
	return (pMessage->string[2] & 0x78) >> 3;
}

//读取AA字段
inline int getAa(const Str* pMessage) {
	return (pMessage->string[2] & 0x04) >> 2;
}

//读取TC字段
inline int getTc(const Str* pMessage) {
	return (pMessage->string[2] & 0x02) >> 1;
}

//读取RD字段
inline int getRd(const Str* pMessage) {
	return pMessage->string[2] & 0x01;
}

//读取RA字段
inline int getRa(const Str* pMessage) {
	return (pMessage->string[3] & 0x80) >> 7;
}

//读取RDCODE字段
inline int getRcode(const Str* pMessage) {
	return pMessage->string[3] & 0x0f;
}

//读取QNAME字段,若格式错误返回0，否则返回查询类型
inline short getQnameAndType(Str* pName, const Str* pMessage) {
	int nameLength = getName(pName, pMessage, 12);
	return byteToShort(pMessage->string + 12 + nameLength);
}

//读取QDCOUNT字段
inline short getQdcount(const Str* pMessage) {
	return byteToShort(pMessage->string + 4);
}

//读取ANCOUNT字段
inline short getAncount(const Str* pMessage) {
	return byteToShort(pMessage->string + 6);
}

//读取NSCOUNT字段
inline short getNscount(const Str* pMessage) {
	return byteToShort(pMessage->string + 8);
}

//读取ARCOUNT字段
inline short getArcount(const Str* pMessage) {
	return byteToShort(pMessage->string + 10);
}

//连接类型为type的记录
void mergeAnswer(Str* pMessage, const Domain* pDomain, const short type);

//保存RDATA记录,若记录类型为A或AAAA类型加入域名并返回1，否则返回0
int saveRdata(Domain* pDomain, const Str* pMessage);