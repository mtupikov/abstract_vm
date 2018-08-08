#ifndef ABSTRACT_VM_IOPERAND_HPP
#define ABSTRACT_VM_IOPERAND_HPP

#include <iostream>
#include "eOperandType.hpp"
#include <AssertMacros.h>

class IOperand {
public:
	virtual int					getPrecision() const = 0;
	virtual eOperandType		getType() const = 0;
	virtual IOperand const		*operator+(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator-(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator*(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator/(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator%(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator^(IOperand const &rhs) const = 0;
	virtual std::string const 	&toString() const = 0;
	virtual ~IOperand() {}
};

#endif
