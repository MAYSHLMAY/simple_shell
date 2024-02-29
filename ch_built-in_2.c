#include "headers/Shell_Header.h"

/**
 * c_promp - returns true if shell is interactive mode
 * @form: struct address
 *
 * Return: 1 if c_promp mode, 0 otherwise
 */
int c_promp(form_t *form)
{
	return (isatty(STDIN_FILENO) && form->readfd <= 2);
}



