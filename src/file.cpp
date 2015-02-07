
/*
*
*
*
*	File Class Source File		In Matrix
*
*	Created by Bonbon	2014.09.25
*
*	Updated by Bonbon	2015.01.10
*
*/

#include "file.h"

#include <string>
#include <fstream>

//for gcc
#include <cstring>
#ifdef __linux__
#include <climits>
#endif

namespace Matrix
{
	File::File(const char *filename)
		:m_filename(NULL)
	{
		if (NULL != filename)
		{
			m_filename = Matrix::TextEncoder(filename).Unicode();
		}
	}

	File::File(const wchar_t *filename)
		:m_filename(NULL)
	{
		if (NULL != filename)
		{
			size_t ulen = wcslen(filename);
			m_filename = new wchar_t[ulen + 1];
			WSTRCOPYN(m_filename, filename, ulen + 1);
		}
	}

	File::File(const File& src)
		:m_filename(NULL)
	{
		const wchar_t * filename = src.FileName();
		if (NULL != filename)
		{
			size_t ulen = wcslen(filename);
			m_filename = new wchar_t[ulen + 1];
			WSTRCOPYN(m_filename, filename, ulen + 1);
		}
	}

	File::~File()
	{
		if (NULL != m_filename)
		{
			delete m_filename;
			m_filename = NULL;
		}
	}

	TextEncode File::Encode()
	{
		if (NULL == m_filename)
		{
			return Matrix::UNKNOWN;
		}
		const char * sample = ReadBlock(m_filename, 0, FBUFSIZ);
		TextEncode encode = Matrix::TextEncoder::DetectEncode(sample);
		if (NULL != sample)
		{
			delete sample;
			sample = NULL;
		}
		return encode;
	}

	const wchar_t* File::FileName() const
	{
		return m_filename;
	}

	const wchar_t * File::Text(int page, size_t *size)
	{
		const wchar_t * utext = ReadAsText(m_filename, page);
		if (NULL == utext)
		{
			return NULL;
		}
		else if (NULL != size)
		{
			*size = wcslen(utext);
		}
		return utext;
	}

	const char * File::AnsiText(int page, size_t *size)
	{
		const wchar_t * utext = ReadAsText(m_filename, page);
		if (NULL == utext)
		{
			return NULL;
		}
		else if (NULL != size)
		{
			*size = wcslen(utext);
		}
		const char * atext = Matrix::TextEncoder::UnicodeToAnsi(utext);
		if (NULL != utext)
		{
			delete utext;
			utext = NULL;
		}
		return atext;
	}

	const char * File::Utf8Text(int page, size_t *size)
	{
		const wchar_t * utext = ReadAsText(m_filename, page);
		if (NULL == utext)
		{
			return NULL;
		}
		else if (NULL != size)
		{
			*size = wcslen(utext);
		}
		const char * u8text = Matrix::TextEncoder::UnicodeToUtf8(utext);
		if (NULL != utext)
		{
			delete utext;
			utext = NULL;
		}
		return u8text;
	}

	const char * File::Binary(int page, size_t *size)
	{
		if (NULL != size)
		{
			*size = FBUFSIZ;
		}
		return ReadAsBinary(m_filename, page);
	}

	int File::OverWrite(const char * text, size_t size)
	{
		if (NULL == m_filename || NULL == text)
		{
			return -2;
		}
		if (0 >= size)
		{
			size = strlen(text);
		}
		return OverWrite(m_filename, text, size);
	}

	int File::WriteText(const char * text, size_t size, bool over_write)
	{
		if (NULL == m_filename || NULL == text)
		{
			return -2;
		}
		if (0 >= size)
		{
			size = strlen(text);
		}
		return Write(m_filename, text, 0, size, over_write);
	}

	int File::AppendText(const char * text, size_t size)
	{
		if (NULL == m_filename || NULL == text)
		{
			return -2;
		}
		if (0 >= size)
		{
			size = strlen(text);
		}
		return Append(m_filename, text, size);
	}

	int File::Exist()
	{
		std::fstream file;
		if (NULL == m_filename)
		{
			return -2;
		}
		char * afilename = Matrix::TextEncoder(m_filename).Ansi();
		file.open(afilename, std::ios_base::in);
		bool exist = file.is_open();
		file.close();
		return exist;
	}

