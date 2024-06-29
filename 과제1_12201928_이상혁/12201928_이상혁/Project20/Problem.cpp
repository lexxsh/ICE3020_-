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

const int MAX_N = 100; // 최대 문자열 길이 설정 
int kmpnext[MAX_N]; // KMP 알고리즘에서 사용하는 next 배열


//12201928 이상혁
// KMP 알고리즘에서 사용하는 next 배열 초기화 함수
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

// KMP 알고리즘을 사용하여 패턴을 주어진 텍스트에서 찾는 함수
int KMP(const char* p, const char* t) {
    int M = strlen(p); // 패턴의 길이
    int N = strlen(t); // 텍스트의 길이
    InitNext(p); // next 배열 초기화
    int i = 0, j = 0; // 텍스트 및 패턴 인덱스
    while (i < N) {
        while (j >= 0 && t[i] != p[j]) {
            j = kmpnext[j];
        }
        i++;
        j++;
        if (j == M) {
            return i - j; // 패턴이 일치하는 위치 반환
        }
    }
    return -1; // 패턴을 찾지 못한 경우
}

//12201928 이상혁
// Boyer-Moore 알고리즘에서 사용하는 skip 배열 초기화 함수
void Initskip(const char* p, int skip[256]) {
    int M = strlen(p);
    for (int i = 0; i < 256; i++) skip[i] = M;
    for (int i = 0; i < M; i++) skip[p[i]] = M - i - 1;
}

// Boyer-Moore 알고리즘을 사용하여 패턴을 주어진 텍스트에서 찾는 함수
int BoyerMoore(const char* p, const char* t) {
    int M = strlen(p); // 패턴의 길이
    int N = strlen(t); // 텍스트의 길이
    int skip[256]; // 각 문자에 대한 이동 거리를 저장하는 배열

    Initskip(p, skip); // skip 배열 초기화

    int i = M - 1;
    while (i < N) {
        int j = M - 1;
        while (t[i] == p[j]) {
            if (j == 0) return i; // 패턴이 일치하는 위치 반환
            i--;
            j--;
        }
        i += max(skip[t[i]], M - j); // 이동 거리 계산
    }
    return -1; // 패턴을 찾지 못한 경우
}

//12201928 이상혁
#define d 2
#define q 101
// Rabin-Karp 알고리즘을 사용하여 패턴을 주어진 텍스트에서 찾는 함수
int RabinKarp(const char pattern[], const char text[]) {
    int m = strlen(pattern); // 패턴의 길이
    int n = strlen(text); // 텍스트의 길이
    int i, j;
    int p = 0; // 패턴의 해시값
    int t = 0; // 텍스트의 해시값
    int h = 1; // d^(m-1) 값을 저장하는 변수

    // d^(m-1) 값을 계산하여 h에 대입.
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // 전처리 단계 : 패턴과 텍스트의 첫번째 부분 문자열의 해시값을 계산함.
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // 문자열 검색 단계
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            // 해시 값이 같다면 두 문자열을 하나하나 비교함.
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            // 해시값이 같고 두 문자열이 같다면 패턴을 찾음.
            if (j == m)
                return i;
        }

        // 다음 부분 문자열에 대한 해시값을 구함.
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            if (t < 0)  // 해시값이 음수라면 양수로 변경해 줌.
                t = (t + q);
        }
    }
    return -1; // 패턴을 찾지 못한 경우
}

