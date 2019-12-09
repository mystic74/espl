int cmpstr(const char *s1, const char *s2)
{
	unsigned index = 0;
	char a = (*(s1+index));
	char b = (*(s2+index));
	
	while((a) && (b))
	{
		if (a > b)
			return 1;
		if (b > a)
			return 2;
		index++;

		a = (*(s1+index));
		b = (*(s2+index));
	}


	if (a > b)
		return 1;
	if (b > a)
		return 2;

	return 0;
}
