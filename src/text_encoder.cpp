
/*
*
*
*
*	TextEncoder Class Header File		In Matrix
*
*	Created by Bonbon	2014.10.27
*
*	Updated by Bonbon	2015.01.10
*
*/


#include "text_encoder.h"

namespace Matrix
{

	TextEncoder::TextEncoder(const char *buffer) :m_copy_flag(false)
	{
		TextEncode encode = DetectEncode(buffer);
		if (NULL == buffer)
		{
			m_buffer = NULL;
		}
		else if (Matrix::ANSI == encode)
		{
			m_buffer = AnsiToUnicode(buffer);
		}
		else if (Matrix::UTF_8_NO_MARK == encode)
		{
			m_buffer = Utf8ToUnicode(buffer);
		}
		else if (Matrix::UTF_8 == encode)
		{
			m_buffer = Utf8ToUnicode(buffer + 3);
		}
		else
		{
			m_buffer = NULL;
		}
	}

	TextEncoder::TextEncoder(const wchar_t *buffer) :m_copy_flag(false)
	{
		if (NULL == buffer)
		{
			m_buffer = NULL;
		}
		else
		{
			size_t ulen = wcslen(buffer);
			m_buffer = new wchar_t[ulen + 1];
			WSTRCOPYN(m_buffer, buffer, ulen + 1);
		}
	}

	TextEncoder::TextEncoder(std::string &buffer) :m_copy_flag(false)
	{
		TextEncode encode = DetectEncode(buffer);
		if (buffer.length() == 0)
		{
			m_buffer = NULL;
		}
		else if (ANSI == encode)
		{
			m_buffer = AnsiToUnicode(buffer.c_str());
		}
		else if (UTF_8_NO_MARK == encode)
		{
			m_buffer = Utf8ToUnicode(buffer.c_str());
		}
		else if (UTF_8 == encode)
		{
			m_buffer = Utf8ToUnicode(buffer.substr(3).c_str());
		}
		else
		{
			m_buffer = NULL;
		}
	}

	TextEncoder::TextEncoder(std::wstring &buffer) :m_copy_flag(false)
	{
		if (buffer.length() == 0)
		{
			m_buffer = NULL;
		}
		else
		{
			size_t ulen = buffer.length();
			m_buffer = new wchar_t[ulen + 1];
			WSTRCOPYN(m_buffer, buffer.c_str(), ulen + 1);
		}
	}

	TextEncoder::TextEncoder(const TextEncoder & src) :m_copy_flag(false), m_buffer(NULL)
	{
		m_copy_flag = src.CopyFlag();
		wchar_t * buffer = src.Buffer();
		if (NULL != buffer)
		{
			int ulen = wcslen(buffer);
			m_buffer = new wchar_t[ulen + 1];
			WSTRCOPYN(m_buffer, buffer, ulen + 1);
		}
	}

	TextEncoder::~TextEncoder()
	{
		if (false == m_copy_flag && NULL != m_buffer)
		{
			delete m_buffer;
			m_buffer = NULL;
		}
	}

	char* TextEncoder::Ansi() const
	{
		if (NULL == m_buffer)
		{
			return NULL;
		}
		else
		{
			return UnicodeToAnsi(m_buffer);
		}
	}

	char* TextEncoder::Utf8() const
	{
		if (NULL == m_buffer)
		{
			return NULL;
		}
		else
		{
			return UnicodeToUtf8(m_buffer);
		}
	}

	wchar_t* TextEncoder::Unicode()
	{
		if (NULL == m_buffer)
		{
			return NULL;
		}
		else
		{
			m_copy_flag = true;
			return m_buffer;
		}
	}

	bool TextEncoder::CopyFlag() const
	{
		return m_copy_flag;
	}

	wchar_t * TextEncoder::Buffer() const
	{
		return m_buffer;
	}

