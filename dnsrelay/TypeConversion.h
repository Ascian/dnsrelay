#pragma once

//���ô�˷�ʽ����chǰ���ֽ�ת��Ϊshort����
inline unsigned short byteToShort(const char* ch) {
	return (unsigned short)((unsigned short)ch[1] + ((unsigned short)ch[0] << 8));
}

//���ô�˷�ʽ����short����ת��Ϊchǰ���ֽ�
inline void shortToByte(char* ch, const short sh) {
	ch[0] = (char)(sh >> 8);
	ch[1] = (char)sh;
}

//���ô�˷�ʽ����int����ת��Ϊchǰ���ֽ�
inline void intToByte(char* ch, const short sh) {
	ch[0] = (char)(sh >> 24);
	ch[1] = (char)(sh >> 16);
	ch[2] = (char)(sh >> 8);
	ch[3] = (char)sh;
}
