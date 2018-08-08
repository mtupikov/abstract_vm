#ifndef ABSTRACT_VM_OPERANDFACTORY_HPP
#define ABSTRACT_VM_OPERANDFACTORY_HPP

#include <iostream>
#include <vector>
#include <map>
#include "IOperand.hpp"

class OperandFactory {
public:
	static IOperand const					*createOperand(eOperandType type, std::string const & value);
	static int								static_init();
private:
	OperandFactory();
	OperandFactory(const OperandFactory&);
	~OperandFactory();
	const OperandFactory&					operator=(const OperandFactory&);
	static IOperand const					*createInt8(std::string const & value);
	static IOperand const					*createInt16(std::string const & value);
	static IOperand const					*createInt32(std::string const & value);
	static IOperand const					*createFloat(std::string const & value);
	static IOperand const					*createDouble(std::string const & value);

	static std::map<eOperandType, IOperand const *(*)(std::string const &value)>	_get;
};

#endif
