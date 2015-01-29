
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
		/// 将指定ANSI编码内容转换为Unicode编码
		/// </summary>
		/// <param name="ansiText">指定ANSI编码文本</param>
		/// <returns>转换后的Unicode文本</returns>
		static wchar_t* AnsiToUnicode(const char * atext, size_t size = 0);

		/// <summary>
		/// 将指定UTF8编码内容转换为Unicode编码
		/// </summary>
		/// <param name="u8Text">指定UTF8编码文本</param>
		/// <returns>转换后的Unicode文本</returns>
		static wchar_t* Utf8ToUnicode(const char * u8text, size_t size = 0);

		/// <summary>
		/// 将指定Unicode编码内容转换为ANSI编码
		/// </summary>
		/// <param name="uText">指定Unicode编码文本</param>
		/// <returns>转换后的ANSI文本</returns>
		static char* UnicodeToAnsi(const wchar_t* utext, size_t size = 0);

		/// <summary>
		/// 将指定Unicode编码内容转换为UTF8编码
		/// </summary>
		/// <param name="uText">指定Unicode编码文本</param>
		/// <returns>转换后的UTF8文本</returns>
		static char* UnicodeToUtf8(const wchar_t* utext, size_t size = 0);

#ifdef __linux__
		static int ConvertCode(const char * from, const char * to, 
			const char *inbuf, size_t inlen, char *outbuf, size_t outlen);
#endif

		/// <summary>
		/// 获取指定文本编码格式，判别失效时优先UTF8
		/// </summary>
		/// <param name="text">指定文本内容</param>
		/// <returns>对应编码的宏</returns>
		static TextEncode DetectEncode(std::string text);

		/// <summary>
		/// 识别无Bom UTF8与ANSI编码文本，判别失效时优先UTF8
		/// </summary>
		/// <param name="text">指定文本内容</param>
		/// <returns>对应编码的宏</returns>
		static TextEncode DetectAnsiOrUtf8(std::string text);

		/// <summary>
		/// 获取指定文本编码格式，判别失效时优先UTF8
		/// </summary>
		/// <param name="buffer">指定文本内容</param>
		/// <returns>对应编码的宏</returns>
		static TextEncode DetectEncode(const char* buffer, size_t size = 0);

		/// <summary>
		/// 识别无Bom UTF8与ANSI编码文本，判别失效时优先UTF8
		/// </summary>
		/// <param name="str">指定文本内容</param>
		/// <returns>对应编码的宏</returns>
		static TextEncode DetectAnsiOrUtf8(const char* str, size_t size = 0);

	private:
		wchar_t *m_buffer;
		bool m_copy_flag;
	};
}

#endif