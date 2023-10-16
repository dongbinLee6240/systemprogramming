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
        cout << "���� ������ �������µ� ����" << endl;
        return;
    }

    cout << "�����ð�: " << ctime(&filestat.st_ctime);

    cout << "���ٽð�: " << ctime(&filestat.st_atime);

    cout << "���� �����ð�: " << ctime(&filestat.st_mtime);
}

int main()
{
    string user = getenv("COMPUTERNAME");
    ofstream fout;
    userInfo users[2];

    fout.open("userinform.dat");

    if (!fout)
    {
        cerr << "���� ���� ����" << endl;
        return 1;
    }

    // ����� ���� �Է¹޾� ���Ͽ� ����
    for (int i = 0; i < 2; ++i)
    {
        cout << endl;

        cout << "����� #" << i + 1 << " ���� �Է�:" << endl;

        cout << "id: " + user << '\n';

        cout << "�̸�: ";
        cin >> users[i].name;

        cout << "���� �ð�: ";
        cin >> users[i].time;

        cout << "���� ���� ����: ";
        cin >> users[i].score;

        // ���Ͽ� ����
        fout << users[i].id << " " << users[i].name << " " << users[i].time << " " << users[i].score << endl;
        
        fout.close(); // ���� �ݱ�
        getfiletime("userinform.dat");
        fout.open("userinform.dat", ios::app);
    }

    fout.close();

    ifstream fin("userinform.dat");

    for (int i = 0; i < 2; ++i)
    {
        fin >> users[i].id >> users[i].name >> users[i].time >> users[i].score;
        cout << endl; //��ĭ �ٱ�
        cout << "-----------------------------------" << endl;
        cout << "����� #" << i + 1 << " ����:" << endl;
        cout << "ID: " + user << endl;
        cout << "�̸�: " << users[i].name << endl;
        cout << "���� �ð�: " << users[i].time << endl;
        cout << "���� ���� ����: " << users[i].score << endl;
        getfiletime("userinform.dat");
        cout << "-----------------------------------" << endl;
    }

    fin.close();

    return 0;
}
