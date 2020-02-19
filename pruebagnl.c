
#include "get_next_line.h"

int		get_next_line(char **line)
{
	static char	*stc;
	char		*tmp;
	int			len;
	char		buff[32];

	if (!line)
		return (-1);
	if (stc == NULL)
		stc = ft_strdup("");
	while (!(ft_strchr(stc)))
	{
		len = read(0, buff, 31);
		if (len < 0)
			return (-1);
		if (!len)
			break;
	}

}