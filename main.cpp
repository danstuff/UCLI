#include "main.h"
#include "process_input.h"

int main(){
	string input = "";

	SetConsoleTitle("Useless Coding Language Interpreter");

	VM = new Virtual_Machine();

	while(true){
		displayTitle();
		
		cout << "Please input a command. Type 'help' for assistance." << endl;

		cout << ">";
		cin >> input;

		cout << endl;

		if(processInput(input))
			cout << endl << "Process SUCCEEDED." << endl << endl;
		else
			cout << endl << "Process FAILED." << endl << endl;

		Sleep(500);

		system("pause");
		
		input = "";
	}

	delete VM;

	return 0;
}