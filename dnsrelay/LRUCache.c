#include "LRUCache.h"
int taller = 0;
int shorter = 0;

CacheNode* searchRBTree(const RBTree T, const Str* pKey) {
	//�ں������Ѱ�ҹؼ���Ϊkey�Ľڵ㣬���ҵ����ؽڵ�����ָ�룬���򷵻�NULL
	if (!T)//δ�ҵ��ؼ���Ϊkey�Ľڵ�
		return NULL;
	if (!compareStr(pKey, &T->key))//�ҵ��ؼ���Ϊkey�Ľڵ�
		return T;
	if (compareStr(pKey, &T->key) < 0)//���������м���Ѱ��
		return searchRBTree(T->lchild, pKey);
	return searchRBTree(T->rchild, pKey);//���������м���Ѱ��
}

void clearRBTree(RBTree T) {
	//�ͷ����������
	clearRBTree(T->lchild);
	clearRBTree(T->rchild);
	deleteDomain(&T->data);
	deleteStr(&T->key);
	free(T);
}

void r_Rotate(RBTree* pT) {
	//��pTָ��ĺ��������������
	RBTree lc = (*pT)->lchild;
	(*pT)->lchild = lc->rchild;
	lc->rchild = (*pT);
	(*pT) = lc;
}//r_Rotate

void l_Rotate(RBTree* pT) {
	//��pTָ��ĺ��������������
	RBTree rc = (*pT)->rchild;
	(*pT)->rchild = rc->lchild;
	rc->lchild = (*pT);
	(*pT) = rc;
}//l_Rotate

CacheNode* insertRBTree(RBTree* pT, const Str* pKey, const Domain* pData) {
	//���ں����pT�в����ں�key��ͬ�ؼ��ֵĽ�㣬�����һ������Ԫ��
	//Ϊdata���½ڵ�,��������ʹ�����ʧȥƽ�⣬����ƽ����ת����
	CacheNode* result;
	if (!(*pT)) {
		(*pT) = (RBTree)malloc(sizeof(CacheNode));
		if ((*pT) == NULL) {
			printf("Request memory failed\n");
			exit(-1);
		}
		initDomain(&(*pT)->data);
		initStr(&(*pT)->key);
		copyDomain(&(*pT)->data, pData);
		copyStr(&(*pT)->key, pKey);
		(*pT)->lchild = NULL;
		(*pT)->rchild = NULL;
		(*pT)->next = NULL;
		(*pT)->pre = NULL;
		(*pT)->color = RED;
		taller = 1;
		return *pT;
	}
	else {
		if (!compareStr(pKey,& (*pT)->key)) {
			//�����Ѵ��ں�key��ͬ�ؼ��ֵĽڵ�
			taller = 0;
			return NULL;
		}
		else if (compareStr(pKey, &(*pT)->key) < 0) {
			//Ӧ���������м���Ѱ��
			result = insertRBTree(&((*pT)->lchild), pKey, pData);
			if (!result) return NULL;
			if (taller)
				if ((*pT)->color == BLACK) {
					if ((*pT)->lchild->color == RED && (*pT)->lchild->lchild != NULL && (*pT)->lchild->lchild->color == RED) {
						//���Ӻ����ӵ����Ӷ�Ϊ��ɫ
						if ((*pT)->rchild == NULL || (*pT)->rchild->color == BLACK) {
							//�Һ���Ϊ�ڣ������������ı�taller״̬
							(*pT)->lchild->color = BLACK;
							(*pT)->color = RED;
							r_Rotate(pT);
							taller = 0;
						}//if
						else {
							//�Һ���Ϊ��ɫ��������ɫ�ı䣬���ı�taller״̬
							(*pT)->lchild->color = BLACK;
							(*pT)->rchild->color = BLACK;
							(*pT)->color = RED;
						}
					}//if
					else if ((*pT)->lchild->color == RED && (*pT)->lchild->rchild != NULL && (*pT)->lchild->rchild->color == RED) {
						//���Ӻ����ӵ��Һ��Ӷ�Ϊ��ɫ
						if ((*pT)->rchild == NULL || (*pT)->rchild->color == BLACK) {
							//�Һ���Ϊ��ɫ����˫������
							l_Rotate(&(*pT)->lchild);
							(*pT)->lchild->color = BLACK;
							(*pT)->color = RED;
							r_Rotate(pT);
							taller = 0;
						}
						else {
							//�Һ���Ϊ��ɫ��������ɫ�ı䣬���ı�taller״̬
							(*pT)->lchild->color = BLACK;
							(*pT)->rchild->color = BLACK;
							(*pT)->color = RED;
						}//if
					}//else if
				}//if
		}//else if
		else {
			//Ӧ���������м���Ѱ��
			result = insertRBTree(&((*pT)->rchild), pKey, pData);
			if (!result) return NULL;
			if (taller)
				if ((*pT)->color == BLACK) {
					if ((*pT)->rchild->color == RED && (*pT)->rchild->rchild != NULL && (*pT)->rchild->rchild->color == RED) {
						//�Һ��Ӻ��Һ��ӵ��Һ��Ӷ�Ϊ��ɫ
						if ((*pT)->lchild == NULL || (*pT)->lchild->color == BLACK) {
							//����Ϊ�ڣ������������ı�taller״̬
							(*pT)->rchild->color = BLACK;
							(*pT)->color = RED;
							l_Rotate(pT);
							taller = 0;
						}//if
						else {
							//����Ϊ��ɫ��������ɫ�ı䣬���ı�taller״̬
							(*pT)->lchild->color = BLACK;
							(*pT)->rchild->color = BLACK;
							(*pT)->color = RED;
						}//else
					}//if
					else if ((*pT)->rchild->color == RED && (*pT)->rchild->lchild != NULL && (*pT)->rchild->lchild->color == RED) {
						//�Һ��Ӻ��Һ��ӵ����Ӷ�Ϊ��ɫ
						if ((*pT)->lchild == NULL || (*pT)->lchild->color == BLACK) {
							//����Ϊ��ɫ����˫������
							r_Rotate(&(*pT)->rchild);
							(*pT)->rchild->color = BLACK;
							(*pT)->color = RED;
							l_Rotate(pT);
							taller = 0;
						}
						else {
							//����Ϊ��ɫ��������ɫ�ı䣬���ı�taller״̬
							(*pT)->lchild->color = BLACK;
							(*pT)->rchild->color = BLACK;
							(*pT)->color = RED;
						}//if
					}//else if
				}//if
		}//else
	}//else
	return result;
}

