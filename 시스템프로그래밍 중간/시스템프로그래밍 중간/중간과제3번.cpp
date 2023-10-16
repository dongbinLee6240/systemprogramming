#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <sys/stat.h>
#include <ctime>
using namespace std;

struct userInfo
{
    char id[20];
    char name[20];
    int time;
    int score;
};

void getfiletime(const char* filename)
{
    struct _stat filestat;

    if (_stat(filename, &filestat) != 0)
    {
        cout << "파일 정보를 가져오는데 실패" << endl;
        return;
    }

    cout << "생성시간: " << ctime(&filestat.st_ctime);

    cout << "접근시간: " << ctime(&filestat.st_atime);

    cout << "최종 수정시간: " << ctime(&filestat.st_mtime);
}

int main()
{
    string user = getenv("COMPUTERNAME");
    ofstream fout;
    userInfo users[2];

    fout.open("userinform.dat");

    if (!fout)
    {
        cerr << "파일 열기 실패" << endl;
        return 1;
    }

    // 사용자 정보 입력받아 파일에 쓰기
    for (int i = 0; i < 2; ++i)
    {
        cout << endl;

        cout << "사용자 #" << i + 1 << " 정보 입력:" << endl;

        cout << "id: " + user << '\n';

        cout << "이름: ";
        cin >> users[i].name;

        cout << "게임 시간: ";
        cin >> users[i].time;

        cout << "게임 실행 점수: ";
        cin >> users[i].score;

        // 파일에 쓰기
        fout << users[i].id << " " << users[i].name << " " << users[i].time << " " << users[i].score << endl;
        
        fout.close(); // 파일 닫기
        getfiletime("userinform.dat");
        fout.open("userinform.dat", ios::app);
    }

    fout.close();

    ifstream fin("userinform.dat");

    for (int i = 0; i < 2; ++i)
    {
        fin >> users[i].id >> users[i].name >> users[i].time >> users[i].score;
        cout << endl; //한칸 뛰기
        cout << "-----------------------------------" << endl;
        cout << "사용자 #" << i + 1 << " 정보:" << endl;
        cout << "ID: " + user << endl;
        cout << "이름: " << users[i].name << endl;
        cout << "게임 시간: " << users[i].time << endl;
        cout << "게임 실행 점수: " << users[i].score << endl;
        getfiletime("userinform.dat");
        cout << "-----------------------------------" << endl;
    }

    fin.close();

    return 0;
}
