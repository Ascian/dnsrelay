#include"Domain.h"

void copyDomain(Domain* pDomain1, const Domain* pDomain2) {
	deleteDomain(pDomain1);
	pDomain1->isStatic = pDomain2->isStatic;
	pDomain1->isAvailable = pDomain2->isAvailable;
	copyStr(&pDomain1->name, &pDomain2->name);

	//复制A类型记录
	pDomain1->numA = pDomain2->numA;
	if (pDomain1->numA != 0 && pDomain1->numA != -1) {
		pDomain1->pRdataA = (Str*)malloc(sizeof(Str) * pDomain1->numA);
		if (pDomain1->pRdataA == NULL) {
			printf("Request memory failed\n");
			exit(-1);
		}
	}
	for (int i = 0; i < pDomain1->numA; i++) {
		initStr(&pDomain1->pRdataA[i]);
		copyStr(&pDomain1->pRdataA[i], &pDomain2->pRdataA[i]);
	}

	//复制AAAA类型记录
	pDomain1->num4A = pDomain2->num4A;
	if (pDomain1->num4A != 0 && pDomain1->num4A != -1) {
		pDomain1->pRdata4A = (Str*)malloc(sizeof(Str) * pDomain1->num4A);
		if (pDomain1->pRdata4A == NULL) {
			printf("Request memory failed\n");
			exit(-1);
		}
	}
	for (int i = 0; i < pDomain1->num4A; i++) {
		initStr(&pDomain1->pRdata4A[i]);
		copyStr(&pDomain1->pRdata4A[i], &pDomain2->pRdata4A[i]);
	}
}

void deleteDomain(Domain* pDomain) {
	deleteStr(&(pDomain->name));
	for (int i = 0; i < pDomain->numA; i++)
		deleteStr(&pDomain->pRdataA[i]);
	free(pDomain->pRdataA);
	pDomain->numA = -1;
	pDomain->pRdataA = NULL;
	for (int i = 0; i < pDomain->num4A; i++)
		deleteStr(&pDomain->pRdata4A[i]);
	free(pDomain->pRdata4A);
	pDomain->num4A = -1;
	pDomain->pRdata4A = NULL;
}