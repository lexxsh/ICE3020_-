#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

const int MAX_N = 100; // �ִ� ���ڿ� ���� ���� 
int kmpnext[MAX_N]; // KMP �˰��򿡼� ����ϴ� next �迭


//12201928 �̻���
// KMP �˰��򿡼� ����ϴ� next �迭 �ʱ�ȭ �Լ�
void InitNext(const char* p) {
    int i = 0, j = -1, M = strlen(p);
    kmpnext[0] = -1;
    while (i < M) {
        while (j >= 0 && p[i] != p[j]) {
            j = kmpnext[j];
        }
        i++;
        j++;
        if (p[i] == p[j]) {
            kmpnext[i] = kmpnext[j];
        }
        else {
            kmpnext[i] = j;
        }
    }
}

// KMP �˰����� ����Ͽ� ������ �־��� �ؽ�Ʈ���� ã�� �Լ�
int KMP(const char* p, const char* t) {
    int M = strlen(p); // ������ ����
    int N = strlen(t); // �ؽ�Ʈ�� ����
    InitNext(p); // next �迭 �ʱ�ȭ
    int i = 0, j = 0; // �ؽ�Ʈ �� ���� �ε���
    while (i < N) {
        while (j >= 0 && t[i] != p[j]) {
            j = kmpnext[j];
        }
        i++;
        j++;
        if (j == M) {
            return i - j; // ������ ��ġ�ϴ� ��ġ ��ȯ
        }
    }
    return -1; // ������ ã�� ���� ���
}

//12201928 �̻���
// Boyer-Moore �˰��򿡼� ����ϴ� skip �迭 �ʱ�ȭ �Լ�
void Initskip(const char* p, int skip[256]) {
    int M = strlen(p);
    for (int i = 0; i < 256; i++) skip[i] = M;
    for (int i = 0; i < M; i++) skip[p[i]] = M - i - 1;
}

// Boyer-Moore �˰����� ����Ͽ� ������ �־��� �ؽ�Ʈ���� ã�� �Լ�
int BoyerMoore(const char* p, const char* t) {
    int M = strlen(p); // ������ ����
    int N = strlen(t); // �ؽ�Ʈ�� ����
    int skip[256]; // �� ���ڿ� ���� �̵� �Ÿ��� �����ϴ� �迭

    Initskip(p, skip); // skip �迭 �ʱ�ȭ

    int i = M - 1;
    while (i < N) {
        int j = M - 1;
        while (t[i] == p[j]) {
            if (j == 0) return i; // ������ ��ġ�ϴ� ��ġ ��ȯ
            i--;
            j--;
        }
        i += max(skip[t[i]], M - j); // �̵� �Ÿ� ���
    }
    return -1; // ������ ã�� ���� ���
}

//12201928 �̻���
#define d 2
#define q 101
// Rabin-Karp �˰����� ����Ͽ� ������ �־��� �ؽ�Ʈ���� ã�� �Լ�
int RabinKarp(const char pattern[], const char text[]) {
    int m = strlen(pattern); // ������ ����
    int n = strlen(text); // �ؽ�Ʈ�� ����
    int i, j;
    int p = 0; // ������ �ؽð�
    int t = 0; // �ؽ�Ʈ�� �ؽð�
    int h = 1; // d^(m-1) ���� �����ϴ� ����

    // d^(m-1) ���� ����Ͽ� h�� ����.
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // ��ó�� �ܰ� : ���ϰ� �ؽ�Ʈ�� ù��° �κ� ���ڿ��� �ؽð��� �����.
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // ���ڿ� �˻� �ܰ�
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            // �ؽ� ���� ���ٸ� �� ���ڿ��� �ϳ��ϳ� ����.
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            // �ؽð��� ���� �� ���ڿ��� ���ٸ� ������ ã��.
            if (j == m)
                return i;
        }

        // ���� �κ� ���ڿ��� ���� �ؽð��� ����.
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            if (t < 0)  // �ؽð��� ������� ����� ������ ��.
                t = (t + q);
        }
    }
    return -1; // ������ ã�� ���� ���
}

