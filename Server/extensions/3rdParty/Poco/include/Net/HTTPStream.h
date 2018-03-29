//
// HTTPStream.h
//
// $Id: //poco/1.3/Net/include/Poco/Net/HTTPStream.h#2 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPStream
//
// Definition of the HTTPStream class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Net_HTTPStream_INCLUDED
#define Net_HTTPStream_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPBasicStreamBuf.h"
#include "Poco/MemoryPool.h"
#include <cstddef>
#include <istream>
#include <ostream>


namespace Poco {
namespace Net {


class HTTPSession;


class Net_API HTTPStreamBuf: public HTTPBasicStreamBuf
	/// This is the streambuf class used for reading and writing
	/// HTTP message bodies.
{
public:
	typedef HTTPBasicStreamBuf::openmode openmode;

	HTTPStreamBuf(HTTPSession& session, openmode mode);
	~HTTPStreamBuf();
	void close();
	
protected:
	int readFromDevice(char* buffer, std::streamsize length);
	int writeToDevice(const char* buffer, std::streamsize length);

private:
	HTTPSession& _session;
	openmode     _mode;
};


class Net_API HTTPIOS: public virtual std::ios
	/// The base class for HTTPInputStream.
{
public:
	HTTPIOS(HTTPSession& session, HTTPStreamBuf::openmode mode);
	~HTTPIOS();
	HTTPStreamBuf* rdbuf();

protected:
	HTTPStreamBuf _buf;
};


class Net_API HTTPInputStream: public HTTPIOS, public std::istream
	/// This class is for internal use by HTTPSession only.
{
public:
	HTTPInputStream(HTTPSession& session);
	~HTTPInputStream();

	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	
private:
	static Poco::MemoryPool _pool;
};


class Net_API HTTPOutputStream: public HTTPIOS, public std::ostream
	/// This class is for internal use by HTTPSession only.
{
public:
	HTTPOutputStream(HTTPSession& session);
	~HTTPOutputStream();

	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	
private:
	static Poco::MemoryPool _pool;
};


} } // namespace Poco::Net


#endif // Net_HTTPStream_INCLUDED
