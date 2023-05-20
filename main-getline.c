#include "shell.h"

int main()
{
	char *input;

	while (1)
	{
		printf("Enter a line: ");
			input = my_getline();


		if (input == NULL)
		{
			continue;
		}

		printf("You entered: %s\n", input);

		free(input);
	}

	return 0;
}
