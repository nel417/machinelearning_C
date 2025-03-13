#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void train_network(NeuralNetwork *nn, int iterations, float eps, float learning_rate) {
    for (int i = 0; i < iterations; ++i) {
        float c = cost(*nn);
        float dw1 = (cost((NeuralNetwork){nn->weight1 + eps, nn->weight2, nn->bias}) - c) / eps;
        float dw2 = (cost((NeuralNetwork){nn->weight1, nn->weight2 + eps, nn->bias}) - c) / eps;
        float db = (cost((NeuralNetwork){nn->weight1, nn->weight2, nn->bias + eps}) - c) / eps;

        nn->weight1 -= learning_rate * dw1;
        nn->weight2 -= learning_rate * dw2;
        nn->bias -= learning_rate * db;
    }
}

int main() {
    return 0;
}
