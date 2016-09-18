#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char * hex = "0xa";
	char * hexTwo = "0xb";
	char * hexThree = "10";
	long int ans;

	ans = strtol(hex, NULL, 16);
	ans = ans + strtol(hexThree, NULL, 10);
	printf("The answer is %ld\n", ans);

	return 0;
}