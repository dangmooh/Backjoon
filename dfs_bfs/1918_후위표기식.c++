#include <iostream>
#include <stack>
#include <string>
using namespace std;

int prec(char op) {
    if(op=='*' || op=='/') return 2;
    if(op=='+' || op=='-') return 1;
    return 0;
}

int main() {
    string s; cin >> s;
    stack<char> stk;
    for(char ch : s) {
        if('A' <= ch && ch <= 'Z') {
            cout << ch;
        } else if(ch == '(') {
            stk.push(ch);
        } else if(ch == ')') {
            while(!stk.empty() && stk.top() != '(') {
                cout << stk.top(); stk.pop();
            }
            if(!stk.empty()) stk.pop(); // '(' 제거
        } else { // 연산자
            // == 여는 괄호 만나면 절대 pop하지 않는다!
            while(!stk.empty() && prec(stk.top()) >= prec(ch) && stk.top() != '(')
            {
                cout << stk.top(); stk.pop();
            }
            stk.push(ch);
        }
    }
    // 남은 연산자 pop (괄호는 빼고)
    while(!stk.empty()) {
        if(stk.top() != '(') cout << stk.top();
        stk.pop();
    }
    cout << '\n';
}
