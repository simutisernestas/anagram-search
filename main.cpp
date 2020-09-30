#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <array>
#include <list>
#include <unordered_map>
#include "md5.h" // https://github.com/JieweiWei/md5

using namespace std;

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

#define NO_OF_CHARS 26

int pcount[NO_OF_CHARS] = { 0 };

bool areAnagram(const char* str1, const string& str2)
{
	// Create a count array and initialize all values as 0
	int count[NO_OF_CHARS] = { 0 };
	int i;

	// For each character in input strings, increment count in
	// the corresponding count array
	for (i = 0; str1[i] && str2[i]; i++)
	{
		count[str1[i]]++;
		count[str2[i]]--;
	}

	// If both strings are of different length. Removing this condition
	// will make the program fail for strings like "aaca" and "aca"
	if (str1[i] || str2[i])
		return false;

	// See if there is any non-zero value in count array
	for (i = 0; i < NO_OF_CHARS; i++)
		if (count[i])
			return false;
	return true;
}

int fc{};
int sc{};

bool couldBeAnagram(const string& str)
{
	int i;
	int copy[NO_OF_CHARS] = { 0 };
	string phrase = "poultryoutwitsants";
	for (char& c: phrase)
		copy[c - 'a']++;

//	for (i = 0; i < NO_OF_CHARS; i++)
//		cout << copy[i] << '\n';
////
//	if (sc == 2)
//		return 0;

	for (auto& c: str)
	{
		auto cc = static_cast<unsigned char>(c);
		cc -= 'a';
//		cout << "cc " << (int)cc << '\n';
		if (cc > 25 || cc < 0)
		{
//			cout << "cc " << (char)(cc + 'a') << '\n';
			fc++;
			return false;
		}
		else
		{
//			cout << "cc " << (char)(cc + 'a') << '\n';
		}
		copy[cc]--;
	}

//	for (i = 0; i < NO_OF_CHARS; i++)
//		cout << copy[i] << '\n';

//	cout << "copy 25 " << copy[25] << '\n';

	for (i = 0; i < NO_OF_CHARS; i++)
	{
		if (copy[i] < 0)
		{
			sc++;
			return false;
		}

	}

	return true;
}

// Function to check the small string
bool compare(string& s1, string& s2)
{
	return s1.size() < s2.size();
}

void checkHash(const string& w0, const string& w1, const string& w2, const string& w3)
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
		if ("665e5bcb0c20062fe8abaaf4628bb154" == hash.toStr())
			cout << "Solved hard! :) " << w << '\n';

	} while (std::next_permutation(s.begin(), s.end()));
}

void checkHash(const string& w0, const string& w1, const string& w2)
{
	vector<string> s{ w0, w1, w2 };

//	string w;
//	w += s[0];
//	w += ' ';
//	w += s[1];
//	w += ' ';
//	w += s[2];
//
//	MD5 hash(w);
//	if ("e4820b45d2277f3844eac66c903e84be" == hash.toStr())
//		cout << "Solved first " << w << '\n';
//	if ("23170acc097c24edb98fc5488ab033fe" == hash.toStr())
//		cout << "Solved second " << w << '\n';
//	if ("665e5bcb0c20062fe8abaaf4628bb154" == hash.toStr())
//		cout << "Solved last " << w << '\n';
//	return;

	std::sort(s.begin(), s.end());
	do
	{
		string w;
		w += s[0];
		w += ' ';
		w += s[1];
		w += ' ';
		w += s[2];

		MD5 hash(w);
		if ("e4820b45d2277f3844eac66c903e84be" == hash.toStr())
			cout << "Solved first " << w << '\n';
		if ("23170acc097c24edb98fc5488ab033fe" == hash.toStr())
			cout << "Solved second " << w << '\n';
		if ("665e5bcb0c20062fe8abaaf4628bb154" == hash.toStr())
			cout << "Solved last " << w << '\n';

	} while (std::next_permutation(s.begin(), s.end()));
}

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
			}
			s += to_string(arr[i]);
			s += ' ';
			sum += arr[i];
			++count;
		}
		if (p && sum == 18 && count == 3)
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
}

