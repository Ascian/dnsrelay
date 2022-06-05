#pragma once
#include<string.h>
#include<stdlib.h>
typedef struct Str {
	char* string;
	unsigned short length;
}Str;

//��ʼ���ַ���
inline void initStr(Str* str) {
	str->length = 0;
	str->string = NULL;
}

//�����ַ���
void setStr(Str* dst, const char* src, const unsigned short length);

//�����ַ�������
inline int strLength(const Str* str) {
	return str->length;
}

//��ȡ�Ӵ�
void getSubstring(Str* dst, const Str* src, const unsigned short add, const unsigned short length);

//�����ַ���
void copyStr(Str* dst, const Str *src);

//����ָ�������ַ���
void copynStr(Str* dst, const Str* src, const unsigned short length);

//�Ƚ��ַ�����str1�ϴ󷵻�1��str1��С����-1����ȷ���0
int compareStr(const Str* str1, const Str* str2);

//�����ַ���
void concatStr(Str* dst, const Str* src);

//���ַ���β������ַ�
void appendStr(Str* dst, const char ch);

//����ָ�������ַ���
void concatnStr(Str* dst, const Str* src, const unsigned short length);

//ɾ���ַ���
inline void deleteStr(Str* dst) {
	free(dst->string);
	dst->string = NULL;
	dst->length = 0;
}

