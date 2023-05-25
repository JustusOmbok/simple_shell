#include "shell.h"

/**
 * bfree - func that frees a pointer and NULLs the address
 * @ptr: the address of the pointer to free
 *
 * Return: 1 if freed, or 0 otherwise.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
