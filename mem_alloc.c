#include "s_shell.h"

/**
 * mem_copy - copies info btn void pointers
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: new pointer size.
 *
 * Return: void
 */
void mem_copy(void *newptr, const void *ptr, unsigned int size)
{
	char *init_ptr = (char *)ptr;
	char *fin_ptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		fin_ptr[i] = init_ptr[i];
}

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer tp previously allocated space
 * @old_size: old size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new allaocated space
 *
 * Return: ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		mem_copy(newptr, ptr, new_size);
	else
		mem_copy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdptr - reallocate memoryof dpouble pointer(dp)
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size of the allocated space of ptr
 * @new_size: new size of the new memory block
 *
 * Return: ptr
 */
char **_reallocdptr(char **ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char **newptr;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for  (i = 0; i < old_size; i++)
	{
		newptr[i] = ptr[i];
	}
	free(ptr);
	return (newptr);
}
