#pragma once
#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <windows.h>  
#include <assert.h>  

char* Unicode2Utf8(const char* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, (const wchar_t*)unicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, (const wchar_t*)unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}
char* Utf82Unicode(const char* utf8) {
	// 预算-缓冲区中宽字节的长度    
	int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, nullptr, 0);
	// 给指向缓冲区的指针变量分配内存    
	size_t num = unicodeLen * sizeof(wchar_t);
	wchar_t *pUnicode = (wchar_t*)malloc(num);
	memset(pUnicode, 0, num);
	// 开始向缓冲区转换字节    
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, pUnicode, unicodeLen);
	return (char*)pUnicode;
}


char* Ansi2Unicode(const char* str)
{
	int dwUnicodeLen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	if (!dwUnicodeLen)
	{
		return strdup(str);
	}
	size_t num = dwUnicodeLen * sizeof(wchar_t);
	wchar_t *pwText = (wchar_t*)malloc(num);
	memset(pwText, 0, num);
	MultiByteToWideChar(CP_ACP, 0, str, -1, pwText, dwUnicodeLen);
	return (char*)pwText;
}

char* Unicode2Ansi(const char* str) {
	// 预算-缓冲区中多字节的长度    
	int ansiiLen = WideCharToMultiByte(CP_ACP, 0, (const wchar_t*)str, -1, nullptr, 0, nullptr, nullptr);
	// 给指向缓冲区的指针变量分配内存    
	char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
	memset(pAssii, 0, sizeof(char)*ansiiLen);
	// 开始向缓冲区转换字节    
	WideCharToMultiByte(CP_ACP, 0, (const wchar_t*)str, -1, pAssii, ansiiLen, nullptr, nullptr);
	return pAssii;
}

char* Ansi2Utf8(const char* str)
{
	char* unicode = Ansi2Unicode(str);
	char* utf8 = Unicode2Utf8(unicode);
	free(unicode);
	return utf8;
}
char* Utf82Ansi(const char* str)
{
	char* unicode = Utf82Unicode(str);
	char* ansi = Unicode2Ansi(unicode);
	free(unicode);
	return ansi;
}

int main(int argc, char *argv[])
{
	printf("Hello, world\n");
	//1.构造一个ansi文件,内容是"中文abc",看hex编码.  
	//ansi: D6 D0 CE C4 61 62 63  
	//utf8: E4 B8 AD E6 96 87 61 62  63  
	//char ansi[] = { 0xD6,0xD0,0xCE,0xC4,0x61,0x62,0x63,0 };
	//char utf8[] = { 0xE4,0xB8,0xAD,0xE6,0x96,0x87,0x61,0x62,0x63,0 };
	//char* str = Ansi2Utf8(ansi);
	//assert(!strcmp(str, utf8));
	//free(str);
	return 0;
}