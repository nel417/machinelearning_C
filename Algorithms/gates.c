#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define EPS 1e-1
#define LEARNING_RATE 1e-1
#define ITERATIONS 100000

typedef struct {
    float weight1;
    float weight2;
    float bias;
} NeuralNetwork;

float sigmoidf(float x) {
    return 1.0f / (1.0f + expf(-x));
}

float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1},
};

#define train_count (sizeof(train) / sizeof(train[0]))

float rand_float(void) {
    return (float)rand() / (float)RAND_MAX;
}

float cost(NeuralNetwork nn) {
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i) {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf(x1 * nn.weight1 + x2 * nn.weight2 + nn.bias);
        float d = y - train[i][2];
        result += d * d;
    }
    return result / train_count;
}

void train_network(NeuralNetwork *nn) {
    for (size_t i = 0; i < ITERATIONS; ++i) {
        float c = cost(*nn);
        float dw1 = (cost((NeuralNetwork){nn->weight1 + EPS, nn->weight2, nn->bias}) - c) / EPS;
        float dw2 = (cost((NeuralNetwork){nn->weight1, nn->weight2 + EPS, nn->bias}) - c) / EPS;
        float db = (cost((NeuralNetwork){nn->weight1, nn->weight2, nn->bias + EPS}) - c) / EPS;

        nn->weight1 -= LEARNING_RATE * dw1;
        nn->weight2 -= LEARNING_RATE * dw2;
        nn->bias -= LEARNING_RATE * db;
    }
}

int main() {
    srand(time(0));
    NeuralNetwork nn = {rand_float(), rand_float(), rand_float()};

    train_network(&nn);
    printf("cost = %f, weight1 = %f, weight2 = %f, bias = %f\n", cost(nn), nn.weight1, nn.weight2, nn.bias);

    return 0;
}