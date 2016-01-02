#pragma once

#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include "main.h"
#include "data_value.h"

const uint MAX_STACK_SIZE = 128;

enum Instruction{
	INST_DEFINE_INTEGER	  = 0x00,
	INST_DEFINE_DOUBLE	  = 0x01,
	INST_DEFINE_CHARACTER = 0x02,

	INST_NEW_LINE = 0x03,
	INST_DELETE	  = 0x04,

	INST_ADD	  = 0x05,
	INST_SUBTRACT = 0x06,
	INST_MULTIPLY = 0x07,
	INST_DIVIDE	  = 0x08,

	INST_CONSOLE_OUT = 0x09,
	INST_CONSOLE_IN	 = 0x10
};

enum Error{
	ERROR_NONE,
	ERROR_FILE_NF,
	ERROR_SYNTAX,
	ERROR_RUNTIME
};

class Virtual_Machine{
	int stacksize;
	DataValue stack[MAX_STACK_SIZE];

	void push(DataValue value);
	DataValue pop();
	DataValue peek();

	bool inStr(string str, string instr);

public:
	Virtual_Machine(): stacksize(0) {};

	Error compileUCL(const char *filename);
	Error processBytecode(const char *filename);
	Error processBytecodeDebug(const char *filename);
};

void Virtual_Machine::push(DataValue value){
	if(stacksize >= MAX_STACK_SIZE){
		cout << "RUNTIME ERROR: STACK OVERFLOW" << endl;
		return;
	}
	stack[stacksize++] = value;
}
DataValue Virtual_Machine::pop(){
	if(stacksize <= 0){
		cout << "RUNTIME ERROR: STACK EMPTY" << endl;

		DataValue val;
		val.type = TYPE_NONE;
		return val;
	}
	return stack[--stacksize];
}
DataValue Virtual_Machine::peek(){
	if(stacksize <= 0){
		cout << "RUNTIME ERROR: STACK EMPTY" << endl;

		DataValue val;
		val.type = TYPE_NONE;
		return val;
	}
	return stack[stacksize-1];
}

bool Virtual_Machine::inStr(string str, string instr){
	return str.find(instr) == string::npos ? false : true;
}

