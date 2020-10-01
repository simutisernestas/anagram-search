#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <array>
#include <list>
#include <unordered_map>
#include "md5.h" // https://github.com/JieweiWei/md5

#define NO_OF_CHARS 26
static int phrase_char_count[NO_OF_CHARS] = { 0 };

using namespace std;

const string hash3 = "665e5bcb0c20062fe8abaaf4628bb154";

bool couldBeAnagram(const string& str)
{
	int copy[NO_OF_CHARS];
	memcpy(copy, phrase_char_count, sizeof(copy));

	for (auto& c: str)
	{
		auto cc = static_cast<unsigned char>(c);
		cc -= 'a';
		if (cc > 25 || cc < 0) // not in english alphabet
			return false;
		copy[cc]--;
	}

	for (int i = 0; i < NO_OF_CHARS; i++)
		if (copy[i] < 0)
			return false;

	return true;
}

// Function to check the small string
bool compare(string& s1, string& s2)
{
	return s1.size() < s2.size();
}

bool checkHash(const string& w0, const string& w1, const string& w2, const string& w3)
{
	vector<string> s{ w0, w1, w2, w3 };
	std::sort(s.begin(), s.end());
	do
	{
		string w;
		w += s[0];
		w += ' ';
		w += s[1];
		w += ' ';
		w += s[2];
		w += ' ';
		w += s[3];

		MD5 hash(w);
		if (hash3 == hash.toStr())
		{
			cout << "Solved hard! :) " << w << '\n';
			return true;
		}

	} while (std::next_permutation(s.begin(), s.end()));

	return false;
}

// possible word lengths in right subset of wordlist
array<int, 10> allowed{ 2,
						3,
						4,
						5,
						6,
						7,
						8,
						9,
						10,
						11 };

/*    arr - array to store the combination
    index - next location in array
    num - given number
    reducedNum - reduced number */
void findCombinationsUtil(int arr[], int index,
	int num, int reducedNum)
{
	// Base condition
	if (reducedNum < 0)
		return;

	// If combination is found, print it
	if (reducedNum == 0)
	{
		string s;
		bool p{ true };
		int sum{};
		int count{};
		for (int i = 0; i < index; i++)
		{
			if (std::find(allowed.begin(), allowed.end(), arr[i]) == allowed.end())
			{
				p = false;
				break;
			}
			s += to_string(arr[i]);
			s += ' ';
			sum += arr[i];
			++count;
		}
		if (p && sum == 18 && count == 4)
			cout << s << endl;
		return;
	}

	// Find the previous number stored in arr[]
	// It helps in maintaining increasing order
	int prev = (index == 0) ? 1 : arr[index - 1];

	// note loop starts from previous number
	// i.e. at array location index - 1
	for (int k = prev; k <= num; k++)
	{
		// next element of array is k
		arr[index] = k;

		// call recursively with reduced number
		findCombinationsUtil(arr, index + 1, num,
			reducedNum - k);
	}
}

/* Function to find out all combinations of
   positive numbers that add upto given number.
   It uses findCombinationsUtil() */
void findCombinations(int n)
{
	// array to store the combinations
	// It can contain max n elements
	int arr[n];

	//find all combinations
	findCombinationsUtil(arr, 0, n, n);

	cout << '\n';
}

vector<array<int, 4>> phrase_lenght_comb_table = {
	{ 2, 2, 3, 11 },
	{ 2, 2, 4, 10 },
	{ 2, 2, 5, 9 },
	{ 2, 2, 6, 8 },
	{ 2, 2, 7, 7 },
	{ 2, 3, 3, 10 },
	{ 2, 3, 4, 9 },
	{ 2, 3, 5, 8 },
	{ 2, 3, 6, 7 },
	{ 2, 4, 4, 8 },
	{ 2, 4, 5, 7 },
	{ 2, 4, 6, 6 },
	{ 2, 5, 5, 6 },
	{ 3, 3, 3, 9 },
	{ 3, 3, 4, 8 },
	{ 3, 3, 5, 7 },
	{ 3, 3, 6, 6 },
	{ 3, 4, 4, 7 },
	{ 3, 4, 5, 6 },
	{ 3, 5, 5, 5 },
	{ 4, 4, 4, 6 },
	{ 4, 4, 5, 5 },
};

int main()
{
	auto t1 = std::chrono::high_resolution_clock::now();

	string phrase = "poultryoutwitsants";
	auto len = phrase.length();

	// all possible combination satisfying the condition,
	// that 4 words has same length as the phrase, output
	// is stored in phrase_lenght_comb_table :)
	// used only to compute phrase_lenght_comb_table !
	findCombinations(len);

	// build table of char for anagram condition checking
	for (char& c: phrase)
		phrase_char_count[c - 'a']++;

	ifstream file;
	file.open("/home/ernestas/Downloads/wordlist");
	if (!file.is_open())
	{
		cout << "can't open file\n";
		return 0;
	}

	string word;
	vector<string> wordlist;
	while (file >> word)
	{
		if (!couldBeAnagram(word))
		{
			continue;
		}

		wordlist.push_back(word);
	}

	sort(wordlist.begin(), wordlist.end(), compare);

	// words by length lookup table
	unordered_map<int, vector<string>> m;
	for (auto& w: wordlist)
		m[w.length()].push_back(w);

	for (auto& comb: phrase_lenght_comb_table)
	{
		auto wordlist0 = m[comb[0]];
		auto wordlist1 = m[comb[1]];
		auto wordlist2 = m[comb[2]];
		auto wordlist3 = m[comb[3]];

		for (auto& w0: wordlist0)
		{
			for (auto& w1: wordlist1)
			{
				string whole1 = w0 + w1;
				if (whole1.length() > len) continue;
				if (!couldBeAnagram(whole1)) continue;

				for (auto& w2: wordlist2)
				{
					string whole2 = whole1 + w2;
					if (whole2.length() > len) continue;
					if (!couldBeAnagram(whole2)) continue;

					for (auto& w3: wordlist3)
					{
						string whole3 = whole2 + w3;
						if (whole3.length() != len) continue;
						if (!couldBeAnagram(whole3)) continue;
						bool found = checkHash(w0, w1, w2, w3);
						if (found)
						{
							auto t2 = std::chrono::high_resolution_clock::now();
							auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
							std::cout << "Duration: " << duration << 's';
							return 0;
						}
					}
				}
			}
		}
		cout << "Cycle" << '\n';
	}

	return 0;
}
