#pragma once
#include"Str.h"

typedef struct Domain {
	Str name;//����
	char isStatic;//�Ƿ����ھ�̬��
	char isAvailable;//�Ƿ������ѯ
	char numA;//A���ͼ�¼����,ֵΪ-1ʱ��ʾ��δ��ѯ��A���ͼ�¼,��ౣ��127����¼
	char num4A;//AAAA���ͼ�¼����,ֵΪ-1ʱ��ʾ��δ��ѯ��AAAA���ͼ�¼,��ౣ��127����¼
	Str* pRdataA;//A���ͼ�¼,������RDATA�ֶ�
	Str* pRdata4A;//AAAA���ͼ�¼��������RDATA�ֶ�
}Domain;

//��ʼ������
inline void initDomain(Domain* pDomain) {
	initStr(&pDomain->name);
	pDomain->isStatic = 0;
	pDomain->isAvailable = 1;
	pDomain->numA = -1;
	pDomain->num4A = -1;
	pDomain->pRdataA = NULL;
	pDomain->pRdata4A = NULL;
}

//�޸�����
inline void setDomainName(Domain* pDomain, const Str* pName) {
	copyStr(&(pDomain->name), pName);
}

//��������
void copyDomain(Domain* pDomain1, const Domain* pDomain2);

//���type���ͼ�¼
inline void addRecord(Domain* pDomain, const Str* pRdata, const int type) {
	if (type == 1) {
		//���A���ͼ�¼
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
		//���AA���ͼ�¼
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

//ɾ������
void deleteDomain(Domain* pDomain);
