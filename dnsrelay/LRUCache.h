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
	struct LRUCacheNode* root;//��������ڵ㣬�洢��̬��;�̬���ṩ���ٲ�ѯ
	struct LRUCacheNode head;//˫�������ͷ,�洢��̬���ṩLRU����
	struct LRUCacheNode tail;//˫�������β
	int count;
	int capacity;
}LRUCache;

//��ʼ��cache
inline void initCache(LRUCache* pCache, const int capacity) {
	pCache->root = NULL;
	pCache->head.next = &pCache->tail;
	pCache->head.pre = NULL;
	pCache->tail.next = NULL;
	pCache->tail.pre = &pCache->head;
	pCache->count = 0;
	pCache->capacity = capacity;
}

//����LRUCache�����ҳɹ���������ָ�룬���򷵻�NULL
Domain* findCache(LRUCache* pCache, const Str* pKey);

//����LRUCache������ɹ�1,���򷵻�0
int addCache(LRUCache* pCache, const Str* pKey, const Domain* pDomain);

//�ͷ�LRUCache
void clearCache(LRUCache* pCache);

//�ͷŶ�̬�ڵ�
void clearDynamicNode(LRUCache* pCache);