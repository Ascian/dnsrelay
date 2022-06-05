#pragma once
#include"Domain.h"
#include"Str.h"
#define RED 1
#define BLACK 0

typedef struct LRUCacheNode {
	Domain data;
	Str key;
	char color;
	struct LRUCacheNode* lchild;
	struct LRUCacheNode* rchild;
	struct LRUCacheNode* next;
	struct LRUCacheNode* pre;
}CacheNode, * RBTree;

typedef struct LRUCache {
	struct LRUCacheNode* root;//红黑树根节点，存储动态表和静态表，提供快速查询
	struct LRUCacheNode head;//双向链表表头,存储动态表，提供LRU机制
	struct LRUCacheNode tail;//双向链表表尾
	int count;
	int capacity;
}LRUCache;

//初始化cache
inline void initCache(LRUCache* pCache, const int capacity) {
	pCache->root = NULL;
	pCache->head.next = &pCache->tail;
	pCache->head.pre = NULL;
	pCache->tail.next = NULL;
	pCache->tail.pre = &pCache->head;
	pCache->count = 0;
	pCache->capacity = capacity;
}

//查找LRUCache，查找成功返回域名指针，否则返回NULL
Domain* findCache(LRUCache* pCache, const Str* pKey);

//插入LRUCache，插入成功1,否则返回0
int addCache(LRUCache* pCache, const Str* pKey, const Domain* pDomain);

//释放LRUCache
void clearCache(LRUCache* pCache);

//释放动态节点
void clearDynamicNode(LRUCache* pCache);