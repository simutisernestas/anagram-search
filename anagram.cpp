#include "md5.h"
#include <bits/stdc++.h>
using namespace std;

class Timer
{
public:
    clock_t start;

    Timer()
    {
        start = clock();
    }

    void timePassed()
    {
        double duration;
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "\nTime passed: " << duration << '\n';
    }

    ~Timer()
    {
        double duration;
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "\nTotal duration: " << duration << '\n';
    }
};

unsigned long hashStr(const std::string &str)
{
    unsigned long hash = 0;
    for (size_t i = 0; i < str.size(); ++i)
        hash += (unsigned char) str[i];
    return hash;
}

int main()
{
    Timer t{};

    std::string phrase{"poultryoutwitsants"};
    string hash0 = "e4820b45d2277f3844eac66c903e84be";
    string hash1 = "23170acc097c24edb98fc5488ab033fe";
    string hash2 = "665e5bcb0c20062fe8abaaf4628bb154";
    std::unordered_map<int, vector<std::string>> hash_map;
    bool procced;

    unsigned long phash = hashStr(phrase);
    std::map<char, int> letter_map;
    for (char &c: phrase)
        letter_map[c]++;

    std::ifstream file("/home/ernestas/CLionProjects/sandbox/wordlist");
    if (!file.is_open())
        return 0;

    std::map<char, int> line_map;
    unsigned long hash;
    std::string line;
    while (getline(file, line)) {

        procced = true;
        line_map.clear();
        for (char &c: line) {
            if (!letter_map.count(c)) {
                procced = false;
                break;
            }
            line_map[c]++;
        }
        if (!procced)
            continue;

        procced = true;
        for (char &c: line) {
            if (letter_map[c] < line_map[c]) {
                procced = false;
                break;
            }
        }
        if (!procced)
            continue;

        hash = hashStr(line);
        if (hash_map.count(hash) == 0) {
            std::vector<std::string> v;
            v.push_back(line);
            hash_map[hash] = v;
        } else {
            (*&hash_map[hash]).push_back(line);
        }
    }
    file.close();

    for (auto &h0: hash_map) {
        for (auto &h1: hash_map) {
            if (h0.first + h1.first > phash)
                continue;

            for (auto &h2: hash_map) {
                if (h0.first + h1.first + h2.first != phash)
                    continue;

                for (auto &s0: h0.second) {
                    for (auto &s1: h1.second) {
                        for (auto &s2: h2.second) {
                            std::string p = s0 + ' ' + s1 + ' ' + s2;
                            std::string pphash = md5(p);
                            if (pphash == hash0) {
                                cout << hash0 << ": " << p;
                                t.timePassed();
                            }
                            if (pphash == hash1) {
                                cout << hash1 << ": " << p;
                                t.timePassed();
                            }
//                            if (pphash == hash2)
//                                cout << hash2 << ": " << p << '\n';
                        }
                    }
                }
            }
        }
    }

    return 0;
}
