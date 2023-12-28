#include <iostream>
#include <windows.h>

using namespace std;

CRITICAL_SECTION cs; // ũ��Ƽ�� ���� �߰�
static int cnt = 0;
static int num[10];
static int sum[10] = { 0, };
static int totalsum;

//ThreadPramas ����ü
struct ThreadParams
{
    int start;
    int end;
};

//�Է°� �ޱ� & ���
DWORD WINAPI InputThread(LPVOID lpParam)
{

    // ũ��Ƽ�� ���� ����
    EnterCriticalSection(&cs);

    for (int i = 0; i < 10; i++)
    {
        cin >> num[i];
        cnt++;
    }

    cout << '\n';

    for (int i = 0; i < 10; i++)
    {
        cout << num[i] << endl;
    }

    cout << '\n';


    // ũ��Ƽ�� ���� ����������
    LeaveCriticalSection(&cs);

    return cnt; // ������ �ε��� ��ȯ
}

//sum & avg
DWORD WINAPI SumThread(LPVOID lpParam)
{
    ThreadParams* params = (ThreadParams*)lpParam;
    int start = params->start;
    int end = params->end;

    float avg = 0;
    int totalsum = 0;

    // ũ��Ƽ�� ���� ����
    EnterCriticalSection(&cs);
    for (int i = start; i < end; i++)
    {
        sum[start] += num[i];
    }
    
    for (int i = 0; i < 10; i++)
    {
        totalsum += sum[i];
    }   

    if (end == 10)
    {
        avg = totalsum / 10.0f;
        cout << "Average: " << avg<<endl;
        cout << "Sum: " << totalsum << endl;
    }

    // ũ��Ƽ�� ���� ����������
    LeaveCriticalSection(&cs);

    return 0;
}

int main()
{
    // ũ��Ƽ�� ���� �ʱ�ȭ
    InitializeCriticalSection(&cs);

    DWORD dwThreadID[4];
    HANDLE hThread[4];

    //8�� 2*4
    ThreadParams paramThread[] = { {0, 10}, {0, 4}, {4, 7}, {7, 10} };

    // ������ 0: Input �ް� ���
    hThread[0] = CreateThread(
        NULL, 0,
        InputThread,
        (LPVOID)(&paramThread[0]),
        0, &dwThreadID[0]
    );

    // ������ 1~3����: avg,sum ���
    for (int i = 1; i < 4; i++) {
        hThread[i] = CreateThread(
            NULL, 0,
            SumThread,
            (LPVOID)(&paramThread[i]),
            0, &dwThreadID[i]
        );
    }

    // ������ ���� ���� Ȯ��
    if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL || hThread[3] == NULL)
    {
        cout << "Thread creation fault!" << endl;
        return -1;
    }

    // ������ ���� ���
    WaitForMultipleObjects(4, hThread, TRUE, INFINITE);

    // ũ��Ƽ�� ���� ����
    DeleteCriticalSection(&cs);

    // �ڵ� �ݱ�
    for (int i = 0; i < 4; i++)
    {
        CloseHandle(hThread[i]);
    }

    return 0;
}