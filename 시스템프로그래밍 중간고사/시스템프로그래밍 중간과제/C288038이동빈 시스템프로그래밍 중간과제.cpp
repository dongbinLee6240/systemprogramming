#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<sys/stat.h>
#include<ctime>
using namespace std;

void GetComputerName()
{
    cout << "ComputerName: " << getenv("COMPUTERNAME") << endl;
}

struct UserInfo
{
    char id[20];
    char name[20];
    int time;
    int score;
};

void DisplayFileTime(const char* filename)
{
    struct _stat filestat;

    if (_stat(filename, &filestat) != 0)
    {
        throw string("getfiletime_error");
    }

    cout << "생성시간: " << ctime(&filestat.st_ctime);
    cout << "접근시간: " << ctime(&filestat.st_atime);
    cout << "최종 수정시간: " << ctime(&filestat.st_mtime);
}

void GetFileTime(const char* filename, ofstream& outfile)
{
    struct _stat filestat;

    if (_stat(filename, &filestat) != 0)
    {
        throw string("getfiletime_error");
    }

    outfile << "생성시간: " << ctime(&filestat.st_ctime);
    outfile << "접근시간: " << ctime(&filestat.st_atime);
    outfile << "최종 수정시간: " << ctime(&filestat.st_mtime);
}

int main()
{
     GetComputerName();
    
     // try문
    try
    {
        string user = getenv("COMPUTERNAME");
        ofstream fout;
        UserInfo users[10];

        fout.open("userinform.dat");

        if (!fout)
        {
            throw string("userinform_error");
        }

        // 사용자 정보 입력받아 파일에 쓰기
        for (int i = 0; i < 10; ++i)
        {
            cout << endl;

            cout << "사용자 #" << i + 1 << " 정보 입력:" << endl;

            cout << "id: " + user << '\n';

            cout << "이름: ";
            cin >> users[i].name;

            char* ptr = strpbrk(users[i].name, "!@#$%^&*()-+"); //name에 특수 문자 있을 경우
            if (ptr != NULL) 
            {

                throw string("name_error");
            }
          
            cout << "게임 시간: ";
            cin >> users[i].time;
            if (users[i].time < 0)  //시간이 음수일때
            {
                throw string("time_error");
            }

            cout << "게임 실행 점수: ";
            cin >> users[i].score;
            if (users[i].score < 0)  //점수가 음수일때
            {
                throw string("score_error");
            }
            // 파일에 쓰기
            fout << users[i].id << " " << users[i].name << " " << users[i].time << " " << users[i].score << endl;

            fout.close(); // 파일 닫기
            DisplayFileTime("userinform.dat");
            GetFileTime("userinform.dat", fout);
            fout.open("userinform.dat", ios::app); //파일 다시 열기
        }

        fout.close();

        // userinform.dat파일의 getfiletime을 fileMgOut 에 넣기
        ofstream fileMgOut("FileMg.tax");

        if (!fileMgOut)
        {
            throw string("fileMgOut_error");
        }

        GetFileTime("userinform.dat", fileMgOut);

        fileMgOut.close();

        ifstream fin("userinform.dat");

        for (int i = 0; i < 10; ++i)
        {
            fin >> users[i].id >> users[i].name >> users[i].time >> users[i].score;
            cout << endl; // 한 칸 뛰기
            cout << "-----------------------------------" << endl;
            cout << "사용자 #" << i + 1 << " 정보:" << endl;
            cout << "ID: " + user << endl;
            cout << "이름: " << users[i].name << endl;
            cout << "게임 시간: " << users[i].time << endl;
            cout << "게임 실행 점수: " << users[i].score << endl;
            DisplayFileTime("userinform.dat");
            GetFileTime("userinform.dat", fileMgOut);
            cout << "-----------------------------------" << endl;
        }

        fin.close();

        return 0;
    }
    // catch문
    catch (const string& error)
    {
        if (error == "userinform_error")
        {
            cout << "userinform.dat 파일 열기 실패" << endl;
        }
        else if (error == "getfiletime_error")
        {
            cout << "파일정보 가져오기 실패" << endl;
        }
        else if (error == "fileMgOut_error")
        {
            cout << "fileMgOut 파일 열기 실패" << endl;
        }
        else if (error == "time_error")
        {
            cout << "잘못된 시간표기입니다." << endl;
        }
        else if (error == "score_error")
        {
            cout << "잘못된 점수표기입니다." << endl;
        }
        else if (error == "name_error")
        {
            cout << "이름에 특수문자가 있습니다." << endl;
        }
        else
        {
            cout << "알 수 없는 오류: " << error << endl;
        }
    }
    
}
