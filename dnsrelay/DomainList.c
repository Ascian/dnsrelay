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
		//读取ID和域名	
		if (fscanf(file, "%d.%d.%d.%d %99s", &id[0], &id[1], &id[2], &id[3], readBuf) < 5) {
			//格式错误
			deleteStr(&rdata);
			deleteDomain(&domain);
			deleteStr(&domainName);
			printf("Format error.\n");
			printf("Successfully load %d records\n", count);
			return;
		}
		char temp = fgetc(file);
		if (id[0] > 255 || id[1] > 255 || id[2] > 255 || id[3] > 255 || (temp != '\n' && temp!= -1)) {
			//格式错误
			deleteStr(&rdata);
			deleteDomain(&domain);
			deleteStr(&domainName);
			printf("Format error.\n");
			printf("Successfully load %d records\n", count);
			return;
		}

		//输出调试信息
		if (debugLevel == 2) {
			char temp[17] = {0};
			sprintf(temp, "%d.%d.%d.%d", id[0], id[1], id[2], id[3]);
			printf("%8d: %-16s%s\n", count, temp, readBuf);
		}

		//添加记录到domainList
		setStr(&domainName, readBuf, strlen(readBuf));
		deleteDomain(&domain);//删除上一条记录
		setDomainName(&domain, &domainName);
		domain.isStatic = 1;//设置为静态记录
		if (id[0] == 0 && id[1] == 0 && id[2] == 0 && id[3] == 0) {
			//id为0.0.0.0
			domain.isAvailable = 0;//设置为不可访问
			if (addDomain(pDomainList, &domain) == 0) {
				//域名信息已存在
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
				//域名信息已存在
				Domain* pDomain = findDomain(pDomainList, &domain.name);
				if (pDomain->numA == -1)//第一次添加A类型记录
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