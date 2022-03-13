#include "DrawCallTest.h"

int main()
{
	DrawCallTest test;
	// range =  5 ~ 100. need multiple of 5. 
	test.Execute(TestArgs(DRAWER_MULTI_DRAW_ELEMENTS_INDIRECT, 50));
	test.Finalize();
	return 0;
}
