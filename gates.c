#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
float sigmoidf(float x) {
    return 1.0f / (1.0f + expf(-x));
}

float train[][3] = {
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,1},

};
#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float(void) {
    return (float) rand() / (float) RAND_MAX;
}

float cost(float weight1, float weight2) {
    float result = 0.0f;
    for(size_t i = 0; i < train_count; ++i) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf(x1 * weight1 + x2 * weight2);
        float d = y - train[i][2];    
        result += d*d;
    }
    result /= train_count;
    return result;
}

int main() {
    srand(time(0));
    float EPS = 1e-1;
    float LEARNING_RATE = 1e-1;
    int ITERATIONS = 1000;
    float weight1 = rand_float();
    float weight2 = rand_float();

    for(size_t i = 0; i < ITERATIONS; ++i) {
        float c = cost(weight1, weight2);
        printf("cost = %f, weight1 = %f, weight2 = %f\n", c, weight1, weight2);

        float dw1 = (cost(weight1 + EPS, weight2) - c) / EPS;
        float dw2 = (cost(weight1, weight2 + EPS) - c) / EPS;
        weight1 -= LEARNING_RATE*dw1;
        weight2 -= LEARNING_RATE*dw2;
    }
    return 0;
}