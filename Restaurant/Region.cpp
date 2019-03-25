#include "Region.h"
#include <string>
int Region::cnt = 0;
Region::Region()
{
	name = 'A' + cnt;
	cnt++;
}

Motorcycle* Region::getVIPMotor() 
{
	Motorcycle*M=VIPMotor.peek();
	return M;
}
Motorcycle* Region::getFrozenMotor() 
{
	Motorcycle*M=FrozenMotor.peek();
	return M;
}
Motorcycle* Region::getNormalMotor() 
{
	Motorcycle*M=NormalMotor.peek();
	return M;
}
Order* Region::getVIPOrder() 
{
	Order*O=VIPOrder.peek();
	return O;
}
Order* Region::getFrozenOrder() 
{
	return FrozenOrder.removeBegin();
}
Order* Region::getNormalOrder() 
{
	return NormalOrder.removeBegin();
}
void Region::setVIPMotor(Motorcycle* V)
{
	VIPMotor.add(V);
}
void Region::setFrozenMotor(Motorcycle* F)
{
	FrozenMotor.add(F);
}
void Region::setNormalMotor(Motorcycle* N)
{
	NormalMotor.add(N);
}
void Region::setVIPOrder( Order* O)
{
	VIPOrder.add(O);
}
void Region::setFrozenOrder(Order* O)
{
	FrozenOrder.add(O);
}
void Region::setNormalOrder(Order* O)
{
	NormalOrder.add(O);
}
bool Region::VIPOrderIsEmpty()
{
	return VIPOrder.isEmpty();
}
bool Region::NormalOrderIsEmpty()
{
	return NormalOrder.isEmpty();
}
bool Region::FrozenOrderIsEmpty()
{
	return FrozenOrder.isEmpty();
}
bool Region::CancelOrder(int id)
{
	
	return NormalOrder.removeID(id);
}

//Draw functions

Order* Region::getNormalDraw(Order* O) 
{
	NormalDraw.dequeue(O);
	 return O;
}
void Region::setNormalDraw(Order* O)
{
	NormalDraw.enqueue(O);
}
bool Region::NormalDrawIsEmpty()
{
	return NormalDraw.isEmpty();
}
string Region::Print()
{
	return "Region " + name + ":    Motors -->  VIP: " + to_string(VIPMotor.Size()) + "    Frozen: " + to_string(FrozenMotor.Size()) + "    Normal: " + to_string(NormalMotor.Size())
			+ "                                                                          Orders -->  VIP: " + to_string(VIPOrder.Size()) + "    Frozen: " + to_string(FrozenOrder.Size()) + "    Normal: " + to_string(NormalOrder.Size());
}
void Region::CopyOrderstoDraw()
{
	Queue<Order*> Q;Order* O;
	while(!VIPOrderIsEmpty())
	{
		O=VIPOrder.peek();
		VIPOrder.remove();
		NormalDraw.enqueue(O);
		Q.enqueue(O);

	}
	while(Q.dequeue(O))
	{
		VIPOrder.add(O);

	}
	for(int i=1;i<=FrozenOrder.Size();i++)
	{
		NormalDraw.enqueue(FrozenOrder.getEntry(i));
	}
	for(int i=1;i<=NormalOrder.Size();i++)
	{
		NormalDraw.enqueue(NormalOrder.getEntry(i));
	}
	
}

////////////////////////////////////////////////////
Region::~Region()
{
}
