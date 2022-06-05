#pragma once
#include"Str.h"

typedef struct Domain {
	Str name;//域名
	char isStatic;//是否属于静态表
	char isAvailable;//是否允许查询
	char numA;//A类型记录数量,值为-1时表示还未查询过A类型记录,最多保存127个记录
	char num4A;//AAAA类型记录数量,值为-1时表示还未查询过AAAA类型记录,最多保存127个记录
	Str* pRdataA;//A类型记录,仅保存RDATA字段
	Str* pRdata4A;//AAAA类型记录，仅保存RDATA字段
}Domain;

//初始化域名
inline void initDomain(Domain* pDomain) {
	initStr(&pDomain->name);
	pDomain->isStatic = 0;
	pDomain->isAvailable = 1;
	pDomain->numA = -1;
	pDomain->num4A = -1;
	pDomain->pRdataA = NULL;
	pDomain->pRdata4A = NULL;
}

//修改域名
inline void setDomainName(Domain* pDomain, const Str* pName) {
	copyStr(&(pDomain->name), pName);
}

//复制域名
void copyDomain(Domain* pDomain1, const Domain* pDomain2);

//添加type类型记录
inline void addRecord(Domain* pDomain, const Str* pRdata, const int type) {
	if (type == 1) {
		//添加A类型记录
		if (pDomain->numA == 127)
			return;
		pDomain->pRdataA = (Str*)realloc(pDomain->pRdataA, sizeof(Str) * (pDomain->numA + 1));
		if (pDomain->pRdataA == NULL) {
			printf("Request memory failed\n");
			exit(-1);
		}
		initStr(&pDomain->pRdataA[pDomain->numA]);
		copyStr(&pDomain->pRdataA[pDomain->numA], pRdata);
		pDomain->numA++;
	}
	else if (type == 28) {
		//添加AA类型记录
		if (pDomain->num4A == 127)
			return;
		pDomain->pRdata4A = (Str*)realloc(pDomain->pRdata4A, sizeof(Str) * (pDomain->num4A + 1));
		if (pDomain->pRdata4A == NULL) {
			printf("Request memory failed\n");
			exit(-1);
		}
		initStr(&pDomain->pRdata4A[pDomain->num4A]);
		copyStr(&pDomain->pRdata4A[pDomain->num4A], pRdata);
		pDomain->num4A++;
	}
}

//删除域名
void deleteDomain(Domain* pDomain);
