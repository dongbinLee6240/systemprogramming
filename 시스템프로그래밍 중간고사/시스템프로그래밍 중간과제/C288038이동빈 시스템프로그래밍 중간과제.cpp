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

    cout << "�����ð�: " << ctime(&filestat.st_ctime);
    cout << "���ٽð�: " << ctime(&filestat.st_atime);
    cout << "���� �����ð�: " << ctime(&filestat.st_mtime);
}

void GetFileTime(const char* filename, ofstream& outfile)
{
    struct _stat filestat;

    if (_stat(filename, &filestat) != 0)
    {
        throw string("getfiletime_error");
    }

    outfile << "�����ð�: " << ctime(&filestat.st_ctime);
    outfile << "���ٽð�: " << ctime(&filestat.st_atime);
    outfile << "���� �����ð�: " << ctime(&filestat.st_mtime);
}

int main()
{
     GetComputerName();
    
     // try��
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

        // ����� ���� �Է¹޾� ���Ͽ� ����
        for (int i = 0; i < 10; ++i)
        {
            cout << endl;

            cout << "����� #" << i + 1 << " ���� �Է�:" << endl;

            cout << "id: " + user << '\n';

            cout << "�̸�: ";
            cin >> users[i].name;

            char* ptr = strpbrk(users[i].name, "!@#$%^&*()-+"); //name�� Ư�� ���� ���� ���
            if (ptr != NULL) 
            {

                throw string("name_error");
            }
          
            cout << "���� �ð�: ";
            cin >> users[i].time;
            if (users[i].time < 0)  //�ð��� �����϶�
            {
                throw string("time_error");
            }

            cout << "���� ���� ����: ";
            cin >> users[i].score;
            if (users[i].score < 0)  //������ �����϶�
            {
                throw string("score_error");
            }
            // ���Ͽ� ����
            fout << users[i].id << " " << users[i].name << " " << users[i].time << " " << users[i].score << endl;

            fout.close(); // ���� �ݱ�
            DisplayFileTime("userinform.dat");
            GetFileTime("userinform.dat", fout);
            fout.open("userinform.dat", ios::app); //���� �ٽ� ����
        }

        fout.close();

        // userinform.dat������ getfiletime�� fileMgOut �� �ֱ�
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
            cout << endl; // �� ĭ �ٱ�
            cout << "-----------------------------------" << endl;
            cout << "����� #" << i + 1 << " ����:" << endl;
            cout << "ID: " + user << endl;
            cout << "�̸�: " << users[i].name << endl;
            cout << "���� �ð�: " << users[i].time << endl;
            cout << "���� ���� ����: " << users[i].score << endl;
            DisplayFileTime("userinform.dat");
            GetFileTime("userinform.dat", fileMgOut);
            cout << "-----------------------------------" << endl;
        }

        fin.close();

        return 0;
    }
    // catch��
    catch (const string& error)
    {
        if (error == "userinform_error")
        {
            cout << "userinform.dat ���� ���� ����" << endl;
        }
        else if (error == "getfiletime_error")
        {
            cout << "�������� �������� ����" << endl;
        }
        else if (error == "fileMgOut_error")
        {
            cout << "fileMgOut ���� ���� ����" << endl;
        }
        else if (error == "time_error")
        {
            cout << "�߸��� �ð�ǥ���Դϴ�." << endl;
        }
        else if (error == "score_error")
        {
            cout << "�߸��� ����ǥ���Դϴ�." << endl;
        }
        else if (error == "name_error")
        {
            cout << "�̸��� Ư�����ڰ� �ֽ��ϴ�." << endl;
        }
        else
        {
            cout << "�� �� ���� ����: " << error << endl;
        }
    }
    
}
