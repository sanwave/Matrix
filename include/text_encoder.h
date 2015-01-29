
/*
*
*
*
*	TextEncoder Class Header File		In Matrix
*
*	Created by Bonbon	2014.10.27
*
*	Updated by Bonbon	2014.10.31
*
*/


#ifndef _TEXT_ENCODER_H_
#define _TEXT_ENCODER_H_

#include <iostream>
#include <string>

//for gcc
#include <cstring>

#ifdef WIN32
#define WSTRCOPYN lstrcpynW
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif __linux__
#define WSTRCOPYN wcsncpy
#include <iconv.h>
#endif

namespace Matrix
{
	enum TextEncode
	{
		ANSI = 0,
		UTF_8,
		UTF_8_NO_MARK,
		UTF_16,
		UTF_16_BIG_ENDIAN,
		UNKNOWN,
		DEFAULT_ENCODE = UTF_8_NO_MARK
	};

	class TextEncoder
	{
	public:

		TextEncoder(const char *buffer);

		TextEncoder(const wchar_t *buffer);

		TextEncoder(std::string &buffer);

		TextEncoder(std::wstring &buffer);

		TextEncoder(const TextEncoder & src);

		~TextEncoder();

		char* Ansi() const;

		char* Utf8() const;

		wchar_t* Unicode();

		bool CopyFlag() const;

		wchar_t * Buffer() const;

		/// <summary>
		/// ��ָ��ANSI��������ת��ΪUnicode����
		/// </summary>
		/// <param name="ansiText">ָ��ANSI�����ı�</param>
		/// <returns>ת�����Unicode�ı�</returns>
		static wchar_t* AnsiToUnicode(const char * atext, size_t size = 0);

		/// <summary>
		/// ��ָ��UTF8��������ת��ΪUnicode����
		/// </summary>
		/// <param name="u8Text">ָ��UTF8�����ı�</param>
		/// <returns>ת�����Unicode�ı�</returns>
		static wchar_t* Utf8ToUnicode(const char * u8text, size_t size = 0);

		/// <summary>
		/// ��ָ��Unicode��������ת��ΪANSI����
		/// </summary>
		/// <param name="uText">ָ��Unicode�����ı�</param>
		/// <returns>ת�����ANSI�ı�</returns>
		static char* UnicodeToAnsi(const wchar_t* utext, size_t size = 0);

		/// <summary>
		/// ��ָ��Unicode��������ת��ΪUTF8����
		/// </summary>
		/// <param name="uText">ָ��Unicode�����ı�</param>
		/// <returns>ת�����UTF8�ı�</returns>
		static char* UnicodeToUtf8(const wchar_t* utext, size_t size = 0);

#ifdef __linux__
		static int ConvertCode(const char * from, const char * to, 
			const char *inbuf, size_t inlen, char *outbuf, size_t outlen);
#endif

		/// <summary>
		/// ��ȡָ���ı������ʽ���б�ʧЧʱ����UTF8
		/// </summary>
		/// <param name="text">ָ���ı�����</param>
		/// <returns>��Ӧ����ĺ�</returns>
		static TextEncode DetectEncode(std::string text);

		/// <summary>
		/// ʶ����Bom UTF8��ANSI�����ı����б�ʧЧʱ����UTF8
		/// </summary>
		/// <param name="text">ָ���ı�����</param>
		/// <returns>��Ӧ����ĺ�</returns>
		static TextEncode DetectAnsiOrUtf8(std::string text);

		/// <summary>
		/// ��ȡָ���ı������ʽ���б�ʧЧʱ����UTF8
		/// </summary>
		/// <param name="buffer">ָ���ı�����</param>
		/// <returns>��Ӧ����ĺ�</returns>
		static TextEncode DetectEncode(const char* buffer, size_t size = 0);

		/// <summary>
		/// ʶ����Bom UTF8��ANSI�����ı����б�ʧЧʱ����UTF8
		/// </summary>
		/// <param name="str">ָ���ı�����</param>
		/// <returns>��Ӧ����ĺ�</returns>
		static TextEncode DetectAnsiOrUtf8(const char* str, size_t size = 0);

	private:
		wchar_t *m_buffer;
		bool m_copy_flag;
	};
}

#endif