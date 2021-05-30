int
str2long(char *str, long *lp)
{
	long		result = 0;
	long		sign = 1;
	while ((*str != '\0') && (isspace(*str)))
		str++;
	if (*str == '-') {
		str++;
		sign = -1;
	} else if (*str == '+') {
		str++;
	}
	if (!*str)
		return 1;
	while (isdigit(*str)) {
		long		increment = sign * convertDigit(*str);
		if ((sign == 1) && (result > (LONG_MAX - increment) / 10))
			return 3;
		if ((sign == -1) && (result < (LONG_MIN - increment) / 10))
			return 3;
		result = result * 10 + increment;
		str++;
	}
	if (*str != '\0')
		return 2;
	*lp = result;
	return 0;
}
