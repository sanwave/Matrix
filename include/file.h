
/*
*
*
*
*	File Class Header File		In Matrix
*
*	Created by Bonbon	2014.09.25
*
*	Updated by Bonbon	2015.01.10
*
*/


#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include <string>
#include <fstream>

#include "text_encoder.h"

#define FBUFSIZ 4096
#define FPAGESIZ 1024 * 1024

namespace Matrix
{
	enum FilePos
	{
		HEAD,
		INSIDE,
		END
	};

	enum ReadSize
	{
		FILEAll = -1,
		FILEPAGE
	};

	class File
	{
	public:

		File(const char *filename);

		File(const wchar_t *filename);

		File(const File& src);

		~File();

		TextEncode Encode();

		const wchar_t* FileName() const;

		const wchar_t * Text(int page = 0, size_t *size = NULL);

		const char * AnsiText(int page = 0, size_t *size = NULL);

		const char * Utf8Text(int page = 0, size_t *size = NULL);

		const char * Binary(int page = 0, size_t *size = NULL);

		int OverWrite(const char * text, size_t size = 0);

		int WriteText(const char * text, size_t size = 0, bool over_write = false);

		int AppendText(const char * text, size_t size = 0);

		int Exist();

		size_t GetSize();

		static int Exist(const char * filename);

		static size_t GetSize(const char * filename);

		static const wchar_t * ReadAsText(const char *filename, int page = 0);

		static const wchar_t * ReadAsText(const wchar_t *filename, int page = 0);

		static const char * ReadAsBinary(const char * filename, int page = 0);

		static const char * ReadAsBinary(const wchar_t * filename, int page = 0);

		static const char * ReadBlock(const wchar_t * filename, off_t off = 0, size_t read_size = FPAGESIZ);

		static int OverWrite(const wchar_t * filename, const char * text, size_t write_size = 0);

		static int Write(const wchar_t * filename, const char * text, off_t off = 0, size_t write_size = 0, bool over_write = false);

		static int Append(const wchar_t * filename, const char * text, size_t app_size = 0);

	private:
		wchar_t *m_filename;
	};
}

#endif