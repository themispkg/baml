#pragma once
# define ENTRYTOKEN "->"
# define HEADERTOKEN ';'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * "valid_arg" takes the first argument and returns output format string list
 * if the argument is valid. returns NULL if the argument is invalid.
 * "valid_token" takes the line read from the file and check whether it has a 
 * valid entry token, returns index position located after the token. returns
 * zero if the argument is invalid.
 * "pheader" takes the line "hstr" comprising a valid token and prints header 
 * output according to the "format"; "hopen" is passed 0 when there is no 
 * previous header in the file.
 * "pentry" takes the line "hstr" comprising a valid token and prints entry
 * output according to the "format"; "hopen" is passed 1 when there is no
 * previous entry in the header, it is set to 2 when an entry is inserted.
 * "pitem" takes the target string and prints it by adding '\' for any quote
 * character and trimming the end of it.
 * "dstr" takes a "base" string and concatenates "tail" by dynamically
 * allocating memory. this function is used to store a complete line from
 * the file.
 */

/*
 * Checks valid arguments for baml
 */
char	**valid_arg(char *arg)
{
	char	**format;

	format = (char **) malloc(sizeof(char *) * 4);

	if (strncmp("--", arg, 2) || !strcmp("--bash", arg))
	{
		format[0] = strdup("=(");
		format[1] = strdup(" ");
		format[2] = strdup("\'");
		format[3] = strdup(")");
		return (format);
	}
	else if (!strcmp("--python", arg) || !strcmp("--ruby", arg))
	{
		format[0] = strdup(" = [");
		format[1] = strdup(", ");
		format[2] = strdup("\"");
		format[3] = strdup("]");
		return (format);
	}
	else
	{
		free(format);
		return (NULL);
	}

}

/*
 * Checks valid tokens like space and tab
 */
size_t	valid_token(char *store)
{
	size_t offset = 0;

	while (store[offset] == ' ' || store[offset] == '\t')
		offset++;
	if (!strncmp(&store[offset], ENTRYTOKEN, 2))
		return (offset + 2);
	return (0);
}

/*
 * Check items for any bugs in parsing (in 69. line)
 */
void	pitem(char *istr)
{

	// Required definitions
	size_t			isize = strlen(istr);
	size_t			scan = 0;
	size_t			checkp = 0;
	size_t			trimmer = 0;
	unsigned char	memory = 0;

	// If size of istr greater than scan -> loop
	while (scan < isize)
	{
		// If 0 numbered member of istr greater than 32 -> trimmer equals to scan
		if (istr[scan] > 32 )
			trimmer = scan;
		// If scan numbered member of istr equals to \' or \" or ' -->
		if (istr[scan] == '\'' || istr[scan] == '\"' || istr[scan] == '`')
		{
			// Memory equals scan numbered member of istr
			memory = istr[scan];
			// Scan numbered member of istr is equals to 0
			istr[scan] = 0;
			// Print result
			printf("%s\\%c", &istr[checkp], memory);
			// Scan numbered member of istr to memory
			istr[scan] = memory;
			// Increase and equals to checkp(0)
			checkp = ++scan;
			continue ;
		}
		scan++; // Increase scan for while
	}
	istr[trimmer + 1]  = 0;
	if (memory == 0)
		printf("%s", istr);
	else if (scan != checkp)
		printf("%s", &istr[checkp]);
}

// Check headers for tabs and spaces
void	pheader(char *hstr, char **format, char *hopen)
{
	size_t	scan;

	while (*hstr && (*hstr == ' ' || *hstr == '\t'))
		hstr++;
	scan = 0;
	while (hstr[scan])
	{
		if (hstr[scan] == ';')
		{
			hstr[scan] = 0;
			break ;
		}
		scan++;
	}
	if (*hopen)
		printf("%s\n", format[3]);
	pitem(hstr);
	printf("%s", format[0]);
	*hopen = 1;
}

// Check entry ```->hey``` with spaces and tabs again
void	pentry(char *estr, char **format, char *hopen)
{
	size_t	scan;

	while (*estr && (*estr == ' ' || *estr == '\t'))
		estr++;
	scan = 0;
	while (estr[scan])
	{
		if (estr[scan] == '\n')
		{
			estr[scan] = 0;
			break ;
		}
		scan++;
	}
	if(*hopen == 2)
		printf("%s", format[1]);
	else
		*hopen = 2;
	printf("%s", format[2]);
	pitem(estr);
	printf("%s", format[2]);
}

// Change some things with strings
size_t	dstr(char *base, char *tail)
{
	size_t	blen = strlen(base);
	size_t	tlen = strlen(tail);

	base = realloc(base, sizeof(char) * (blen + tlen + 1)); // Allocate memory
	for (size_t i = blen; i < blen + tlen; i++)
	{
		base[i] = *tail;
		tail++;
	}
	base[blen + tlen] = 0;
	return (blen + tlen);
}
