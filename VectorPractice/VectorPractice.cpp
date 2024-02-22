#include <iostream>
using namespace std;
#include <vector>

int main()
{
    //==========================================================================
    // vector

    vector<int> v;

    // size(resize)
    // capacity (reserve)
    // 사이즈는 실제 데이터 크기
    // capacity 는 할당된 공간


    // 삽입/삭제
    // - 시작 O(N)
    // - 중간 O(N)
    // - 끝   O(1)
    // push_back, front, back

    // 임의접근 
    // v[i]   O(1)
    // v.remove(10)

    // reserve 를 먼저 하고 작업하는 이유는 이사비용을 아낄 수 있다.
    v.reserve(10);

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);


    int a = v.front();  // O(1)
    int b = v.back();   // O(1)

    // 벡터에는 데이터를 앞에 넣는 함수는 없다!!

    v[2] = 100;         // O(1)

    const int size = v.size();      // 미리 계산하면 for문이 돌때마다 v.size() 호출되는 것을 아낄수 있음
    for (int i = 0; i < size; i++)
        cout << v[i] << endl;


    // 초기화
    vector<int> v2(5);      // capacity 세팅
    vector<int> v3(5, -1);  // capacity 초기값 세팅
    vector<int> v4{ 1, 2, 3, 4, 5 }; // c++11 에서 등장한 초기값 세팅

    // vector는 동적 배열 = heap 영역에 할당
    // vector 라는 클래스 자체는 stack에 있지만 실제 데이터는 heap 영역에 있다
    vector<int> v5 = v4;

    v5[0] = 100;    // v5 값만 바뀐다. 즉, v4의 값이 v5에 값이 복사된다.

    // 함수로 호출할 때 넘긴 vector가 복사되는걸 방지하고 싶다면?
    // Test(vector<int>& v)
    // {}

    // clear() 를 했을 때 size와 capacity 는 어떻게 될까?
    // size     => 0 으로 줄어든다(데이터는 사라진다)
    // capacity => 줄어들지 않는다(이사비용을 아끼기 위해서)

    // capacity 를 정말 0으로 메모리를 정리하고 싶다면?
    // 실전에선 거의 사용하지는 않는다.
    vector<int>().swap(v4);

    //==========================================================================
    // iterator 반복자

    {
        vector<int> v{ 1, 2, 3, 4, 5 };

        int* ptr = &v[0];
        int* ptrEnd = &v[4] + 1;

        while (ptr != ptrEnd)
        {
            cout << *ptr << endl;
            ptr++;
        }
    }

    // 포인터를 사용하지 않고 iterator를 사용하는 이유
    // 어떠한 자료구조를 사용하더라도 호환되기 때문에 동일한 코드를 유지할 수 있다.
    {
        vector<int> v{ 1, 2, 3, 4, 5 };

        vector<int>::iterator it;
        for(it = v.begin(); it != v.end(); it++)
        {
            int data = *it;
            if (data == 3)
            {
                // 데이터를 찾음
                break;
            }
        }

        // 제대로 찾은 건지 크로스 체킹시
        if (it != v.end())
        {
            // 찾은 상태인 경우 들어옴
            cout << "찾음" << endl;

            // 느린건 알지만 중간에 특정 값을 삭제하고 싶은 경우
            v.erase(it);        // { 1, 2, 4, 5 }
        }

        
    }
    

    {
        // 모든 데이터를 순회하다 특정 조건에 따라 제거할 때 주의해야함
        // 실수를 많이 함!!
        vector<int> v{ 1, 2, 3, 4, 5 };

        // [1]
        //for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        //{
        //    int value = *it;
        //    if (value % 2 == 0)
        //        v.erase(it)
        //}

        // [2]
        for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        {
            cout << *it << endl;
        }

        // 의도는 알겠지만, [1] 부터 크래시가 나서 실행이 안된다.
        // 왜 안되는가?
        // erase()를 하게 되면 { 1, 2, 3, 4, 5} => {1, 3, 4, 5 } 가 된 이후 3의 위치를 다시 반환해주기 때문에 
        // v.erase(it)가 아니라
        // it = v.erase(it)로 받아줘야한다.
        // 하지만 순회를 할 때 증감식에 it++을 그대로 둔다면 { 1, 3, 4, 5 } 에서 3이 들어있는 자리는 체크하지 않고
        // 증감이 되어 4가 있는 값부터 체크를 하게 되어 원하지 않는 동작이 일어날 수 있다.
        // 따라서 아래처럼 만들어 줘야 정상 작동 한다.

        for (vector<int>::iterator it = v.begin(); it != v.end();)
        {
            int value = *it;
            if (value % 2 == 0)
                it = v.erase(it);
            else
                it++;
        }

        for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        {
            cout << *it << endl;
        }
    }

}