CacheNode* addRBTree(RBTree* pT, const Str* pKey, const Domain* pData) {
	CacheNode* result = insertRBTree(pT, pKey, pData);
	(*pT)->color = BLACK;//�޸ĸ������ɫΪ��
	return result;
}

CacheNode* deleteRBTree(RBTree* pT, RBTree parent, const Str* pKey) {
	// ������TΪ���ĺ�����в����ں�key����ͬ�ؼ��ֵĽڵ㣬����false;����ɾ����Ԫ�أ���true��
	// ����ɾ����ʹ�����ʧȥƽ�⣬����ƽ����ת����
	// prΪT˫��
	CacheNode* result;
	if (!(*pT))  return NULL;//�����ڸ�Ԫ��
	else if (!compareStr(pKey, &(*pT)->key)) {
		//�ҵ�Ԫ�ؽڵ�
		if (!(*pT)->lchild) {
			//������Ϊ�գ����������ӵ�˫����			
			if (!parent || (*pT)->color == RED || ((*pT)->rchild != NULL && (*pT)->rchild->color == RED)) {
				//*pTΪ���ڵ㣬����*pT�����Һ�������һ��Ϊ��ɫ������ƽ�����
				if ((*pT)->rchild != NULL)
					(*pT)->rchild->color = BLACK;
				shorter = 0;
			}
			else {
				//*pT��Ϊ���ڵ㣬��*pT�����Һ��Ӷ�Ϊ��ɫ����ƽ�����
				shorter = 1;
			}
			result = *pT;
			*pT = (*pT)->rchild;
		}
		else if (!(*pT)->rchild) {
			//������Ϊ�գ����������ӵ�˫����	
			if (!parent || (*pT)->color == RED || ((*pT)->lchild != NULL && (*pT)->lchild->color == RED)) {
				//*pTΪ���ڵ㣬����*pT������������һ��Ϊ��ɫ������ƽ�����
				shorter = 0;
				if ((*pT)->lchild != NULL)
					(*pT)->lchild->color = BLACK;
			}
			else {
				//*pT��Ϊ���ڵ㣬��*pT�������Ӷ�Ϊ��ɫ����ƽ�����
				shorter = 1;
			}
			result = *pT;
			*pT = (*pT)->lchild;
		}
		else {
			//�������������ڣ����������ĵľ�ͷ������ֵ����T
			RBTree temp = (*pT)->lchild;
			RBTree tempParent = *pT;
			//�滻�������йؼ������Ľڵ�
			while (temp->rchild != NULL) {
				tempParent = temp;
				temp = temp->rchild;
			}
			//��ɫ�����滻
			char color = (*pT)->color;
			(*pT)->color = temp->color;
			temp->color = color;
			if (tempParent != *pT) {
				CacheNode* tempLchild = temp->lchild;
				temp->lchild = (*pT)->lchild;
				temp->rchild = (*pT)->rchild;
				tempParent->rchild = *pT;
				*pT = temp;
				tempParent->rchild->lchild = tempLchild;
				tempParent->rchild->rchild = NULL;
				result = deleteRBTree(&((*pT)->lchild), *pT, &tempParent->rchild->key);//���������еݹ����ƽ��
			}
			else {
				CacheNode* tempLchild = temp->lchild;
				temp->rchild = (*pT)->rchild;
				temp->lchild = *pT;
				(*pT)->rchild = NULL;
				(*pT)->lchild = tempLchild;
				*pT = temp;
				result = deleteRBTree(&((*pT)->lchild), *pT, &tempParent->key);//���������еݹ����ƽ��
			}
			if (shorter) {
				//����Ϊ˫�ڽڵ�
				if ((*pT)->rchild->color == BLACK) {
					//�Һ���Ϊ��ɫ
					if ((*pT)->rchild->rchild != NULL && (*pT)->rchild->rchild->color == RED) {
						//�Һ��ӵ��Һ���Ϊ��ɫ
						(*pT)->rchild->rchild->color = BLACK;
						(*pT)->rchild->color = (*pT)->color;
						l_Rotate(pT);
						(*pT)->lchild->color = BLACK;
						shorter = 0;
					}//if
					else if ((*pT)->rchild->lchild != NULL && (*pT)->rchild->lchild->color == RED) {
						//�Һ��ӵ�����Ϊ��ɫ
						(*pT)->rchild->lchild->color = (*pT)->color;
						r_Rotate(&(*pT)->rchild);
						l_Rotate(pT);
						(*pT)->lchild->color = BLACK;
						shorter = 0;
					}//else if
					else {
						//�ֵܽڵ�����Һ��Ӷ�Ϊ��ɫ
						if ((*pT)->color == RED) {
							//*pTΪ��ɫ
							(*pT)->color = BLACK;
							(*pT)->rchild->color = RED;
							shorter = 0;
						}
						else {
							//*pTΪ��ɫ
							(*pT)->rchild->color = RED;
						}
					}//else
				}//if
				else {
					//�Һ���Ϊ��ɫ
					l_Rotate(pT);
					(*pT)->color = BLACK;
					(*pT)->lchild->color = RED;
					RBTree* pLc = &(*pT)->lchild;
					if ((*pLc)->rchild->rchild != NULL && (*pLc)->rchild->rchild->color == RED) {
						//pLc�Һ��ӵ��Һ���Ϊ��ɫ
						(*pLc)->rchild->rchild->color = BLACK;
						(*pLc)->rchild->color = (*pLc)->color;
						l_Rotate(pLc);
						(*pLc)->lchild->color = BLACK;
					}//if
					else if ((*pLc)->rchild->lchild != NULL && (*pLc)->rchild->lchild->color == RED) {
						//pLc�Һ��ӵ�����Ϊ��ɫ
						(*pLc)->rchild->lchild->color = (*pLc)->color;
						r_Rotate(&(*pLc)->rchild);
						l_Rotate(pLc);
						(*pLc)->lchild->color = BLACK;
					}//else if
					else {
						//pLc�Һ��ӵ����Һ��Ӷ�Ϊ��ɫ
						(*pLc)->color = BLACK;
						(*pLc)->rchild->color = RED;
					}//else
					shorter = 0;
				}//else
			}//if
		}//else
	}//else if
	else if (compareStr(pKey, &(*pT)->key) < 0) {
		//����������Ѱ��
		result = deleteRBTree(&((*pT)->lchild), *pT, pKey);
		if (!result)  return NULL;
		if (shorter) {
			//����Ϊ˫�ڽڵ�
			if ((*pT)->rchild->color == BLACK) {
				//�Һ���Ϊ��ɫ
				if ((*pT)->rchild->rchild != NULL && (*pT)->rchild->rchild->color == RED) {
					//�Һ��ӵ��Һ���Ϊ��ɫ
					(*pT)->rchild->rchild->color = BLACK;
					(*pT)->rchild->color = (*pT)->color;
					l_Rotate(pT);
					(*pT)->lchild->color = BLACK;
					shorter = 0;
				}//if
				else if ((*pT)->rchild->lchild != NULL && (*pT)->rchild->lchild->color == RED) {
					//�Һ��ӵ�����Ϊ��ɫ
					(*pT)->rchild->lchild->color = (*pT)->color;
					r_Rotate(&(*pT)->rchild);
					l_Rotate(pT);
					(*pT)->lchild->color = BLACK;
					shorter = 0;
				}//else if
				else {
					//�ֵܽڵ�����Һ��Ӷ�Ϊ��ɫ
					if ((*pT)->color == RED) {
						//*pTΪ��ɫ
						(*pT)->color = BLACK;
						(*pT)->rchild->color = RED;
						shorter = 0;
					}
					else {
						//*pTΪ��ɫ
						(*pT)->rchild->color = RED;
					}
				}//else
			}//if
			else {
				//�Һ���Ϊ��ɫ
				l_Rotate(pT);
				(*pT)->color = BLACK;
				(*pT)->lchild->color = RED;
				RBTree* pLc = &(*pT)->lchild;
				if ((*pLc)->rchild->rchild != NULL && (*pLc)->rchild->rchild->color == RED) {
					//pLc�Һ��ӵ��Һ���Ϊ��ɫ
					(*pLc)->rchild->rchild->color = BLACK;
					(*pLc)->rchild->color = (*pLc)->color;
					l_Rotate(pLc);
					(*pLc)->lchild->color = BLACK;
				}//if
				else if ((*pLc)->rchild->lchild != NULL && (*pLc)->rchild->lchild->color == RED) {
					//pLc�Һ��ӵ�����Ϊ��ɫ
					(*pLc)->rchild->lchild->color = (*pLc)->color;
					r_Rotate(&(*pLc)->rchild);
					l_Rotate(pLc);
					(*pLc)->lchild->color = BLACK;
				}//else if
				else {
					//pLc�Һ��ӵ����Һ��Ӷ�Ϊ��ɫ
					(*pLc)->color = BLACK;
					(*pLc)->rchild->color = RED;
				}//else
				shorter = 0;
			}//else
		}//if
	}//else if
	else {
		//��������Ѱ��
		result = deleteRBTree(&((*pT)->rchild), *pT, pKey);
		if (!result)  return NULL;
		if (shorter) {
			//�Һ���Ϊ˫�ڽڵ�
			if ((*pT)->lchild->color == BLACK) {
				//����Ϊ��ɫ
				if ((*pT)->lchild->lchild != NULL && (*pT)->lchild->lchild->color == RED) {
					//���ӵ�����Ϊ��ɫ
					(*pT)->lchild->lchild->color = BLACK;
					(*pT)->lchild->color = (*pT)->color;
					r_Rotate(pT);
					(*pT)->rchild->color = BLACK;
					shorter = 0;
				}//if
				else if ((*pT)->lchild->rchild != NULL && (*pT)->lchild->rchild->color == RED) {
					//���ӵ��Һ���Ϊ��ɫ
					(*pT)->lchild->rchild->color = (*pT)->color;
					l_Rotate(&(*pT)->lchild);
					r_Rotate(pT);
					(*pT)->rchild->color = BLACK;
					shorter = 0;
				}//else if
				else {
					//�ֵܽڵ�����Һ��Ӷ�Ϊ��ɫ
					if ((*pT)->color == RED) {
						//*pTΪ��ɫ
						(*pT)->color = BLACK;
						(*pT)->lchild->color = RED;
						shorter = 0;
					}
					else {
						//*pTΪ��ɫ
						(*pT)->lchild->color = RED;
					}
				}//else
			}//if
			else {
				//����Ϊ��ɫ
				r_Rotate(pT);
				(*pT)->color = BLACK;
				(*pT)->rchild->color = RED;
				RBTree* pRc = &(*pT)->rchild;
				if ((*pRc)->lchild->lchild != NULL && (*pRc)->lchild->lchild->color == RED) {
					//pRc���ӵ�����Ϊ��ɫ
					(*pRc)->lchild->lchild->color = BLACK;
					(*pRc)->lchild->color = (*pRc)->color;
					r_Rotate(pRc);
					(*pRc)->rchild->color = BLACK;
				}//if
				else if ((*pRc)->lchild->rchild != NULL && (*pRc)->lchild->rchild->color == RED) {
					//pRc���ӵ��Һ���Ϊ��ɫ
					(*pRc)->lchild->rchild->color = (*pRc)->color;
					l_Rotate(&(*pRc)->lchild);
					r_Rotate(pRc);
					(*pRc)->rchild->color = BLACK;
					shorter = 0;
				}//else if
				else {
					(*pRc)->color = BLACK;
					(*pRc)->lchild->color = RED;
				}//else
				shorter = 0;
			}//else
		}//if
	}//else
	return result;
}