	wchar_t* TextEncoder::AnsiToUnicode(const char * atext, size_t size)
	{
		if (NULL == atext)
		{
			return NULL;
		}
		else if (0 == size)
		{
			size = strlen(atext);
		}
#ifdef WIN32
		int ulen = ::MultiByteToWideChar(CP_ACP, NULL, atext, size, NULL, 0);
		wchar_t* utext = new wchar_t[ulen + 1];
		::MultiByteToWideChar(CP_ACP, NULL, atext, size, utext, ulen);
		utext[ulen] = '\0';
#elif __linux__
		size_t len = size * 2 + 2;
		wchar_t *utext = new wchar_t[len];
		ConvertCode("GB2312", "UNICODE", atext, size, (char *)utext, len);
#endif
		return utext;
	}

	wchar_t* TextEncoder::Utf8ToUnicode(const char * u8text, size_t size)
	{
		if (NULL == u8text)
		{
			return NULL;
		}
		else if (0 == size)
		{
			size = strlen(u8text);
		}
#ifdef WIN32
		int ulen = ::MultiByteToWideChar(CP_UTF8, NULL, u8text, size, NULL, 0);
		wchar_t* utext = new wchar_t[ulen + 1];
		::MultiByteToWideChar(CP_UTF8, NULL, u8text, size, utext, ulen);
		utext[ulen] = '\0';
#elif __linux__
		size_t len = size * 2 + 2;
		wchar_t *utext = new wchar_t[len];
		ConvertCode("UTF-8", "UNICODE", u8text, size, (char *)utext, len);
#endif
		return utext;
	}

	char* TextEncoder::UnicodeToAnsi(const wchar_t* utext, size_t size)
	{
		if (NULL == utext)
		{
			return NULL;
		}
		else if (0 == size)
		{
			size = wcslen(utext);
		}
#ifdef WIN32
		int len = ::WideCharToMultiByte(CP_ACP, NULL, utext, size, NULL, 0, NULL, NULL);
		char *atext = new char[len + 1];
		::WideCharToMultiByte(CP_ACP, NULL, utext, size, atext, len, NULL, NULL);
		atext[len] = '\0';
#elif __linux__
		size *= 4;
		size_t len = size + 1;
		char *atext = new char[len];
		ConvertCode("UNICODE", "GB2312", (char *)utext, size, atext, len);
#endif
		return atext;
	}

