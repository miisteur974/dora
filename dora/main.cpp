#include <iostream> 
#include <Windows.h>
#include "console.h"


int main(int argc, char* argv[])
{

	directory* root = new directory("Disk0");
	system("cls");
	console t(root);
	t.start();
	system("pause");
	return 0;
}
