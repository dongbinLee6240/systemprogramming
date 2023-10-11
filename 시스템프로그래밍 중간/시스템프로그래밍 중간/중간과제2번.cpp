#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

struct userInfo
{
    char id[20];
    char name[20];
    int time;
    int score;
};

int main()
{
    string user = getenv("COMPUTERNAME");
    ofstream fout;
    userInfo users[10];

    fout.open("userinform.dat");

    if (!fout)
    {
        cerr << "���� ���� ����" << endl;
        return 1;
    }

    // ����� ���� �Է¹޾� ���Ͽ� ����
    for (int i = 0; i < 10; ++i)
    {
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
    }

    fout.close();

    ifstream fin("userinform.dat");

    for (int i = 0; i < 10; ++i)
    {
        fin >> users[i].id >> users[i].name >> users[i].time >> users[i].score;
        cout << endl; //��ĭ �ٱ�
        cout << "����� #" << i + 1 << " ����:" << endl;
        cout << "ID: "+user<< endl;
        cout << "�̸�: " << users[i].name << endl;
        cout << "���� �ð�: " << users[i].time << endl;
        cout << "���� ���� ����: " << users[i].score << endl;
        cout << "-------------------------" << endl;
    }

    fin.close();

    return 0;
}
