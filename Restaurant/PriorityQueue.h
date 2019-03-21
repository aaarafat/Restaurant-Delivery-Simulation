#pragma once
template<class T>
class PriorityQueue
{
	int size;
	virtual bool SplitUp() = 0;
	virtual bool SplitDown() = 0;
public:
	virtual T ExtractMax() = 0;
	virtual int Size() = 0;
	PriorityQueue(void);
	virtual ~PriorityQueue(void);
};

