#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MAX_R 1000000



long long solution(int r1, int r2) {
    long long answer = 0;


    
    for(int i=0; i<=r2; ++i)
    {
        
        if(i==0)
        {
            continue;
        }

        int tmp2 = (int)sqrt(r2*r2 - i * i);
        int tmp1 = 0;
        if(r1 < i)
        {
            answer += tmp2;
        }
        else{
            tmp1 = (int)sqrt(r1 * r1 - i * i);
            answer += tmp2 - tmp1;
        }

    }

    long long answer3 = answer * 4; 

    return answer3;
}