#include <iostream>
#include "DrawCallTest.h"
#include <iostream>
#include <string>
#include <functional>
using namespace std;

int main()
{
	DrawCallTest test;
	test.Execute(TestArgs(DRAWER_DRAW_ELEMENTS_INDIRECT, 100));
	test.Finalize();
	return 0;
}
