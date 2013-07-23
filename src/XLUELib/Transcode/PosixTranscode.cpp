#include "stdafx.h"
#include "./PosixTranscode.h"
#include <iconv.h>
#include <errno.h>

#pragma warning(disable: 4127)

#define CP_GBK      (936)       // 简体中文code page

#define CHECK_INPUT()  do { if ( NULL == in || 0 == len /*|| '\0' == in[0]字符串带0是允许的*/ ) { out.erase(); return; } } while(0)

void PosixTranscode::Unicode_to_UTF8(const wchar_t* in, size_t len, std::string& out)
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


	iconv_t env;
	env = iconv_open("UTF-8","WCHAR_T");
    //env = iconv_open("UTF-8","UTF-16");
    if ( env == (iconv_t)-1 )
    {
        if ( errno == EINVAL )
        {
            assert(0);
        }
    }
	size_t in_len = len * sizeof(wchar_t);
	size_t res = iconv(env, (char**)&in, (size_t*)&in_len, (char**)&pBuf, (size_t*)&out_len);
    if ( res == (size_t)-1 )
    {
        if ( errno == EILSEQ )
        {
            assert(0);
        }
        assert(0);
    }
    assert(res != (size_t)(-1));

	iconv_close(env);
	out = pResult;

	delete [] pResult;
}


void PosixTranscode::UTF8_to_Unicode(const char* in, size_t len, std::wstring& out)
{
	CHECK_INPUT();
	wchar_t* pBuf = new wchar_t[len + 1];
	if ( NULL == pBuf )
	{
		return;
	}

	memset(pBuf, 0, (len + 1) * sizeof(wchar_t));
	wchar_t* pResult = pBuf;

	size_t out_len = sizeof(wchar_t) * (len + 1);

	iconv_t env;
	env = iconv_open("WCHAR_T","UTF-8");
    if ( env == (iconv_t)-1 )
    {
        if ( errno == EINVAL )
        {
            assert(0);
        }
    }
	size_t res = iconv(env, (char**)&in, (size_t*)&len, (char**)&pBuf, &out_len);
    if ( res == (size_t)-1 )
    {
        if ( errno == EILSEQ )
        {
            assert(0);
        }
        assert(0);
    }
	iconv_close(env);
	out = pResult;

	delete [] pResult;
}

void PosixTranscode::ANSI_to_Unicode(const char* in, size_t len, std::wstring& out)
{
	CHECK_INPUT();

	iconv_t env;
	env = iconv_open("WCHAR_T","MS-ANSI");
	size_t out_len = (len + 1)*sizeof(wchar_t);
	wchar_t* pbuffer = new wchar_t[len + 1];
	memset(pbuffer, 0,out_len);
	wchar_t* pResult = pbuffer;
	size_t res = iconv(env, (char**)&in, (size_t*)&len, (char**)&pbuffer, (size_t*)&out_len);
    assert(res != (size_t)(-1));
	iconv_close(env);
	out = pResult;
	delete[] pResult;
}

void PosixTranscode::Unicode_to_ANSI(const wchar_t* in, size_t len, std::string& out)
{
	CHECK_INPUT();

	iconv_t env;
	env = iconv_open("MS-ANSI","WCHAR_T");
	size_t out_len = len*2 + 1;
	size_t in_len = len * sizeof(wchar_t);
	char* pbuffer = new char[out_len];
	memset(pbuffer, 0, out_len);
	char* pResult = pbuffer;
	size_t res = iconv(env, (char**)&in, (size_t*)&in_len, (char**)&pbuffer, (size_t*)&out_len);
    assert(res != (size_t)(-1));
	iconv_close(env);
	out = pResult;
	delete[] pResult;
}


void PosixTranscode::Unicode_to_GBK(const wchar_t* in, size_t len, std::string& out)
{
	CHECK_INPUT();

	iconv_t env;
	env = iconv_open("GBK","WCHAR_T");
	size_t out_len = len*2 + 1;
	size_t in_len = len * sizeof(wchar_t);
	char* pbuffer = new char[out_len];
	memset(pbuffer, 0, out_len);
	char* pResult = pbuffer;
	size_t res = iconv(env, (char**)&in, (size_t*)&in_len, (char**)&pbuffer, (size_t*)&out_len);
    assert(res != (size_t)(-1));
	iconv_close(env);
	out = pResult;
	delete[] pResult;
}

void PosixTranscode::GBK_to_Unicode(const char* in, size_t len, std::wstring& out)
{
	CHECK_INPUT();

	iconv_t env;
	env = iconv_open("WCHAR_T","GBK");
	size_t out_len = (len + 1)*sizeof(wchar_t);
	wchar_t* pbuffer = new wchar_t[len + 1];
	memset(pbuffer, 0,out_len);
	wchar_t* pResult = pbuffer;
	size_t res = iconv(env, (char**)&in, (size_t*)&len, (char**)&pbuffer, (size_t*)&out_len);
    assert(res != (size_t)(-1));
	iconv_close(env);
	out = pResult;
	delete[] pResult;
}