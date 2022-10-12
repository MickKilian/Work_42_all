#include <unistd.h>

char	*skip_spaces(char *s)
{
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return s;
}

char	*skip_one_word(char*s)
{
	s = skip_spaces(s);
	while (*s && *s != ' ' && *s != '\t')
		s++;
	return s;
}

char	*print_one_word(char*s)
{
	s = skip_spaces(s);
	while (*s && *s != ' ' && *s != '\t')
		write(1, s++, 1);
	return s;
}

int main(int argc, char**argv)
{
	char *start = argv[1];
	char *pos = start;
	
	pos = skip_one_word(pos);
	while(*pos)
	{
		pos = print_one_word(pos);
		pos = skip_spaces(pos);
		write(1, " ", 1);
	}
	print_one_word(start);
}