//12201928 �̻���
// �߰ߵ� ���� ������ �����ϴ� ����ü
struct PatternFound {
    int lineNum; // �� ��ȣ
    int startIdx; // ���� �ε���
    string pattern; // �߰ߵ� ����
    string algorithm; // ���� �˰���
};
//12201928 �̻���
// �־��� ���Ͽ��� ������ ã�� �Լ�
void findPattern() {
    ifstream file("RFC2616_modified.txt"); // ���� ����

    const char* patterns[] = { "similar", "UA -----v", "HTTP/1.1", "\"A\"..\"Z\"", "[50]" }; // ã�� ���ϵ�
    const int patternsSize = sizeof(patterns) / sizeof(patterns[0]); // ������ ����

    string line; // ������ �� ���� �����ϴ� ����
    int lineNum = 0; // �� ��ȣ
    vector<PatternFound> foundPatterns; // �߰ߵ� ���ϵ��� �����ϴ� ����
    map<string, map<string, int>> patternCounts; // �� ������ � �˰������� �� �� �߰ߵǾ����� �����ϴ� ��

    // ������ �� ���� �о�� ������ ã��
    while (getline(file, line)) {
        lineNum++;
        for (int i = 0; i < patternsSize; i++) {
            int startPos = 0;
            // KMP �˰������� ������ ã��
            while (startPos < line.size()) {
                int foundPos = KMP(patterns[i], line.c_str() + startPos);
                if (foundPos != -1) {
                    foundPatterns.push_back({ lineNum, startPos + foundPos, patterns[i], "KMP" });
                    patternCounts[patterns[i]]["KMP"]++;
                    startPos += foundPos + 1;
                }
                else {
                    break;
                }
            }

            startPos = 0;
            // Boyer-Moore �˰������� ������ ã��
            while (startPos < line.size()) {
                int foundPos = BoyerMoore(patterns[i], line.c_str() + startPos);
                if (foundPos != -1) {
                    foundPatterns.push_back({ lineNum, startPos + foundPos, patterns[i], "BoyerMoore" });
                    patternCounts[patterns[i]]["BoyerMoore"]++;
                    startPos += foundPos + 1;
                }
                else {
                    break;
                }
            }

            startPos = 0;
            
            // Rabin-Karp �˰������� ������ ã��
            while (startPos < line.size()) {
                int foundPos = RabinKarp(patterns[i], line.c_str() + startPos);
                if (foundPos != -1) {
                    foundPatterns.push_back({ lineNum, startPos + foundPos, patterns[i], "RabinKarp" });
                    patternCounts[patterns[i]]["RabinKarp"]++;
                    startPos += foundPos + 1;
                }
                else {
                    break;
                }
            }
        }
    }
    // �˰���� ���� ���� �߰ߵ� ��ġ���� ������ �ڷᱸ��
    map<string, map<string, vector<pair<int, int>>>> summary;

    // �߰ߵ� ���ϵ��� ��� ������ �߰�
    for (const auto& fp : foundPatterns) {
        summary[fp.algorithm][fp.pattern].push_back({ fp.lineNum, fp.startIdx });
    }

    // ��� ���� ���
    for (const auto& alg : summary) {
        cout << alg.first << " �˰��� ���:" << endl; // �˰��� �̸�
        for (const auto& pat : alg.second) {
            cout << "  ���� \"" << pat.first << "\" �߰� ��ġ: ";
            for (const auto& pos : pat.second) {
                cout << "(line : " << pos.first << ", idx : " << pos.second << ") ";
            }
            cout << endl;
        }
        cout << endl;
    }
    for (const auto& entry : patternCounts) {
        for (const auto& subentry : entry.second) {
            cout << "���� \"" << entry.first << "\"��(��) " << subentry.first << " �˰������� " << subentry.second << "�� �߰ߵǾ����ϴ�." << endl;
        }
    }
    file.close(); // ���� �ݱ�
}
//12201928 �̻���
// �־��� ���ڿ��� ���Ϸ� �����ϴ� �Լ�
void generateTextFile(const char* filename, const char* text, int size) {
     ofstream file(filename); // ���� ����
    if (!file) {
         cerr << "������ ������ �� �����ϴ�." <<  endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << text; // ���ڿ��� ���Ͽ� ����
    }

    file.close(); // ���� �ݱ�
}

