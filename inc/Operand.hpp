#ifndef OPERAND_H
# define OPERAND_H

#include "IOperand.hpp"
#include <limits>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "Exceptions.hpp"
#include "OperandFactory.hpp"

template <typename T>
class Operand : public IOperand {
public:
	Operand(std::string const &value, eOperandType type, int precision):
	_type(type),
	_precision(precision) {
		std::stringstream ss;
		if (type < Float) {
			long long v = std::stoll(value);
			checkPrecision(type, v);
			_value = static_cast<T>(v);
			ss << std::setprecision(precision) << v;
			_str_value = ss.str();
		} else {
			long double	v = std::stold(value);
			checkPrecision(type, v);
			_value = static_cast<T>(v);
			ss << std::setprecision(precision) << std::fixed << v;
			_str_value = ss.str();
		}
	}

	int getPrecision() const override {
		return _precision;
	}

	eOperandType getType() const override {
		return _type;
	}

	const IOperand *operator+(IOperand const &rhs) const override {
		eOperandType type = _type > rhs.getType() ? _type : rhs.getType();
		int precision = _precision > rhs.getPrecision() ? _precision : rhs.getPrecision();
		std::stringstream ss;
		if (type < Float) {
			long long ret = std::stoll(_str_value) + std::stoll(rhs.toString());
			checkPrecision(type, ret);
			ss << ret;
			return OperandFactory::createOperand(type, ss.str());
		} else {
			long double ret = std::stold(_str_value) + std::stold(rhs.toString());
			checkPrecision(type, ret);
			ss << std::setprecision(precision) << std::fixed << ret;
			return OperandFactory::createOperand(type, ss.str());
		}
	}

	const IOperand *operator-(IOperand const &rhs) const override {
		eOperandType type = _type > rhs.getType() ? _type : rhs.getType();
		int precision = _precision > rhs.getPrecision() ? _precision : rhs.getPrecision();
		std::stringstream ss;
		if (type < Float) {
			long long ret = std::stoll(_str_value) - std::stoll(rhs.toString());
			checkPrecision(type, ret);
			ss << ret;
			return OperandFactory::createOperand(type, ss.str());
		} else {
			long double ret = std::stold(_str_value) - std::stold(rhs.toString());
			checkPrecision(type, ret);
			ss << std::setprecision(precision) << std::fixed << ret;
			return OperandFactory::createOperand(type, ss.str());
		}
	}

	const IOperand *operator*(IOperand const &rhs) const override {
		eOperandType type = _type > rhs.getType() ? _type : rhs.getType();
		int precision = _precision > rhs.getPrecision() ? _precision : rhs.getPrecision();
		std::stringstream ss;
		if (type < Float) {
			long long ret = std::stoll(_str_value) * std::stoll(rhs.toString());
			checkPrecision(type, ret);
			ss << ret;
			return OperandFactory::createOperand(type, ss.str());
		} else {
			long double ret = std::stold(_str_value) * std::stold(rhs.toString());
			checkPrecision(type, ret);
			ss << std::setprecision(precision) << std::fixed << ret;
			return OperandFactory::createOperand(type, ss.str());
		}
	}

	const IOperand *operator/(IOperand const &rhs) const override {
		eOperandType type = _type > rhs.getType() ? _type : rhs.getType();
		int precision = _precision > rhs.getPrecision() ? _precision : rhs.getPrecision();
		std::stringstream ss;
		if (std::stold(rhs.toString()) == 0)
			throw DivisionByZeroException();
		if (type < Float) {
			long long ret = std::stoll(_str_value) / std::stoll(rhs.toString());
			checkPrecision(type, ret);
			ss << ret;
			return OperandFactory::createOperand(type, ss.str());
		} else {
			long double ret = std::stold(_str_value) / std::stold(rhs.toString());
			checkPrecision(type, ret);
			ss << std::setprecision(precision) << std::fixed << ret;
			return OperandFactory::createOperand(type, ss.str());
		}
	}

	const IOperand *operator%(IOperand const &rhs) const override {
		eOperandType type = _type > rhs.getType() ? _type : rhs.getType();
		int precision = _precision > rhs.getPrecision() ? _precision : rhs.getPrecision();
		std::stringstream ss;
		if (std::stold(rhs.toString()) == 0)
			throw DivisionByZeroException();
		if (type < Float) {
			long long ret = std::stoll(_str_value) % std::stoll(rhs.toString());
			checkPrecision(type, ret);
			ss << ret;
			return OperandFactory::createOperand(type, ss.str());
		} else {
			long double ret = fmod(std::stod(_str_value), std::stod(rhs.toString()));
			checkPrecision(type, ret);
			ss << std::setprecision(precision) << std::fixed << ret;
			return OperandFactory::createOperand(type, ss.str());
		}
	}

	const IOperand *operator^(IOperand const &rhs) const override {
		eOperandType type = _type > rhs.getType() ? _type : rhs.getType();
		int precision = _precision > rhs.getPrecision() ? _precision : rhs.getPrecision();
		std::stringstream ss;
		if (type < Float) {
			long long ret = static_cast<long long>(pow(std::stoll(_str_value),  std::stoll(rhs.toString())));
			checkPrecision(type, ret);
			ss << ret;
			return OperandFactory::createOperand(type, ss.str());
		} else {
			long double ret = powl(std::stold(_str_value),  std::stold(rhs.toString()));
			checkPrecision(type, ret);
			ss << std::setprecision(precision) << std::fixed << ret;
			return OperandFactory::createOperand(type, ss.str());
		}
	}

	const std::string &toString() const override {
		return _str_value;
	}

private:
	T				_value;
	eOperandType 	_type;
	int 			_precision;
	std::string		_str_value;

	Operand() {};
	~Operand() {};
	Operand(const Operand&) {};
	const Operand &operator=(const Operand&) {};
	template <typename K>
	void checkPrecision(eOperandType type, K value) const {
		switch (type) {
			case Int8:
				if (value < std::numeric_limits<char>::min())
					throw UnderflowException("Underflow of Int8");
				else if (value > std::numeric_limits<char>::max())
					throw OverflowException("Overflow of Int8");
				break;
			case Int16:
				if (value < std::numeric_limits<short>::min())
					throw UnderflowException("Underflow of Int16");
				else if (value > std::numeric_limits<short>::max())
					throw OverflowException("Overflow of Int16");
				break;
			case Int32:
				if (value < std::numeric_limits<int>::min())
					throw UnderflowException("Underflow of Int32");
				else if (value > std::numeric_limits<int>::max())
					throw OverflowException("Overflow of Int23");
				break;
			case Float:
				if (value < -std::numeric_limits<float>::max())
					throw UnderflowException("Underflow of Float");
				else if (value > std::numeric_limits<float>::max())
					throw OverflowException("Overflow of Float");
				break;
			case Double:
				if (value < -std::numeric_limits<double >::max())
					throw UnderflowException("Underflow of Double");
				else if (value > std::numeric_limits<double >::max())
					throw OverflowException("Overflow of Double");
				break;
		}
	}
};

#endif
