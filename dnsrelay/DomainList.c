#include "DomainList.h"

void loadDomainList(DomainList* pDomainList, const char* fileAddress, int debugLevel) {
	printf("Try to load table \"%s\"", fileAddress);
	FILE* file = fopen(fileAddress, "r");
	if (file == NULL) {
		printf("...Ignored\n");
		return;
	}
	else {
		printf("...OK\n");
	}

	int count = 0;
	int id[4] = {0};
	char readBuf[100] = {0};
	Str domainName;
	Str rdata;
	Domain domain;
	initStr(&domainName);
	initStr(&rdata);
	initDomain(&domain);

	while (!feof(file)) {
		//��ȡID������	
		if (fscanf(file, "%d.%d.%d.%d %99s", &id[0], &id[1], &id[2], &id[3], readBuf) < 5) {
			//��ʽ����
			deleteStr(&rdata);
			deleteDomain(&domain);
			deleteStr(&domainName);
			printf("Format error.\n");
			printf("Successfully load %d records\n", count);
			return;
		}
		char temp = fgetc(file);
		if (id[0] > 255 || id[1] > 255 || id[2] > 255 || id[3] > 255 || (temp != '\n' && temp!= -1)) {
			//��ʽ����
			deleteStr(&rdata);
			deleteDomain(&domain);
			deleteStr(&domainName);
			printf("Format error.\n");
			printf("Successfully load %d records\n", count);
			return;
		}

		//���������Ϣ
		if (debugLevel == 2) {
			char temp[17] = {0};
			sprintf(temp, "%d.%d.%d.%d", id[0], id[1], id[2], id[3]);
			printf("%8d: %-16s%s\n", count, temp, readBuf);
		}

		//��Ӽ�¼��domainList
		setStr(&domainName, readBuf, strlen(readBuf));
		deleteDomain(&domain);//ɾ����һ����¼
		setDomainName(&domain, &domainName);
		domain.isStatic = 1;//����Ϊ��̬��¼
		if (id[0] == 0 && id[1] == 0 && id[2] == 0 && id[3] == 0) {
			//idΪ0.0.0.0
			domain.isAvailable = 0;//����Ϊ���ɷ���
			if (addDomain(pDomainList, &domain) == 0) {
				//������Ϣ�Ѵ���
				Domain* pDomain = findDomain(pDomainList, &domain.name);
				pDomain->isAvailable = 0;
			}
		}
		else {
			char temp[4];
			temp[0] = (char)id[0];
			temp[1] = (char)id[1];
			temp[2] = (char)id[2];
			temp[3] = (char)id[3];
			setStr(&rdata, temp, 4);
			domain.numA = 0;
			addRecord(&domain, &rdata, 1);
			if (addDomain(pDomainList, &domain) == 0) {
				//������Ϣ�Ѵ���
				Domain* pDomain = findDomain(pDomainList, &domain.name);
				if (pDomain->numA == -1)//��һ�����A���ͼ�¼
					domain.numA = 0;
				addRecord(pDomain, &rdata, 1);
			}
		}
		count++;
	}
	deleteStr(&rdata);
	deleteDomain(&domain);
	deleteStr(&domainName);
	printf("Successfully load %d records\n", count);
}