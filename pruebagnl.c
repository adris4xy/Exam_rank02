
#include "get_next_line.h"

int		get_next_line(char **line)
{
	static char *stc;
	char		*tmp;
	int			len;
	char		buff[512];

	if (!line)
		return (-1);
	if (stc == NULL)
		stc = ft_strdup("");
	
}