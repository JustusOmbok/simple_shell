#include "shell.h"

/**
 * input_buf - buffers for chained commands
 * @info: struct parameter
 * @buf: buffer address
 * @len: len variable address
 *
 * Return: number of bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t v = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		v = getline(buf, &len_p, stdin);
#else
		v = _getline(info, buf, &len_p);
#endif
		if (v > 0)
		{
			if ((*buf)[v - 1] == '\n')
			{
				(*buf)[v - 1] = '\0'; /* remove trailing newline */
				v--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = v;
				info->cmd_buf = buf;
			}
		}
	}
	return (v);
}

/**
 * get_input - gets a line without the newline
 * @info: struct parameter
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t k, l, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		l = k; /* init new iterator to current buf position */
		p = buf + k; /* get pointer for return */

		check_chain(info, buf, &l, k, len);
		while (l < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &l))
				break;
			l++;
		}

		k = l + 1; /* increments past nulled ';'' */
		if (k >= len) /* end of buffer? */
		{
			k = len = 0; /* resets position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* passes back pointer to current command position */
		return (_strlen(p)); /* returns length of current command */
	}

	*buf_p = buf; /* if not a chain, passes back buffer from _getline() */
	return (r); /* returns length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: struct parameter
 * @buf: the buffer
 * @i: the size
 *
 * Return: v
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t v = 0;

	if (*i)
		return (0);
	v = read(info->readfd, buf, READ_BUF_SIZE);
	if (v >= 0)
		*i = v;
	return (v);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: struct parameter
 * @ptr: pointer address to buffer, preallocated or NULL
 * @length: size of preallocated pointer buffer if not NULL
 *
 * Return: z
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, z = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		z = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, z, z ? z + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (z)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	z += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = z;
	*ptr = p;
	return (z);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
