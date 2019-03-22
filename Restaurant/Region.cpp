#include "Region.h"


Region::Region()
{

}

Motorcycle* Region::getVIPMotor() const
{
	return VIPMotor.peek();
}
Motorcycle* Region::getFrozenMotor() const
{
	return FrozenMotor.peek();
}
Motorcycle* Region::getNormalMotor() const
{
	return NormalMotor.peek();
}
Order* Region::getVIPOrder() const
{
	return VIPOrder.peek();
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
Region::~Region()
{
}