Error Virtual_Machine::compileUCL(const char *filename){
	fstream infile(filename, ios::in);

	string outstr = filename;

	if(inStr(outstr, ".txt") || inStr(outstr, ".ucl")){
		for(uint i = 0; i < 4; i++)
			outstr.pop_back();
	}

	fstream outfile(outstr + ".ucr", ios::out);

	outfile.clear();

	uint i = 0;

	while(!infile.eof()){
		string line = "";

		getline(infile, line);

		if(inStr(line, "//") || inStr(line, "\n") || line == "")
			continue;

		else if(inStr(line, "integer ")){
			char byte = 0;

			outfile << char(INST_DEFINE_INTEGER);
			sscanf_s(line.c_str(), "integer %i", &byte);
			outfile << byte;
		}
		else if(inStr(line, "double ")){
			char byte = 0;

			outfile << char(INST_DEFINE_DOUBLE);
			sscanf_s(line.c_str(), "double %d", &byte);
			outfile << byte;
		}
		else if(inStr(line, "character ")){
			char byte = 0;
		
			outfile << char(INST_DEFINE_CHARACTER);
			sscanf_s(line.c_str(), "character %c", &byte);
			outfile << byte;
		}

		else if(inStr(line, "newline"))
			outfile << char(INST_NEW_LINE);
		else if(inStr(line, "delete"))
			outfile << char(INST_DELETE);

		else if(inStr(line, "add"))
			outfile << char(INST_ADD);
		else if(inStr(line, "subtract"))
			outfile << char(INST_SUBTRACT);
		else if(inStr(line, "multiply"))
			outfile << char(INST_MULTIPLY);
		else if(inStr(line, "divide"))
			outfile << char(INST_DIVIDE);

		else if(inStr(line, "console out"))
			outfile << char(INST_CONSOLE_OUT);
		else if(inStr(line, "console in"))
			outfile << char(INST_CONSOLE_IN);

		else
			return ERROR_SYNTAX;
	}

	infile.close();
	outfile.close();

	cout << outstr + ".ucr" + " was generated." << endl << endl;

	return ERROR_NONE;
}
Error Virtual_Machine::processBytecode(const char *filename){
	fstream file(filename, ios::in);

	if(!file.is_open())
		return ERROR_FILE_NF;

	while(!file.eof()){
		DataValue value;
		
		char byte = 0;
		file.read(&byte, 1);

		switch(byte){
		case INST_DEFINE_INTEGER:
			file.read(&byte, 1);
			value.type = TYPE_INTEGER;
			value.asInteger = byte;
			push(value);
			break;
		case INST_DEFINE_DOUBLE:
			file.read(&byte, 1);
			value.type = TYPE_DOUBLE;
			value.asDouble = byte;
			push(value);
			break;
		case INST_DEFINE_CHARACTER:
			file.read(&byte, 1);
			value.type = TYPE_CHARACTER;
			value.asCharacter = byte;
			push(value);
			break;

		case INST_NEW_LINE:
			cout << endl;
			break;
		case INST_DELETE:
			pop();
			break;

		case INST_ADD:
			push(pop() + pop());
			break;
		case INST_SUBTRACT:
			push(pop() - pop());
			break;
		case INST_MULTIPLY:
			push(pop() * pop());
			break;
		case INST_DIVIDE:
			push(pop() / pop());
			break;

		case INST_CONSOLE_OUT:			
			switch(peek().type){
			case TYPE_INTEGER:	 cout << peek().asInteger; break;
			case TYPE_DOUBLE:	 cout << peek().asDouble; break;
			case TYPE_CHARACTER: cout << peek().asCharacter; break;
			}
			break;
		case INST_CONSOLE_IN:
			value.type = TYPE_INTEGER;
			cin >> value.asInteger;
			push(value);
			break;
		}
	}

	clearInputBuffer();

	return ERROR_NONE;
}
Error Virtual_Machine::processBytecodeDebug(const char *filename){
	fstream file(filename, ios::in);

	if(!file.is_open())
		return ERROR_FILE_NF;

	while(!file.eof()){
		DataValue value;
		
		char byte = 0;
		file.read(&byte, 1);

		switch(byte){
		case INST_DEFINE_INTEGER:
			file.read(&byte, 1);
			value.type = TYPE_INTEGER;
			value.asInteger = byte;
			push(value);
			cout << "INT " << value.asInteger << endl;
			break;
		case INST_DEFINE_DOUBLE:
			file.read(&byte, 1);
			value.type = TYPE_DOUBLE;
			value.asDouble = byte;
			push(value);
			cout << "DOUBLE " << value.asDouble << endl;
			break;
		case INST_DEFINE_CHARACTER:
			file.read(&byte, 1);
			value.type = TYPE_CHARACTER;
			value.asCharacter = byte;
			push(value);
			cout << "CHAR " << value.asCharacter << endl;
			break;

		case INST_DELETE:
			cout << "DELETE" << endl;
			pop();
			break;

		case INST_ADD:
			cout << "ADD" << endl;
			push(pop() + pop());
			break;
		case INST_SUBTRACT:
			cout << "SUBTRCT" << endl;
			push(pop() - pop());
			break;
		case INST_MULTIPLY:
			cout << "MULTIPLY" << endl;
			push(pop() * pop());
			break;
		case INST_DIVIDE:
			cout << "DIVIDE" << endl;
			push(pop() / pop());
			break;

		case INST_CONSOLE_OUT:
			cout << "OUTPUT: ";
			
			switch(peek().type){
			case TYPE_INTEGER:	 cout << peek().asInteger   << endl; break;
			case TYPE_DOUBLE:	 cout << peek().asDouble    << endl; break;
			case TYPE_CHARACTER: cout << peek().asCharacter << endl; break;
			}
			break;
		case INST_CONSOLE_IN:
			cout << "INPUT: ";

			cin >> value.asInteger;
			push(value);
			break;
		}
	}

	return ERROR_NONE;
}

#endif