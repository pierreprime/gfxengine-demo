#include "score.h"

int score;

void score_init()
{
    score = 0;
}

int score_get()
{
    return score;
}

void score_set(int s)
{
    score = s;
}
