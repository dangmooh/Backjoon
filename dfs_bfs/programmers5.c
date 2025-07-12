#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int total_time(int level, int diffs[], int times[], size_t n, long long limit)
{
    long long t = 0;
    t += times[0];

    for(size_t i=1; i<n; i++)
    {
        if(level >= diffs[i])
        {
            t += times[i];
        }
        else
        {
            int misses = diffs[i] - level;
            t += (long long)misses*(times[i] + times[i-1]) + times[i];
        }
        if (t > limit) break;
    }
    return t;
}

// diffs_len은 배열 diffs의 길이입니다.
// times_len은 배열 times의 길이입니다.
int solution(int diffs[], size_t diffs_len, int times[], size_t times_len, long long limit) {
    int answer = 0;

    size_t n = diffs_len;
    int maxdiff = 0;
    for(size_t i=0; i<n; i++)
    {
        if(diffs[i]> maxdiff)
        {
            maxdiff = diffs[i];
        }
    }

    int low =1, high = maxdiff;
    while(low < high)
    {
        int mid = low + (high - low) / 2;
        if(total_time(mid, diffs, times, n, limit) <= limit)
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }

    return low;
}