	size_t File::GetSize()
	{
		std::fstream file;
		size_t size;
		if (NULL == m_filename)
		{
			return 0;
		}
		char * afilename = Matrix::TextEncoder(m_filename).Ansi();
		file.open(afilename, std::ios_base::in);
		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			size = static_cast<size_t>(file.tellg());
		}
		else
		{
			size = 0;
		}
		file.close();
		return size;
	}

	int File::Exist(const char * filename)
	{
		std::fstream file;
		if (NULL == filename)
		{
			return -2;
		}
		char * afilename = Matrix::TextEncoder(filename).Ansi();
		file.open(afilename, std::ios_base::in);
		bool exist = file.is_open();
		file.close();
		return exist;
	}

	size_t File::GetSize(const char * filename)
	{
		std::fstream file;
		size_t size = 0;
		if (NULL == filename)
		{
			return 0;
		}
		char * afilename = Matrix::TextEncoder(filename).Ansi();
		file.open(afilename, std::ios_base::in);
		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			size = static_cast<size_t>(file.tellg());
		}
		else
		{
			size = 0;
		}
		file.close();
		return size;
	}

	const wchar_t * File::ReadAsText(const char *filename, int page)
	{
		if (NULL == filename)
		{
			return NULL;
		}
		const char * ufilename = Matrix::TextEncoder(filename).Ansi();
		const wchar_t * utext = ReadAsText(ufilename, page);
		if (NULL != ufilename)
		{
			delete ufilename;
			ufilename = NULL;
		}
		return utext;
	}

	const wchar_t * File::ReadAsText(const wchar_t *filename, int page)
	{
		const char * text = ReadBlock(filename, FPAGESIZ * page, FPAGESIZ);
		if (NULL == text)
		{
			return NULL;
		}
		const wchar_t * utext = Matrix::TextEncoder(text).Unicode();
		if (NULL != text)
		{
			delete text;
			text = NULL;
		}
		return utext;
	}

	const char * File::ReadAsBinary(const char * filename, int page)
	{
		if (NULL == filename)
		{
			return NULL;
		}
		const wchar_t * ufilename = Matrix::TextEncoder(filename).Unicode();
		const char * buffer = ReadBlock(ufilename, FPAGESIZ * page, FPAGESIZ);
		if (NULL != ufilename)
		{
			delete ufilename;
			ufilename = NULL;
		}
		return buffer;
	}

	const char * File::ReadAsBinary(const wchar_t * filename, int page)
	{
		return ReadBlock(filename, FPAGESIZ * page, FPAGESIZ);
	}

	const char * File::ReadBlock(const wchar_t * filename, off_t off, size_t read_size)
	{
		std::fstream file;
		if (NULL == filename)
		{
			return NULL;
		}
		char * afilename = Matrix::TextEncoder(filename).Ansi();
		file.open(afilename, std::ios_base::in | std::ios_base::binary);
		if (!file.is_open())
		{
			return NULL;
		}

		file.seekg(0, std::ios::end);
		size_t size = static_cast<size_t>(file.tellg());

		if (off < std::ios::beg)
		{
			off = std::ios::beg;
			read_size = size;
		}
		else if (off > 0 && (size_t)off >= size)
		{
			file.close();
			return NULL;
		}
		else if (read_size <= 0 || off + read_size > size)
		{
			read_size = size - off;
		}

		file.seekg(off);
		char* buffer = new char[read_size + 1];
		file.read(buffer, read_size);
		buffer[read_size] = '\0';
		file.close();

		if (NULL != afilename)
		{
			delete afilename;
			afilename = NULL;
		}
		return buffer;
	}

	int File::OverWrite(const wchar_t * filename, const char * text, size_t write_size)
	{
		std::ofstream file;
		if (NULL == filename || NULL == text)
		{
			return -2;
		}
		char * afilename = Matrix::TextEncoder(filename).Ansi();

        file.open(afilename, std::ios_base::out | std::ios_base::binary);

		if (0 >= write_size)
		{
			write_size = strlen(text);
		}
		file.write(text, write_size);
		file.close();

		if (NULL != afilename)
		{
			delete afilename;
			afilename = NULL;
		}
		return 1;
	}

	int File::Write(const wchar_t * filename, const char * text, off_t off, size_t write_size, bool over_write)
	{
		std::fstream file;
		if (NULL == filename || NULL == text)
		{
			return -2;
		}
		char * afilename = Matrix::TextEncoder(filename).Ansi();
		file.open(afilename, std::ios_base::in);
		bool exist = file.is_open();
		file.close();
		if (exist && (false == over_write))
		{
			file.close();
			return 0;
		}
		else if (exist)
		{
			file.open(afilename, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
		}
		else
		{
			file.open(afilename, std::ios_base::out | std::ios_base::binary);
		}
		if (0 >= write_size)
		{
			write_size = strlen(text);
		}
		file.seekg(off);
		file.write(text, write_size);
		file.close();

		if (NULL != afilename)
		{
			delete afilename;
			afilename = NULL;
		}
		return 1;
	}

	int File::Append(const wchar_t * filename, const char * text, size_t app_size)
	{
		std::fstream file;
		if (NULL == filename || NULL == text)
		{
			return -2;
		}
		char * afilename = Matrix::TextEncoder(filename).Ansi();
		file.open(afilename, std::ios_base::app | std::ios_base::binary);
		if (!file.is_open())
		{
			file.close();
			file.open(afilename, std::ios_base::out | std::ios_base::binary);
		}
		else if (0 >= app_size)
		{
			app_size = strlen(text);
		}
		file.write(text, app_size);
		file.close();

		if (NULL != afilename)
		{
			delete afilename;
			afilename = NULL;
		}
		return 0;
	}

}
