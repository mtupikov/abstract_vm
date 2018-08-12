#include <limits>
#include <iomanip>
#include "../inc/Parser.hpp"
#include "../inc/Exceptions.hpp"

Parser::Parser() = default;

Parser::~Parser() = default;

void Parser::executeCommands(std::list<command> commands) {
	try {
		for (command cmd : commands) {
			checkValue(cmd);
			switch (cmd.type) {
				case Push:
					push(cmd);
					break;
				case Pop:
					pop();
					break;
				case Dump:
					dump();
					break;
				case Assert:
					assert(cmd);
					break;
				case Add:
					add();
					break;
				case Sub:
					sub();
					break;
				case Mul:
					mul();
					break;
				case Div:
					div();
					break;
				case Mod:
					mod();
					break;
				case Pow:
					pow();
					break;
				case Sqrt:
					sqrt();
					break;
				case Min:
					min();
					break;
				case Max:
					max();
					break;
				case Clear:
					clear();
					break;
				case Print:
					print();
					break;
				case Exit:
					return;
			}
		}
	} catch (TypesAreNotEqualException &e) {
		std::cout << e.what() << std::endl;
	} catch (AssertException &e) {
		std::cout << e.what() << std::endl;
	} catch (NotInt8Exception &e) {
		std::cout << e.what() << std::endl;
	} catch (EmptyStackException &e) {
		std::cout << e.what() << std::endl;
	} catch (OverflowException &e) {
		std::cout << e.what() << std::endl;
	} catch (UnderflowException &e) {
		std::cout << e.what() << std::endl;
	} catch (DivisionByZeroException &e) {
		std::cout << e.what() << std::endl;
	} catch (PrecisionInIntTypeException &e) {
		std::cout << e.what() << std::endl;
	} catch (std::out_of_range &e) {
		std::cout << e.what() << std::endl;
	}
	for (const IOperand *op : _operands)
		delete op;
}

void							Parser::push(const command &cmd) {
	_operands.push_front(OperandFactory::createOperand(cmd.valueType, cmd.strValue));
}

void							Parser::pop() {
	checkForEmptyStack();
	_operands.pop_front();
}

void							Parser::dump() {
	checkForEmptyStack();
	for (const IOperand *op : _operands)
		std::cout << std::setprecision(op->getPrecision()) << std::fixed << op->toString() << std::endl;
}

void							Parser::assert(const command &cmd) {
	checkForEmptyStack();
	const IOperand *op1 = _operands.front();
	_operands.pop_front();
	const IOperand *op2 = OperandFactory::createOperand(cmd.valueType, cmd.strValue);
	checkForEqualTypes(op1, op2);
	if (std::stod(op1->toString()) != std::stod(op2->toString())) {
		delete op1;
		delete op2;
		throw AssertException();
	}
	delete op1;
	delete op2;
}

void							Parser::add() {
	checkForEmptyStack();
	const IOperand *op1 = _operands.front();
	_operands.pop_front();
	checkForEmptyStack();
	const IOperand *op2 = _operands.front();
	_operands.pop_front();
	_operands.push_front(*op2 + *op1);
	delete op1;
	delete op2;
}

void							Parser::sub() {
	checkForEmptyStack();
	const IOperand *op1 = _operands.front();
	_operands.pop_front();
	checkForEmptyStack();
	const IOperand *op2 = _operands.front();
	_operands.pop_front();
	_operands.push_front(*op2 - *op1);
	delete op1;
	delete op2;
}

void							Parser::mul() {
	checkForEmptyStack();
	const IOperand *op1 = _operands.front();
	_operands.pop_front();
	checkForEmptyStack();
	const IOperand *op2 = _operands.front();
	_operands.pop_front();
	_operands.push_front(*op2 * *op1);
	delete op1;
	delete op2;
}

void							Parser::div() {
	checkForEmptyStack();
	const IOperand *op1 = _operands.front();
	_operands.pop_front();
	checkForEmptyStack();
	const IOperand *op2 = _operands.front();
	_operands.pop_front();
	_operands.push_front(*op2 / *op1);
	delete op1;
	delete op2;
}