void addNode(CacheNode* pHead, CacheNode* pNode) {
	//���ڵ��������
	pNode->pre = pHead;
	pNode->next = pHead->next;
	pHead->next->pre = pNode;
	pHead->next = pNode;
}

void removeNode(CacheNode* pNode) {
	//ɾ���ڵ�
	pNode->next->pre = pNode->pre;
	pNode->pre->next = pNode->next;
}

void moveToHead(CacheNode* pHead, CacheNode* pNode) {
	//���ڵ��ƶ�����ͷ
	removeNode(pNode);
	addNode(pHead, pNode);
}

CacheNode* popTail(CacheNode* pTail)
//����βɾ���������ر�βָ��
{
	CacheNode* result = pTail->pre;
	removeNode(result);
	return result;
}

Domain* findCache(LRUCache* pCache, const Str* pKey) {
	CacheNode* result = searchRBTree(pCache->root, pKey);
	if (result == NULL)
		return NULL;

	//���Ǿ�̬�����ݣ������·������ݲ�������ͷ��
	if (result->data.isStatic != 1)
		moveToHead(&pCache->head, result);
	return &result->data;
}

int addCache(LRUCache* pCache, const Str* pKey, const Domain* pData) {
	CacheNode* result = addRBTree(&pCache->root, pKey, pData);
	if (result == NULL)
		return 0;

	//���Ǿ�̬�����ݣ������²������ݲ�������ͷ��
	//�������С�����������ڱ�βɾ���������ʹ������
	if (result->data.isStatic != 1) {
		addNode(&pCache->head, result);
		pCache->count++;
		if (pCache->count > pCache->capacity) {
			CacheNode* tail = popTail(&pCache->tail);
			CacheNode* needToDelete = deleteRBTree(&pCache->root, NULL, &tail->key);
			deleteDomain(&needToDelete->data);
			deleteStr(&needToDelete->key);
			free(needToDelete);
			pCache->count--;
		}
	}
	return 1;
}

void clearCache(LRUCache* pCache) {
	clearRBTree(pCache->root);
}

void clearDynamicNode(LRUCache* pCache) {
	while (pCache->count != 0) {
		CacheNode* tail = popTail(&pCache->tail);
		CacheNode* needToDelete = deleteRBTree(&pCache->root, NULL, &tail->key);
		deleteDomain(&needToDelete->data);
		deleteStr(&needToDelete->key);
		free(needToDelete);
		pCache->count--;
	}
}