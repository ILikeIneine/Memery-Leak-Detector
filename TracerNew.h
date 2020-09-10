#ifndef TRACER_NEW_H_
#define TRACER_NEW_H_
#include <map>

void* operator new(size_t size, const char* filename, long line);
void operator delete(void* p);

class TracerNew
{
	//store the infos 
	class TracerNewInfo {
	public:
		TracerNewInfo(const char* filename = nullptr, long lint = 0);
		const char* Getfile() const;
		long Line() const;
	private:
		const char* file_;
		long line_;
	};
	class Lock {
	public:
		// Locking BEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEP
		Lock(TracerNew& tracer) :tracer_(tracer) { tracer.Lock_++; }
		//Unlock TIKTOK
		~Lock() { tracer_.Lock_--; }
	private:
		TracerNew &tracer_;
	};
public:
	static bool ready;
	TracerNew();
	~TracerNew();
	void Add(void* p, const char* filename, long line);
	void Remove(void* p);
	void Dump();			//��ӡ�ڴ���Ϣ
private:
	int Lock_;
	std::map<void*, TracerNewInfo> infos_;	//���������Ϣ
};


extern TracerNew NewTracer;

#endif // !TRACER_NEW_H_
