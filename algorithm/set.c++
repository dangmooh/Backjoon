/*
연관 컨테이너(associative container) 중 하나입니다.

노드 기반 컨테이너 이며 균형 이진트리로 구현되어있습니다.

Key라 불리는 원소들의 집합으로 이루어진 컨테이너 입니다. 

(원소 = key)key값은 중복이 허용 되지않습니다.

원소가 insert 멤버 함수에 의해 삽입이 되면, 원소는 자동으로 정렬 됩니다.

default 정렬기준은 less(오름차순) 입니다.

inorder traversal (중위순회) 를 통하여 순서대로 출력이 가능합니다.
iterator는 자동으로 inorder traversal 순서대로 출력해줍니다.

*/

#include <iostream>
#include <set>

