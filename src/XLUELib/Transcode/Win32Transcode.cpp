#include "stdafx.h"
#include "./Win32Transcode.h"
#include <Windows.h>
#include <mbstring.h>

#pragma warning(disable: 4127)

#define CP_GBK      (936)       // 简体中文code page

#define CHECK_INPUT()  do { if ( NULL == in || 0 == len /*|| '\0' == in[0]字符串带0是允许的*/ ) { out.erase(); return; } } while(0)

void Win32Transcode::Unicode_to_UTF8(const wchar_t* in, size_t len, std::string& out)
{
	CHECK_INPUT();    
	size_t out_len = len * 3 + 1;
	char* pBuf = new char[out_len];
	if ( NULL == pBuf )
	{
		return;
	}

	char* pResult = pBuf;
	memset(pBuf, 0, out_len);

	out_len = ::WideCharToMultiByte(CP_UTF8, 0, in, (int)len, pBuf, (int)len * 3, NULL, NULL);
	out.assign( pResult, out_len );

	delete [] pResult;
}


void Win32Transcode::UTF8_to_Unicode(const char* in, size_t len, std::wstring& out)
{
	CHECK_INPUT();
	wchar_t* pBuf = new wchar_t[len + 1];
	if ( NULL == pBuf )
	{
		return;
	}

	memset(pBuf, 0, (len + 1) * sizeof(wchar_t));
	wchar_t* pResult = pBuf;

	int out_len;

	out_len = ::MultiByteToWideChar(CP_UTF8, 0, in, (int)(intptr_t)len, pBuf, (int)len * sizeof(wchar_t));
	out.assign( pResult, out_len );

	delete [] pResult;
}

void Win32Transcode::ANSI_to_Unicode(const char* in, size_t len, std::wstring& out)
{
	CHECK_INPUT();

	//assert( _mbslen((const unsigned char*)in) == strlen(in) ); // ANSI 要求必须是纯英文
	int wbufferlen = (int)::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,in,(int)len,NULL,0);
	wchar_t* pwbuffer = new wchar_t[wbufferlen+4];
	if ( NULL == pwbuffer )
	{
		return;
	}
	wbufferlen = (int)::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,in,(int)len,pwbuffer,wbufferlen+2);
	pwbuffer[wbufferlen] = '\0';
	out.assign( pwbuffer, wbufferlen );
	delete[] pwbuffer;
}

void Win32Transcode::Unicode_to_ANSI(const wchar_t* in, size_t len, std::string& out)
{
	CHECK_INPUT();

	int bufferlen = (int)::WideCharToMultiByte(CP_ACP,0,in,(int)len,NULL,0,NULL,NULL);
	char* pBuffer = new char[bufferlen + 4];
	if ( NULL == pBuffer )
	{
		return;
	}
	int out_len = ::WideCharToMultiByte(CP_ACP,0,in,(int)len,pBuffer,bufferlen+2,NULL,NULL);   
	pBuffer[bufferlen] = '\0';
	out.assign( pBuffer, out_len );
	delete[] pBuffer;
	//assert( _mbslen((const unsigned char*)out.c_str()) == strlen(out.c_str()) );
}


void Win32Transcode::Unicode_to_GBK(const wchar_t* in, size_t len, std::string& out)
{
	CHECK_INPUT();

	int bufferlen = (int)::WideCharToMultiByte(CP_GBK,0,in,(int)len,NULL,0,NULL,NULL);
	char* pBuffer = new char[bufferlen + 4];
	if ( NULL == pBuffer )
	{
		return;
	}
	int out_len = ::WideCharToMultiByte(CP_GBK,0,in,(int)len,pBuffer,bufferlen+2,NULL,NULL);   
	pBuffer[bufferlen] = '\0';
	out.assign( pBuffer, out_len );
	delete[] pBuffer;
}

void Win32Transcode::GBK_to_Unicode(const char* in, size_t len, std::wstring& out)
{
	CHECK_INPUT();
	int wbufferlen = (int)::MultiByteToWideChar(CP_GBK,MB_PRECOMPOSED,in,(int)len,NULL,0);
	wchar_t* pwbuffer = new wchar_t[wbufferlen+4];
	if ( NULL == pwbuffer )
	{
		return;
	}
	wbufferlen = (int)::MultiByteToWideChar(CP_GBK,MB_PRECOMPOSED,in,(int)len,pwbuffer,wbufferlen+2);
	pwbuffer[wbufferlen] = '\0';
	out.assign( pwbuffer, wbufferlen );
	delete[] pwbuffer;
}