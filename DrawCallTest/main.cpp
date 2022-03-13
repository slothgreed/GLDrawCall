#include "DrawCallTest.h"

int main()
{
	DrawCallTest test;
	test.Execute(TestArgs(DRAWER_DRAW_ELEMENTS_INDIRECT, 10));
	test.Finalize();
	return 0;
}
