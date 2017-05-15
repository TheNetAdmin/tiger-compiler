#include "util.h"
#include "slp.h"
#include "prog1.h"

int main()
{
	/*
	int num;
	num = maxargs(prog2());
	printf("%d\n", num);
	*/
	A_stm s = prog2();
	interp(s);
	return 0;
}