// �˰����� ������ �׽�Ʈ�ϴ� �Լ�
void test() {
    const char* pattern = "patternpattern"; // ã�� ����
    const int textSize = 1000000; // �ؽ�Ʈ ���� ũ�� (1,000,000 ����)

    const char* worstText = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"; // ������ �幰�� ��Ÿ���� �ؽ�Ʈ
    generateTextFile("test1.txt", worstText, textSize); // �ؽ�Ʈ ���� ����
    cout << "Test1 ��� �ؽ�Ʈ ������ �����Ǿ����ϴ�." << endl;

    const char* bestText = "patternpatternpatternpatternpatternpatternpattern"; // ������ ���� ��Ÿ���� �ؽ�Ʈ
    generateTextFile("test2.txt", bestText, textSize); // �ؽ�Ʈ ���� ����
    cout << "Test2 ��� �ؽ�Ʈ ������ �����Ǿ����ϴ�." << endl;

    const char* abcdefText = "ABCDEF"; // �ؽ�Ʈ
    const char* xyzPattern = "XYZ"; // ����
    generateTextFile("test3.txt", abcdefText, 1000000); // �ؽ�Ʈ ���� ���� (�ؽ�Ʈ�� "ABCDEF"�� 100�� �ݺ��Ͽ� ����)
    cout << "Test3 ��� �ؽ�Ʈ ������ �����Ǿ����ϴ�." << endl;
    //12201928 �̻���
    // �ؽ�Ʈ ���Ͽ��� ���� �˻� ���� �� �ð� ����

    // �־��� ��� �ؽ�Ʈ ���� ����
    ifstream worstFile("test1.txt");

    string line;
    vector<chrono::duration<double>> durationsKMP, durationsBoyerMoore, durationsRabinKarp;

    // KMP �˰��� �׽�Ʈ
    auto start = chrono::high_resolution_clock::now();
    while (getline(worstFile, line)) {
        KMP(pattern, line.c_str());
    }
    auto end = chrono::high_resolution_clock::now();
    durationsKMP.push_back(end - start);
    worstFile.clear();
    worstFile.seekg(0);

    // Boyer-Moore �˰��� �׽�Ʈ
    start = chrono::high_resolution_clock::now();
    while (getline(worstFile, line)) {
        BoyerMoore(pattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsBoyerMoore.push_back(end - start);
    worstFile.clear();
    worstFile.seekg(0);

    // Rabin-Karp �˰��� �׽�Ʈ
    start = chrono::high_resolution_clock::now();
    while (getline(worstFile, line)) {
        RabinKarp(pattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsRabinKarp.push_back(end - start);
    worstFile.clear();
    worstFile.seekg(0);

    worstFile.close();

    ifstream bestFile("test2.txt");

    // KMP �˰��� �׽�Ʈ
    start = chrono::high_resolution_clock::now();
    while (getline(bestFile, line)) {
        KMP(pattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsKMP.push_back(end - start);
    bestFile.clear();
    bestFile.seekg(0);

    // Boyer-Moore �˰��� �׽�Ʈ
    start = chrono::high_resolution_clock::now();
    while (getline(bestFile, line)) {
        BoyerMoore(pattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsBoyerMoore.push_back(end - start);
    bestFile.clear();
    bestFile.seekg(0);

    // Rabin-Karp �˰��� �׽�Ʈ
    start = chrono::high_resolution_clock::now();
    while (getline(bestFile, line)) {
        RabinKarp(pattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsRabinKarp.push_back(end - start);
    bestFile.clear();
    bestFile.seekg(0);

    bestFile.close();

    ifstream abcdefFile("test3.txt");

    // KMP �˰��� �׽�Ʈ
    start = chrono::high_resolution_clock::now();
    while (getline(abcdefFile, line)) {
        KMP(xyzPattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsKMP.push_back(end - start);
    abcdefFile.clear();
    abcdefFile.seekg(0);

    // Boyer-Moore �˰��� �׽�Ʈ
    start = chrono::high_resolution_clock::now();
    while (getline(abcdefFile, line)) {
        BoyerMoore(xyzPattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsBoyerMoore.push_back(end - start);
    abcdefFile.clear();
    abcdefFile.seekg(0);

    // Rabin-Karp �˰��� �׽�Ʈ
    start = chrono::high_resolution_clock::now();
    while (getline(abcdefFile, line)) {
        RabinKarp(xyzPattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsRabinKarp.push_back(end - start);
    abcdefFile.clear();
    abcdefFile.seekg(0);

    abcdefFile.close();

    // ��� ���
    cout << "KMP �˰��� ���� �ð� (test1): " << durationsKMP[0].count() << " ��" << endl;
    cout << "KMP �˰��� ���� �ð� (test2): " << durationsKMP[1].count() << " ��" << endl;
    cout << "KMP �˰��� ���� �ð� (test3): " << durationsKMP[2].count() << " ��" << endl;

    cout << "Boyer-Moore �˰��� ���� �ð� (test1): " << durationsBoyerMoore[0].count() << " ��" << endl;
    cout << "Boyer-Moore �˰��� ���� �ð� (test2): " << durationsBoyerMoore[1].count() << " ��" << endl;
    cout << "Boyer-Moore �˰��� ���� �ð� (test3): " << durationsBoyerMoore[2].count() << " ��" << endl;

    cout << "Rabin-Karp �˰��� ���� �ð� (test1): " << durationsRabinKarp[0].count() << " ��" << endl;
    cout << "Rabin-Karp �˰��� ���� �ð� (test2): " << durationsRabinKarp[1].count() << " ��" << endl;
    cout << "Rabin-Karp �˰��� ���� �ð� (test3): " << durationsRabinKarp[2].count() << " ��" << endl;
}

// ���� �Լ�
int main() { 
    
    cout << "--------------12201928 �̻���--------------------" << endl << endl;
    
    //findPattern();// ����ã��
    test(); // �˰��� ���� �׽�Ʈ ����
    return 0;
}
