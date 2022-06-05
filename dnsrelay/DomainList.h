#pragma once
#include"Domain.h"
#include"LRUCache.h"
#include<stdio.h>
#include<stdlib.h>
#include"Str.h"

typedef struct DomainList {
	LRUCache cache;
}DomainList;

//初始化域名列表
inline void initDomainList(DomainList* pDomainList, const int capacity) {
	initCache(&pDomainList->cache, capacity);
}

//添加域名,加入成功返回1，否则返回0
inline int addDomain(DomainList* pDomainList, const Domain* pDomain) {
	return addCache(&pDomainList->cache, &pDomain->name, pDomain);
}

//释放域名表
inline void deleteDomainList(DomainList* pDomainList) {
	clearCache(&pDomainList->cache);
}

//刷新域名表中动态记录
inline void refreshDomianList(DomainList* pDomainList) {
	clearDynamicNode(&pDomainList->cache);
}

//在domainList中找到关键字为key的域名，若找到返回节点域指针，否则返回NULL
inline Domain* findDomain(DomainList* pDomainList, const Str* pKey) {
	return findCache(&pDomainList->cache, pKey);
}

//从文件中读取域名数据，根据debugLevel选择输出内容
void loadDomainList(DomainList* pDomainList, const char* fileAddress, int debugLevel);