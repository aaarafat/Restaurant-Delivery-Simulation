#include "Region.h"


Region::Region()
{

}

Motorcycle* Region::getVIPMotor() 
{
	Motorcycle*M=VIPMotor.peek();
	VIPMotor.remove();
	return M;
}
Motorcycle* Region::getFrozenMotor() 
{
	Motorcycle*M=FrozenMotor.peek();
	FrozenMotor.remove();
	return M;
}
Motorcycle* Region::getNormalMotor() 
{
	Motorcycle*M=NormalMotor.peek();
	NormalMotor.remove();
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

Region::~Region()
{
}
