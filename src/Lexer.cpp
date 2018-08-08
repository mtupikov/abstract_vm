#include <fstream>
#include <array>
#include "../inc/Lexer.hpp"
#include "../inc/Exceptions.hpp"
#include "../inc/Commands.hpp"

bool exitInInput = false;

void Lexer::checkForLexErrors(int argc, char **argv, std::list<command> *list) {
	if (argc > 2)
		throw TooManyArgsException();
	else if (argc == 1)
		readFromStdIn(list);
	else
		readFromFile(list, argv[1]);
}

void Lexer::readFromFile(std::list<command> *list, char *filename) {
	std::fstream	fs;
	std::string		out;
	bool			exit = false;

	fs.open(filename, std::fstream::in);
	if (!fs.is_open())
		throw OpenFileException();
	while (std::getline(fs, out)) {
		std::cout << out << std::endl;
		if (!checkInput(out, list))
			exit = true;
	}
	fs.close();
	if (exit || !exitInInput)
		throw LexerException();
}

void Lexer::readFromStdIn(std::list<command> *list) {
	bool	exit = false;

	for (std::string line; std::getline(std::cin, line) && !std::regex_match(line, std::regex("((\\s)+)?(;;)((\\s)+)?"));)
		if (!checkInput(line, list))
			exit = true;
	if (exit || !exitInInput)
		throw LexerException();
}

bool Lexer::checkInput(std::string s, std::list<command> *list) {
	std::array<std::regex, 20> regex;
	regex[0] =	"((\\s)+)?(push)((\\s)+)?"
				"(int8|int16|int32|float|double)((\\s)+)?"
				"\\(((\\s)+)?"
				"(\\+|-)?[\\d]+(\\.[\\d]+)?((\\s)+)?"
				"\\)((\\s)+)?"
				"(;(.+)?)?";
	regex[1] =	"((\\s)+)?(assert)((\\s)+)?"
				"(int8|int16|int32|float|double)((\\s)+)?"
				"\\(((\\s)+)?"
				"(\\+|-)?[\\d]+(\\.[\\d]+)?((\\s)+)?"
				"\\)((\\s)+)?"
				"(;(.+)?)?";
	regex[2] =	"((\\s)+)?(add)((\\s)+)?(;(.+)?)?";
	regex[3] =	"((\\s)+)?(sub)((\\s)+)?(;(.+)?)?";
	regex[4] =	"((\\s)+)?(mul)((\\s)+)?(;(.+)?)?";
	regex[5] =	"((\\s)+)?(div)((\\s)+)?(;(.+)?)?";
	regex[6] =	"((\\s)+)?(mod)((\\s)+)?(;(.+)?)?";
	regex[7] =	"((\\s)+)?(pow)((\\s)+)?(;(.+)?)?";
	regex[8] =	"((\\s)+)?(pop)((\\s)+)?(;(.+)?)?";
	regex[9] =	"((\\s)+)?(dump)((\\s)+)?(;(.+)?)?";
	regex[10] =	"((\\s)+)?(print)((\\s)+)?(;(.+)?)?";
	regex[11] =	"((\\s)+)?(exit)((\\s)+)?(;(.+)?)?";
	regex[12] =	"((\\s)+)?";
	regex[13] =	"((\\s)+)?;(.+)?";
	regex[14] =	"((\\s)+)?int8((\\s)+)?";
	regex[15] =	"((\\s)+)?int16((\\s)+)?";
	regex[16] =	"((\\s)+)?int32((\\s)+)?";
	regex[17] =	"((\\s)+)?float((\\s)+)?";
	regex[18] =	"((\\s)+)?double((\\s)+)?";
	regex[19] =	"\\(((\\s)+)?(\\+|-)?[\\d]+(\\.[\\d]+)?((\\s)+)?\\)";

	for (int i = 0; i < 14; i++)
		if (std::regex_match(s, std::regex(regex[i]))) {
			if (i > 1 && i < 12) {
				command cmd;
				if (i == 11)
					exitInInput = true;
				cmd.type = static_cast<commandType>(i);
				list->push_back(cmd);
			} else if (i != 12 && i != 13){
				createCommand(list, regex, s);
			}
			return true;
		}
	std::cerr << "Lexer error" << std::endl;
	return false;
}

void Lexer::createCommand(std::list<command> *list, const std::array<std::regex, 20> &regex, std::string &item) {
	command cmd;
	std::smatch resultMatch;

	if (std::regex_search(item, regex[0]))
		cmd.type = Push;
	else if (std::regex_search(item, regex[1]))
		cmd.type = Assert;

	if (std::regex_search(item, regex[14]))
		cmd.valueType = Int8;
	else if (std::regex_search(item, regex[15]))
		cmd.valueType = Int16;
	else if (std::regex_search(item, regex[16]))
		cmd.valueType = Int32;
	else if (std::regex_search(item, regex[17]))
		cmd.valueType = Float;
	else if (std::regex_search(item, regex[18]))
		cmd.valueType = Double;

	std::regex_search(item, resultMatch, regex[19]);
	size_t start = static_cast<size_t>(resultMatch.prefix().length()) + 1;
	size_t lenNumber = item.length() - start - resultMatch.suffix().length() - 1;
	cmd.strValue = item.substr(start, lenNumber);
	cmd.strValue = trim(cmd.strValue);
	cmd.value = std::stold(cmd.strValue);
	list->push_back(cmd);
}

const std::string& Lexer::trim(std::string &s) {
	const char* ws = " \t\n\r\f\v";
	s.erase(0, s.find_first_not_of(ws));
	s.erase(s.find_last_not_of(ws) + 1);
	return s;
}
