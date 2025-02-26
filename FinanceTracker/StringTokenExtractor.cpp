#include "StringTokenExtractor.h"

StringTokenExtractor::StringTokenExtractor(const MyString& str, const char delimiter): mCurrPos(str.GetCStr()), mDelimiter(delimiter)
{
}

void StringTokenExtractor::GetNextToken(MyString& token)
{
	if (!mCurrPos || *mCurrPos == '\0')
	{
		token.Clear();
		return;
	}

	const char* tokenStart = mCurrPos;

	while (*mCurrPos != '\0' && *mCurrPos != mDelimiter)
	{
		++mCurrPos;
	}

	token.Assign(tokenStart, mCurrPos - tokenStart);

	if (*mCurrPos == mDelimiter)
	{
		++mCurrPos;
	}
}

MyString StringTokenExtractor::GetRemaining()
{
	return { mCurrPos };
}
