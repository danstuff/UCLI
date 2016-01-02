#pragma once

#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

#include "main.h"
#include "virtual_machine.h"

Virtual_Machine *VM = NULL;

bool reportError(Error error, string file){
	string errmsg;

	switch(error){
	case ERROR_FILE_NF:
		errmsg = "[ERROR] File not found: " + file; break;
	case ERROR_SYNTAX:  
		errmsg = "[ERROR] Syntax error found in "  + file + ". Check your code!"; break;
	case ERROR_RUNTIME:
		errmsg = "[ERROR] Runtime error found in " + file + ". Check your code!"; break;
	default:
		return true;
	}

	cout << errmsg << endl;

	return false;
}

bool compile(){
	string filename;

	cout << "Please input the file you would like to compile into bytecode." << endl;
	cout << ">";
	cin >> filename;
		
	cout << endl;

	cout << "Opening file and compiling..." << endl << endl;

	Error error = VM->compileUCL(filename.c_str());	
	return reportError(error, filename);
}
bool run(bool debug = false){
	string filename;

	cout << "Please input the bytecode file you would like to execute." << endl;
	cout << ">";
	cin >> filename;

	cout << endl;

	cout << "Opening file and executing..." << endl << endl;

	Error error;
	
	if(debug)
		error = VM->processBytecodeDebug(filename.c_str());
	else 
		error = VM->processBytecode(filename.c_str());

	return reportError(error, filename);
}
bool help(){
	cout << "-Type 'compile' to compile a .txt or .ucl file written in UCL. This will generate a .ucr file." << endl;
	cout << "-Type 'run' to execute a precompiled .ucr file." << endl;
	cout << "-Type 'about' for more information about this program." << endl;
	cout << "-Any files you want to work with must be stored locally so UCLI can find them." << endl;

	return true;
}
bool about(){
	cout << "The Useless Coding Language Interpereter is a program written by Dan that \ncompiles and runs any files written in the Useless Coding Language.\n";
	cout << "The Useless Coding Language (UCL) was created by Dan in order to do absolutely \nnothing besides prove the fact that he can write a programming language.\n";
	cout << "Good on you, Dan. You're so goddamn special.\n";
	cout << "If you want to learn how to program in UCL, no documentation is available, so \nyou have to ask Dan. Oops. ";
	cout << "Check out some of the .ucl template files and you \nshould get the gist of it. " << endl;

	return true;
}

bool processInput(string input){
	displayTitle();

	if(input == "compile" || input == "c"){
		cout << "Command selected: COMPILE" << endl;
		return compile();
	}

	if(input == "run" || input == "r"){
		cout << "Command selected: RUN" << endl;
		return run();
	}

	if(input == "debugrun" || input == "dr"){
		cout << "Command selected: DEBUG RUN" << endl;
		return run();
	}

	if(input == "comprun" || input == "cr"){
		cout << "Command selected: COMPILE AND RUN" << endl;
		return compile() ? run() : false;
	}

	if(input == "help" || input == "h"){
		cout << "Command selected: HELP" << endl;
		return help(); 
	}

	if(input == "about" || input == "a"){
		cout << "Command selected: ABOUT" << endl;
		return about(); 
	}

	cout << "[ERROR] Command not found: " << input << endl;
	return false;
}

#endif