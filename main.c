#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
};
#define train_count (sizeof(train)/sizeof(train[0]))

float rand_float(void) {
    return (float) rand() / (float) RAND_MAX;
}

// the closer to cost function is 0, the better
float cost(float weight, float bias) {
    float result = 0.0f;
    for(size_t i = 0; i < train_count; i++) {
        float x = train[i][0];
        float y = x * weight + bias;
        float d = y - train[i][1];    
        result += d*d;
    }
    result /= train_count;
    return result;
}

int main() {
    srand(time(0));
    float weight = rand_float()*10.0f;
    float bias = rand_float()*5.0f;

    float eps = 1e-3;
    float rate = 1e-3;
    int iterations = 350;
    for(size_t i = 0; i < iterations; i++) {
        float dweight = (cost(weight + eps, bias) - cost(weight, bias)) /eps;
        float dbias = (cost(weight, bias + eps) - cost(weight, bias)) /eps;

        weight -= rate*dweight;
        bias -= rate*dbias;
        printf("cost = %f, weight = %f, bias = %f\n", cost(weight, bias), weight, bias);
    }
    printf("--------------------------------\n");
    printf("weight = %f, bias = %f\n", weight, bias);
    return 0;
}
