#include "TracerNew.h"
#include <cstdlib>
#include <iostream>
TracerNew NewTracer;
bool TracerNew::ready = false;
void TracerNew::Add(void* p, const char* filename, long line)
{
	if (TracerNew::Lock_ > 0)
		return;
	Lock lock(*this);
	//临界区
	infos_[p] = TracerNewInfo(filename, line);	//may new
	//临界区
}

void TracerNew::Remove(void* p)
{
	if (TracerNew::Lock_ > 0)
		return;
	Lock lock(*this);
	//临界区
	auto it = infos_.find(p);
	if (it != infos_.end())
	{
		infos_.erase(it);		// may delete
	}
	//临界区
}

void TracerNew::Dump()
{
	for(auto tracer_info : infos_)
	{
		std::cout << "0x" << tracer_info.first << ":\t" << tracer_info.second.Getfile() << "\t at Line:" << tracer_info.second.Line() << std::endl;
	}
}

void* operator new(size_t size, const char* filename, long line)
{
	void* p = malloc(size);
	if (TracerNew::ready)
		NewTracer.Add(p, filename, line);
	return p;
}

void operator delete(void* p)
{
	if (TracerNew::ready)
		NewTracer.Remove(p);
	free(p);
}

TracerNew::TracerNewInfo::TracerNewInfo( const char* file, long line) : file_(file), line_(line)
{

}

const char* TracerNew::TracerNewInfo::Getfile() const
{
	return file_;
}

long TracerNew::TracerNewInfo::Line() const
{
	return line_;
}

TracerNew::TracerNew()
{
	ready = true;
}


TracerNew::~TracerNew()
{
	ready = false;
	NewTracer.Dump();
}


