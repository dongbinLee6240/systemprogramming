#include <iostream>
#include <windows.h>

using namespace std;

CRITICAL_SECTION cs; // 크리티컬 섹션 추가
static int cnt = 0;
static int num[10];
static int sum[10] = { 0, };
static int totalsum;

//ThreadPramas 구조체
struct ThreadParams
{
    int start;
    int end;
};

//입력값 받기 & 출력
DWORD WINAPI InputThread(LPVOID lpParam)
{

    // 크리티컬 섹션 진입
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


    // 크리티컬 섹션 빠져나오기
    LeaveCriticalSection(&cs);

    return cnt; // 스레드 인덱스 반환
}

//sum & avg
DWORD WINAPI SumThread(LPVOID lpParam)
{
    ThreadParams* params = (ThreadParams*)lpParam;
    int start = params->start;
    int end = params->end;

    float avg = 0;
    int totalsum = 0;

    // 크리티컬 섹션 진입
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

    // 크리티컬 섹션 빠져나오기
    LeaveCriticalSection(&cs);

    return 0;
}

int main()
{
    // 크리티컬 섹션 초기화
    InitializeCriticalSection(&cs);

    DWORD dwThreadID[4];
    HANDLE hThread[4];

    //8개 2*4
    ThreadParams paramThread[] = { {0, 10}, {0, 4}, {4, 7}, {7, 10} };

    // 스레드 0: Input 받고 출력
    hThread[0] = CreateThread(
        NULL, 0,
        InputThread,
        (LPVOID)(&paramThread[0]),
        0, &dwThreadID[0]
    );

    // 스레드 1~3생성: avg,sum 계산
    for (int i = 1; i < 4; i++) {
        hThread[i] = CreateThread(
            NULL, 0,
            SumThread,
            (LPVOID)(&paramThread[i]),
            0, &dwThreadID[i]
        );
    }

    // 스레드 생성 실패 확인
    if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL || hThread[3] == NULL)
    {
        cout << "Thread creation fault!" << endl;
        return -1;
    }

    // 스레드 종료 대기
    WaitForMultipleObjects(4, hThread, TRUE, INFINITE);

    // 크리티컬 섹션 삭제
    DeleteCriticalSection(&cs);

    // 핸들 닫기
    for (int i = 0; i < 4; i++)
    {
        CloseHandle(hThread[i]);
    }

    return 0;
}