void							Parser::mod() {
	checkForEmptyStack();
	const IOperand *op1 = _operands.front();
	_operands.pop_front();
	checkForEmptyStack();
	const IOperand *op2 = _operands.front();
	_operands.pop_front();
	_operands.push_front(*op2 % *op1);
	delete op1;
	delete op2;
}

void							Parser::pow() {
	checkForEmptyStack();
	const IOperand *op1 = _operands.front();
	_operands.pop_front();
	checkForEmptyStack();
	const IOperand *op2 = _operands.front();
	_operands.pop_front();
	_operands.push_front(*op2 ^ *op1);
	delete op1;
	delete op2;
}

void							Parser::sqrt() {
	checkForEmptyStack();
	const IOperand *op1 = _operands.front();
	_operands.pop_front();
	double sq = ::sqrt(std::stold(op1->toString()));
	std::ostringstream strs;
	strs << sq;
	std::string str = strs.str();
	_operands.push_front(OperandFactory::createOperand(Double, str));
}


void							Parser::min() {
	checkForEmptyStack();
	const IOperand *min = _operands.front();
	for (const IOperand *op : _operands)
		if (std::stold(min->toString()) > std::stold(op->toString()))
			min = op;
	std::cout << "Min: " << std::setprecision(min->getPrecision()) << std::fixed << min->toString() <<std::endl;
}

void							Parser::max() {
	checkForEmptyStack();
	const IOperand *max = _operands.front();
	for (const IOperand *op : _operands)
		if (std::stold(max->toString()) < std::stold(op->toString()))
			max = op;
	std::cout << "Max: " << std::setprecision(max->getPrecision()) << std::fixed << max->toString() <<std::endl;
}

void							Parser::clear() {
	_operands.clear();
}


void							Parser::print() {
	checkForEmptyStack();
	const IOperand *op1 = _operands.front();
	if (op1->getType() != Int8)
		throw NotInt8Exception();
	std::cout << static_cast<char>(std::stoi(op1->toString())) << std::endl;
}

void 						Parser::checkForEmptyStack() {
	if (_operands.empty())
		throw EmptyStackException();
}

void 						Parser::checkForEqualTypes(const IOperand *op1, const IOperand *op2) {
	if (op1->getType() != op2->getType()) {
		delete op1;
		delete op2;
		throw TypesAreNotEqualException();
	}
}

void Parser::checkValue(const command &cmd) {
	switch (cmd.valueType) {
		case Int8: {
			auto c = static_cast<char>(cmd.value);
			if (c < std::numeric_limits<char>::min())
				throw UnderflowException("Underflow of Int8");
			else if (c > std::numeric_limits<char>::max())
				throw OverflowException("Overflow of Int8");
			break;
		}
		case Int16: {
			auto s = static_cast<short>(cmd.value);
			if (s < std::numeric_limits<short>::min())
				throw UnderflowException("Underflow of Int16");
			else if (s > std::numeric_limits<short>::max())
				throw OverflowException("Overflow of Int16");
			break;
		}
		case Int32: {
			auto i = static_cast<int>(cmd.value);
			if (i < std::numeric_limits<int>::min())
				throw UnderflowException("Underflow of Int32");
			else if (i > std::numeric_limits<int>::max())
				throw OverflowException("Overflow of Int23");
			break;
		}
		case Float: {
			auto f = static_cast<float>(cmd.value);
			if (f < -std::numeric_limits<float>::max())
				throw UnderflowException("Underflow of Float");
			else if (f > std::numeric_limits<float>::max())
				throw OverflowException("Overflow of Float");
			break;
		}
		case Double: {
			auto d = static_cast<double>(cmd.value);
			if (d < -std::numeric_limits<double>::max())
				throw UnderflowException("Underflow of Double");
			else if (d > std::numeric_limits<double>::max())
				throw OverflowException("Overflow of Double");
			break;
		}
	}
}

std::forward_list<const IOperand *>	Parser::_operands;
