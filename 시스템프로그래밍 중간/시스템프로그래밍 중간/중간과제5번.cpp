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

void getfiletime(const char* filename, ofstream& outfile)
{
    struct _stat filestat;

    if (_stat(filename, &filestat) != 0)
    {
        cerr << "���� ������ �������µ� ����" << endl;
        return;
    }

    outfile << "�����ð�: " << ctime(&filestat.st_ctime);
    outfile << "���ٽð�: " << ctime(&filestat.st_atime);
    outfile << "���� �����ð�: " << ctime(&filestat.st_mtime);
}

int main()
{
    try
    {
        string user = getenv("COMPUTERNAME");
        ofstream fout;
        userInfo users[2];

        fout.open("userinform.dat");

        if (!fout)
        {
            throw std::ios_base::failure("���� ���� ����");
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
            getfiletime("userinform.dat", fout);
            fout.open("userinform.dat", ios::app);
        }

        fout.close();

        // "FileMg.txt" ������ ��� getfiletime()�� ����� ����
        ofstream fileMgOut("FileMg.tax");

        if (!fileMgOut)
        {
            cerr << "FileMg.tax ���� ���� ����" << endl;
            return 1;
        }

        getfiletime("userinform.dat", fileMgOut);

        fileMgOut.close();

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
            getfiletime("userinform.dat", fileMgOut);
            cout << "-----------------------------------" << endl;
        }

        fin.close();

        return 0;
    }
}
