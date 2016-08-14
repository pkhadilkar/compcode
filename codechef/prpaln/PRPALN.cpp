#include <iostream>
#define MAX_LEN (100000 + 1)
using namespace std;

bool inline is_palindrome_with_deletion(const string & str, int i, int j, int remaining_deletes)
{
	if (j <= i) {
		/* 
			remaining deletes could be either 0 or 1. If string
			is even length and remaining delete is 1, it can
			be converted into odd length palindrome by deleting
			middle letter. If string is odd and remaining deletes
			is 1, it can be converted into even length palindrome
			by deleting middle letter.
		*/
		return true;
	}

	if (str[i] == str[j])
	{
		return is_palindrome_with_deletion(str, i + 1, j - 1, remaining_deletes);
	} else if (remaining_deletes == 1) {
		return (is_palindrome_with_deletion(str, i + 1, j, remaining_deletes - 1) 
				|| is_palindrome_with_deletion(str, i, j - 1, remaining_deletes - 1));
	} else {
		return false;
	}
}

bool is_valid_palindrome(const string & str)
{
	int l = str.length();

	return is_palindrome_with_deletion(str, 0, l - 1, 1);
}

int main() {
	int T;
	ios_base::sync_with_stdio(false);

	cin >> T;

	for(int i = 0; i < T; ++i)
	{
		string str;
		cin >> str;

		cout << (is_valid_palindrome(str) ? "YES" : "NO") << "\n";
	}

	return 0;
}
