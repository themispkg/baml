#include "baml.h"

char	is_quote(char c)
{
	if (c == '\'' || c == '\"' || c == '`')
		return (1);
	return (0);
}
