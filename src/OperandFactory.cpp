#include "../inc/OperandFactory.hpp"
#include "../inc/Operand.hpp"

OperandFactory::OperandFactory() {}

OperandFactory::OperandFactory(const OperandFactory&) {}

OperandFactory::~OperandFactory() {}

const OperandFactory 	&OperandFactory::operator=(const OperandFactory &of) { return of; }

IOperand const			*OperandFactory::createOperand(eOperandType type, std::string const &value) {
	if (type < Float && value.find('.') != std::string::npos)
		throw PrecisionInIntTypeException();
	IOperand const *(*f)(std::string const &value);
	f = _get.at(type);
	return (f(value));
}

IOperand const			*OperandFactory::createInt8(std::string const &value) {
	return (new Operand<char>(value, Int8, 0));
}

IOperand const			*OperandFactory::createInt16(std::string const &value) {
	return (new Operand<short >(value, Int16, 0));
}

IOperand const			*OperandFactory::createInt32(std::string const &value) {
	return (new Operand<int>(value, Int32, 0));
}

IOperand const			*OperandFactory::createFloat(std::string const &value) {
	return (new Operand<float>(value, Float, 7));
}

IOperand const			*OperandFactory::createDouble(std::string const &value) {
	return (new Operand<double >(value, Double, 14));
}

int						OperandFactory::static_init()
{
	_get[Int8] = &OperandFactory::createInt8;
	_get[Int16] = &OperandFactory::createInt16;
	_get[Int32] = &OperandFactory::createInt32;
	_get[Float] = &OperandFactory::createFloat;
	_get[Double] = &OperandFactory::createDouble;
	return 42;
}

std::map<eOperandType, IOperand const *(*)(std::string const &value)>	OperandFactory::_get;
