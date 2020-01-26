int is_upper(char c)
{
	return ((c <= 'Z') && (c >= 'A'));
}

int is_lower(char c)
{
	return ((c <= 'z') && (c >= 'a'));
}


char to_upper(char c)
{
	return ((char) c + ('A' - 'a'));
}


char to_lower(char c)
{
	return ((char) c - ('A' - 'a'));
}

/***
* Chagnes a lower letter to upper one and vise versa
* if its not a letter does nothing.
*
* @param c - the letter we change
* @out  - The letter after the change(if done.)
*/
char change_letter_case(char c)
{
	char return_c = c;

	if (is_lower(c))
		return_c = to_upper(c);
	else if (is_upper(c))
		return_c = to_lower(c);

	return return_c;
}