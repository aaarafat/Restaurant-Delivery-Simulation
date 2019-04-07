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
	VIPOrder.remove();
	return O;
}
Order* Region::getFrozenOrder() 
{
	Order* O;
	FrozenOrder.removeBegin(O);
	return O;
}
Order* Region::getNormalOrder() 
{
	Order* O;
	NormalOrder.removeBegin(O);
	return O;
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

Order* Region::getDrawOrders(Order* O) 
{
	DrawOrders.dequeue(O);
	 return O;
}
void Region::setDrawOrders(Order* O)
{
	DrawOrders.enqueue(O);
}
bool Region::DrawOrdersIsEmpty()
{
	return DrawOrders.isEmpty();
}
string Region::Print()
{
	return "Region " + name + ":    Motors -->  VIP: " + to_string(VIPMotor.Size()) + "    Frozen: " + to_string(FrozenMotor.Size()) + "    Normal: " + to_string(NormalMotor.Size())
			+ "                                                                          Orders -->  VIP: "
			+ to_string(VIPOrder.Size()) + "    Frozen: " + to_string(FrozenOrder.Size()) + "    Normal: " + to_string(NormalOrder.Size());
}
void Region::CopyOrderstoDraw()
{
	Queue<Order*> Q;Order* O;
	while(!VIPOrderIsEmpty())
	{
		O=VIPOrder.peek();
		VIPOrder.remove();
		DrawOrders.enqueue(O);
		Q.enqueue(O);

	}
	while(Q.dequeue(O))
	{
		VIPOrder.add(O);

	}
	for(int i=1;i<=FrozenOrder.Size();i++)
	{
		DrawOrders.enqueue(FrozenOrder.getEntry(i));
	}
	for(int i=1;i<=NormalOrder.Size();i++)
	{
		DrawOrders.enqueue(NormalOrder.getEntry(i));
	}
	
}

////////////////////////////////////////////////////
Region::~Region()
{
}
