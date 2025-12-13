/*

열린 구간과 닫힌 구간을 잘 구분해야한다. 

구하고자 하는 것이 경계 값의 최소인지 최대인지 특정 값인지에 따라 결정

열린 구간
-> while (low < high)  [low, high) 즉 
이 구간에서는 경계의 low를 찾거나  

high 및 low의 갱신 규칙

닫힌 구간 [low, high]
→ low와 high 모두 탐색 대상에 포함됨.
→ 탐색 가능한 값의 실제 범위 전체를 그대로 넣는다.

열린 구간 [low, high)
→ high는 탐색 대상이 아님.
→ 즉, “탐색 구간의 오른쪽 경계 바로 다음 값”까지 high에 넣는다.

(A) lower bound (처음으로 ok==true인 최소 x)
구간	while	조건이 참이면	조건이 거짓이면	종료 후 반환
닫힌 [l,r]	l <= r	r = mid - 1	l = mid + 1	l
열린 [l,r)	l < r	r = mid	l = mid + 1	l

(B) upper bound (마지막으로 ok==true인 최대 x)
구간	while	mid 선택	조건이 참이면	조건이 거짓이면	종료 후 반환
닫힌 [l,r]	l <= r	mid = (l+r)/2	l = mid + 1	r = mid - 1	r
열린 [l,r] 관점으로 구현을 깔끔히 하려면	l < r	상향 편향 mid mid = (l+r+1)/2	l = mid	r = mid - 1	l

(C) 정확히 target 찾기 (정렬 배열)
int find_idx(const vector<int>& a, int target){
    int l = 0, r = (int)a.size()-1;
    while(l <= r){
        int mid = l + (r - l)/2;
        if (a[mid] == target) return mid;
        else if (a[mid] < target) l = mid + 1;
        else                      r = mid - 1;
    }
    return -1; // 못 찾음
}







*/
#include <iostream>


int low = 0, high = n - 1;
while (low <= high) {
    int mid = (low + high) / 2;
    if (arr[mid] >= target)
        high = mid - 1; // mid 가능 → 왼쪽 좁히기
    else
        low = mid + 1;  // mid 불가능 → 오른쪽 확장
}
return low; // 첫 번째로 target 이상인 위치