vector<array<int, 4>> pc = {
	{2, 2, 3, 11},
	{2, 2, 4, 10},
	{2, 2, 5, 9 },
	{2, 2, 6, 8 },
	{2, 2, 7, 7 },
	{2, 3, 3, 10},
	{2, 3, 4, 9 },
	{2, 3, 5, 8 },
	{2, 3, 6, 7 },
	{2, 4, 4, 8 },
	{2, 4, 5, 7 },
	{2, 4, 6, 6 },
	{2, 5, 5, 6 },
	{3, 3, 3, 9 },
	{3, 3, 4, 8 },
	{3, 3, 5, 7 },
	{3, 3, 6, 6 },
	{3, 4, 4, 7 },
	{3, 4, 5, 6 },
	{3, 5, 5, 5 },
	{4, 4, 4, 6 },
	{4, 4, 5, 5},
};

//const vector<array<int, 4>> pc = {
//	{2, 5 ,11 },
//	{2, 6 ,10 },
//	{2, 7 ,9 },
//	{2, 8 ,8 },
//	{3, 4 ,11 },
//	{3, 5 ,10 },
//	{3, 6 ,9 },
//	{3, 7 ,8 },
//	{4, 4 ,10 },
//	{4, 5 ,9 },
//	{4, 6 ,8 },
//	{4, 7 ,7 },
//	{5, 5 ,8 },
//	{5, 6 ,7 },
//	{6, 6 ,6},
//};

int main()
{
	unordered_map<int, vector<string>> m;

	int n = 18;
	findCombinations(n);

	string phrase = "poultryoutwitsants";
//	std::cout << phrase.length() << std::endl;

	auto l = phrase.length();

	for (char& c: phrase)
		pcount[c - 'a']++;

//	for (auto a: pcount)
//		cout << a << '\n';

//	cout << couldBeAnagram("youz");
//	return 0;

	ifstream file;
	file.open("/home/ernestas/Downloads/wordlist");
	if (!file.is_open())
	{
		cout << "can't open file\n";
		return 0;
	}

	string word;
	int count{};
	vector<string> wv;
	while (file >> word)
	{
		if (!couldBeAnagram(word))
		{
			count++;
		}
		else
		{
			if (word.length() > 1)
				wv.push_back(word);
//			cout << word << '\n';
		}
	}

//	cout << 102401 - count << '\n';
//	cout << fc << " " << sc;

	sort(wv.begin(), wv.end(), compare);

	list<int> lens;
	for (auto& w: wv)
	{
		m[w.length()].push_back(w);
		lens.push_back(w.length());
	}
	lens.unique();
	cout << '\n';
	for (auto& a: lens)
	{
		cout << a << '\n';
	}

	for (auto& comb: pc)
	{
		auto wv0 = m[comb[0]];
		auto wv1 = m[comb[1]];
		auto wv2 = m[comb[2]];
		auto wv3 = m[comb[3]];

		for (auto& w0: wv0)
		{
			for (auto& w1: wv1)
			{
				string whole1 = w0 + w1;
				if (whole1.length() > l) continue;
				if (!couldBeAnagram(whole1)) continue;

				for (auto& w2: wv2)
				{
					string whole2 = whole1 + w2;
					if (whole2.length() > l) continue;
					if (!couldBeAnagram(whole2)) continue;
//					checkHash(w0, w1, w2);

					for (auto& w3: wv3)
					{
						string whole3 = whole2 + w3;
						if (whole3.length() != l) continue;
						if (!couldBeAnagram(whole3)) continue;
						checkHash(w0, w1, w2, w3);
					}
				}
			}
		}
		cout << "a" << '\n';
	}

	return 0;

	for (auto& w0: wv)
	{
		for (auto& w1: wv)
		{
			string whole1 = w0 + w1;
			if (whole1.length() > l) continue;
			if (!couldBeAnagram(whole1)) continue;
			for (auto& w2: wv)
			{
				string whole2 = whole1 + w2;
				if (whole2.length() != l) continue;
				if (!couldBeAnagram(whole2)) continue;
				checkHash(w0, w1, w2);
				for (auto& w3: wv)
				{
					string whole3 = whole2 + w3;
					if (whole3.length() != l) continue;
					if (couldBeAnagram(whole3))
					{
						//cout << whole3 << '\n';
						checkHash(w0, w1, w2, w3);
					}
				}
			}
		}
//		cout << w0 << '\n';
	}

	return 0;

	auto t1 = std::chrono::high_resolution_clock::now();
	for (long i = 0; i < 1874516337; ++i)
	{
		count++;
	}
	auto t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();

	std::cout << duration;

	return 0;
}