	char* TextEncoder::UnicodeToUtf8(const wchar_t* utext, size_t size)
	{
		if (NULL == utext)
		{
			return NULL;
		}
		else if (0 == size)
		{
			size = wcslen(utext);
		}
#ifdef WIN32
		int len = ::WideCharToMultiByte(CP_UTF8, NULL, utext, size, NULL, 0, NULL, NULL);
		char *u8text = new char[len + 1];
		::WideCharToMultiByte(CP_UTF8, NULL, utext, size, u8text, len, NULL, NULL);
		u8text[len] = '\0';
#elif __linux__
		size *= 4;
		size_t len = size * 2 + 1;
		char *u8text = new char[len];
		ConvertCode("UNICODE", "UTF-8", (char *)utext, size, u8text, len);
#endif
		return u8text;
	}

#ifdef __linux__
	int TextEncoder::ConvertCode(const char * from, const char * to,
		const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
	{
		char *pin = const_cast<char *> (inbuf);
		char *pout = outbuf;
		iconv_t cd = iconv_open(to, from);
		if (0 == cd)
		{
			return -2;
		}
		iconv(cd, NULL, NULL, NULL, NULL);
		memset(outbuf, 0, outlen);
		if ((size_t)-1 == iconv(cd, &pin, &inlen, &pout, &outlen))
		{
			return -1;
		}
		iconv_close(cd);
		return 0;
	}
#endif

	TextEncode TextEncoder::DetectEncode(std::string text)
	{
		if (text.length() <= 3)
		{
			return Matrix::UNKNOWN;
		}
		else if ((text[0] == 0xEF) && (text[1] == 0xBB) && (text[2] == 0xBF))
		{
			return Matrix::UTF_8;//UTF8 With Bom
		}
		else if ((text[0] == 0xFF) && (text[1] == 0xFE))
		{
			return Matrix::UTF_16;
		}
		else if ((text[0] == 0xFE) && (text[0] == 0xFF))
		{
			return Matrix::UTF_16_BIG_ENDIAN;
		}
		else
		{
			return DetectAnsiOrUtf8(text);
		}
	}

	TextEncode TextEncoder::DetectAnsiOrUtf8(std::string text)
	{
		int index = -1;
		int u8Count = 0;
		char i = -1;
		char ch;
		while (text[++index])
		{
			ch = text[index];
			if ((ch & 0x80) == 0)
			{
				continue;//Ansi×Ö·û
			}
			else if ((ch & 0xC0) == 0xC0)
			{
				if ((ch & 0xFC) == 0xFC)
				{
					u8Count = 5;
				}
				else if ((ch & 0xF8) == 0xF8)
				{
					u8Count = 4;
				}
				else if ((ch & 0xF0) == 0xF0)
				{
					u8Count = 3;
				}
				else if ((ch & 0xE0) == 0xE0)
				{
					u8Count = 2;
				}
				else if ((ch & 0xC0) == 0xC0)
				{
					u8Count = 1;
				}
				while (u8Count > ++i)
				{
					if ((text[index + 1 + i] & 0x80) != 0x80)
					{
						return Matrix::ANSI;
					}
				}
				index += u8Count;
				i = 0;
			}
			else
			{
				return Matrix::ANSI;
			}
		}
		//Ä¬ÈÏUTF8
		return Matrix::DEFAULT_ENCODE;
	}

	TextEncode TextEncoder::DetectEncode(const char* buffer, size_t size)
	{
		TextEncode encode = ANSI;

		if (NULL == buffer || strlen(buffer) <= 3)
		{
			return Matrix::UNKNOWN;
		}

		const unsigned char* bom = reinterpret_cast<const unsigned char*>(buffer);
		if (bom[0] == 0xfe && bom[1] == 0xff)
		{
			encode = Matrix::UTF_16_BIG_ENDIAN;
		}
		else if (bom[0] == 0xff && bom[1] == 0xfe)
		{
			encode = Matrix::UTF_16;
		}
		else if (bom[0] == 0xef && bom[1] == 0xbb && bom[2] == 0xbf)
		{
			encode = Matrix::UTF_8;
		}
		else
		{
			encode = DetectAnsiOrUtf8(buffer, size);
		}
		return encode;
	}

	TextEncode TextEncoder::DetectAnsiOrUtf8(const char* str, size_t size)
	{
		if (0 == size)
		{
			size = strlen(str);
		}

		while (size > 0)
		{
			if ((*str & 0x80) == 0)
			{
				//1 byte
				++str;
				--size;
			}
			else
			{
				if ((*str & 0xf0) == 0xe0)
				{
					//3 bytes
					if (size < 3)
					{
						return Matrix::ANSI;
					}
					if ((*(str + 1) & 0xc0) != 0x80 || (*(str + 2) & 0xc0) != 0x80)
					{
						return Matrix::ANSI;
					}
					str += 3;
					size -= 3;
				}
				else if ((*str & 0xe0) == 0xc0)
				{
					//2 bytes
					if (size < 2)
					{
						return Matrix::ANSI;
					}
					if ((*(str + 1) & 0xc0) != 0x80)
					{
						return Matrix::ANSI;
					}
					str += 2;
					size -= 2;
				}
				else if ((*str & 0xf8) == 0xf0)
				{
					//4 bytes
					if (size < 4)
					{
						return Matrix::ANSI;
					}
					if ((*(str + 1) & 0xc0) != 0x80 || (*(str + 2) & 0xc0) != 0x80
						|| (*(str + 3) & 0xc0) != 0x80)
					{
						return Matrix::ANSI;
					}
					str += 4;
					size -= 4;
				}
				else
				{
					return Matrix::ANSI;
				}
			}
		}
		return Matrix::UTF_8_NO_MARK;
	}
}