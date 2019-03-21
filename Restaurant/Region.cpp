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
void Region::setVIPMotor(const Motorcycle& V)
{
	VIPMotor.add(V);
}
void Region::setFrozenMotor(const Motorcycle& F)
{
	FrozenMotor.add(F);
}
void Region::setNormalMotor(const Motorcycle& N)
{
	NormalMotor.add(N);
}
void Region::setVIPOrder(const Order& O)
{
	VIPOrder.add(O);
}
Region::~Region()
{
}
