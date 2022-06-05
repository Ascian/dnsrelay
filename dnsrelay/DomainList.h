#pragma once
#include"Domain.h"
#include"LRUCache.h"
#include<stdio.h>
#include<stdlib.h>
#include"Str.h"

typedef struct DomainList {
	LRUCache cache;
}DomainList;

//��ʼ�������б�
inline void initDomainList(DomainList* pDomainList, const int capacity) {
	initCache(&pDomainList->cache, capacity);
}

//�������,����ɹ�����1�����򷵻�0
inline int addDomain(DomainList* pDomainList, const Domain* pDomain) {
	return addCache(&pDomainList->cache, &pDomain->name, pDomain);
}

//�ͷ�������
inline void deleteDomainList(DomainList* pDomainList) {
	clearCache(&pDomainList->cache);
}

//ˢ���������ж�̬��¼
inline void refreshDomianList(DomainList* pDomainList) {
	clearDynamicNode(&pDomainList->cache);
}

//��domainList���ҵ��ؼ���Ϊkey�����������ҵ����ؽڵ���ָ�룬���򷵻�NULL
inline Domain* findDomain(DomainList* pDomainList, const Str* pKey) {
	return findCache(&pDomainList->cache, pKey);
}

//���ļ��ж�ȡ�������ݣ�����debugLevelѡ���������
void loadDomainList(DomainList* pDomainList, const char* fileAddress, int debugLevel);