#pragma once

//采用大端方式，将ch前两字节转换为short类型
inline unsigned short byteToShort(const char* ch) {
	return (unsigned short)((unsigned short)ch[1] + ((unsigned short)ch[0] << 8));
}

//采用大端方式，将short类型转换为ch前两字节
inline void shortToByte(char* ch, const short sh) {
	ch[0] = (char)(sh >> 8);
	ch[1] = (char)sh;
}

//采用大端方式，将int类型转换为ch前两字节
inline void intToByte(char* ch, const short sh) {
	ch[0] = (char)(sh >> 24);
	ch[1] = (char)(sh >> 16);
	ch[2] = (char)(sh >> 8);
	ch[3] = (char)sh;
}