//12201928 이상혁
// 발견된 패턴 정보를 저장하는 구조체
struct PatternFound {
    int lineNum; // 줄 번호
    int startIdx; // 시작 인덱스
    string pattern; // 발견된 패턴
    string algorithm; // 사용된 알고리즘
};
//12201928 이상혁
// 주어진 파일에서 패턴을 찾는 함수
void findPattern() {
    ifstream file("RFC2616_modified.txt"); // 파일 열기

    const char* patterns[] = { "similar", "UA -----v", "HTTP/1.1", "\"A\"..\"Z\"", "[50]" }; // 찾을 패턴들
    const int patternsSize = sizeof(patterns) / sizeof(patterns[0]); // 패턴의 개수

    string line; // 파일의 한 줄을 저장하는 변수
    int lineNum = 0; // 줄 번호
    vector<PatternFound> foundPatterns; // 발견된 패턴들을 저장하는 벡터
    map<string, map<string, int>> patternCounts; // 각 패턴이 어떤 알고리즘으로 몇 번 발견되었는지 저장하는 맵

    // 파일의 각 줄을 읽어가며 패턴을 찾음
    while (getline(file, line)) {
        lineNum++;
        for (int i = 0; i < patternsSize; i++) {
            int startPos = 0;
            // KMP 알고리즘으로 패턴을 찾음
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
            // Boyer-Moore 알고리즘으로 패턴을 찾음
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
            
            // Rabin-Karp 알고리즘으로 패턴을 찾음
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
    // 알고리즘과 패턴 별로 발견된 위치들을 저장할 자료구조
    map<string, map<string, vector<pair<int, int>>>> summary;

    // 발견된 패턴들을 요약 정보에 추가
    for (const auto& fp : foundPatterns) {
        summary[fp.algorithm][fp.pattern].push_back({ fp.lineNum, fp.startIdx });
    }

    // 요약 정보 출력
    for (const auto& alg : summary) {
        cout << alg.first << " 알고리즘 결과:" << endl; // 알고리즘 이름
        for (const auto& pat : alg.second) {
            cout << "  패턴 \"" << pat.first << "\" 발견 위치: ";
            for (const auto& pos : pat.second) {
                cout << "(line : " << pos.first << ", idx : " << pos.second << ") ";
            }
            cout << endl;
        }
        cout << endl;
    }
    for (const auto& entry : patternCounts) {
        for (const auto& subentry : entry.second) {
            cout << "패턴 \"" << entry.first << "\"이(가) " << subentry.first << " 알고리즘으로 " << subentry.second << "번 발견되었습니다." << endl;
        }
    }
    file.close(); // 파일 닫기
}
//12201928 이상혁
// 주어진 문자열을 파일로 생성하는 함수
void generateTextFile(const char* filename, const char* text, int size) {
     ofstream file(filename); // 파일 열기
    if (!file) {
         cerr << "파일을 생성할 수 없습니다." <<  endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << text; // 문자열을 파일에 쓰기
    }

    file.close(); // 파일 닫기
}

// 알고리즘의 성능을 테스트하는 함수
void test() {
    const char* pattern = "patternpattern"; // 찾을 패턴
    const int textSize = 1000000; // 텍스트 파일 크기 (1,000,000 문자)

    const char* worstText = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"; // 패턴이 드물게 나타나는 텍스트
    generateTextFile("test1.txt", worstText, textSize); // 텍스트 파일 생성
    cout << "Test1 경우 텍스트 파일이 생성되었습니다." << endl;

    const char* bestText = "patternpatternpatternpatternpatternpatternpattern"; // 패턴이 자주 나타나는 텍스트
    generateTextFile("test2.txt", bestText, textSize); // 텍스트 파일 생성
    cout << "Test2 경우 텍스트 파일이 생성되었습니다." << endl;

    const char* abcdefText = "ABCDEF"; // 텍스트
    const char* xyzPattern = "XYZ"; // 패턴
    generateTextFile("test3.txt", abcdefText, 1000000); // 텍스트 파일 생성 (텍스트가 "ABCDEF"를 100번 반복하여 생성)
    cout << "Test3 경우 텍스트 파일이 생성되었습니다." << endl;
    //12201928 이상혁
    // 텍스트 파일에서 패턴 검색 수행 및 시간 측정

    // 최악의 경우 텍스트 파일 열기
    ifstream worstFile("test1.txt");

    string line;
    vector<chrono::duration<double>> durationsKMP, durationsBoyerMoore, durationsRabinKarp;

    // KMP 알고리즘 테스트
    auto start = chrono::high_resolution_clock::now();
    while (getline(worstFile, line)) {
        KMP(pattern, line.c_str());
    }
    auto end = chrono::high_resolution_clock::now();
    durationsKMP.push_back(end - start);
    worstFile.clear();
    worstFile.seekg(0);

    // Boyer-Moore 알고리즘 테스트
    start = chrono::high_resolution_clock::now();
    while (getline(worstFile, line)) {
        BoyerMoore(pattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsBoyerMoore.push_back(end - start);
    worstFile.clear();
    worstFile.seekg(0);

    // Rabin-Karp 알고리즘 테스트
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

    // KMP 알고리즘 테스트
    start = chrono::high_resolution_clock::now();
    while (getline(bestFile, line)) {
        KMP(pattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsKMP.push_back(end - start);
    bestFile.clear();
    bestFile.seekg(0);

    // Boyer-Moore 알고리즘 테스트
    start = chrono::high_resolution_clock::now();
    while (getline(bestFile, line)) {
        BoyerMoore(pattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsBoyerMoore.push_back(end - start);
    bestFile.clear();
    bestFile.seekg(0);

    // Rabin-Karp 알고리즘 테스트
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

    // KMP 알고리즘 테스트
    start = chrono::high_resolution_clock::now();
    while (getline(abcdefFile, line)) {
        KMP(xyzPattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsKMP.push_back(end - start);
    abcdefFile.clear();
    abcdefFile.seekg(0);

    // Boyer-Moore 알고리즘 테스트
    start = chrono::high_resolution_clock::now();
    while (getline(abcdefFile, line)) {
        BoyerMoore(xyzPattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsBoyerMoore.push_back(end - start);
    abcdefFile.clear();
    abcdefFile.seekg(0);

    // Rabin-Karp 알고리즘 테스트
    start = chrono::high_resolution_clock::now();
    while (getline(abcdefFile, line)) {
        RabinKarp(xyzPattern, line.c_str());
    }
    end = chrono::high_resolution_clock::now();
    durationsRabinKarp.push_back(end - start);
    abcdefFile.clear();
    abcdefFile.seekg(0);

    abcdefFile.close();

    // 결과 출력
    cout << "KMP 알고리즘 수행 시간 (test1): " << durationsKMP[0].count() << " 초" << endl;
    cout << "KMP 알고리즘 수행 시간 (test2): " << durationsKMP[1].count() << " 초" << endl;
    cout << "KMP 알고리즘 수행 시간 (test3): " << durationsKMP[2].count() << " 초" << endl;

    cout << "Boyer-Moore 알고리즘 수행 시간 (test1): " << durationsBoyerMoore[0].count() << " 초" << endl;
    cout << "Boyer-Moore 알고리즘 수행 시간 (test2): " << durationsBoyerMoore[1].count() << " 초" << endl;
    cout << "Boyer-Moore 알고리즘 수행 시간 (test3): " << durationsBoyerMoore[2].count() << " 초" << endl;

    cout << "Rabin-Karp 알고리즘 수행 시간 (test1): " << durationsRabinKarp[0].count() << " 초" << endl;
    cout << "Rabin-Karp 알고리즘 수행 시간 (test2): " << durationsRabinKarp[1].count() << " 초" << endl;
    cout << "Rabin-Karp 알고리즘 수행 시간 (test3): " << durationsRabinKarp[2].count() << " 초" << endl;
}

// 메인 함수
int main() { 
    
    cout << "--------------12201928 이상혁--------------------" << endl << endl;
    
    //findPattern();// 패턴찾기
    test(); // 알고리즘 성능 테스트 실행
    return 0;
}
