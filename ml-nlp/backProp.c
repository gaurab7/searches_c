#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Define network structure
#define IN 2      // Input neurons
#define HN 2      // Hidden neurons
#define ON 1      // Output neurons
#define LR 0.5    // Learning rate

// Activation function and derivative
double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
double sigmoidDeriv(double y) { return y * (1.0 - y); }  // uses output y

int main() {
    srand(time(0));

    // XOR dataset
    double X[4][IN] = {{0,0}, {0,1}, {1,0}, {1,1}};
    double Y[4][ON] = {{0}, {1}, {1}, {0}};

    // Weights and biases
    double wIH[IN][HN], wHO[HN][ON], bH[HN], bO[ON];

    // Initialize random weights
    for (int i=0;i<IN;i++) for (int j=0;j<HN;j++) wIH[i][j] = ((double)rand()/RAND_MAX)-0.5;
    for (int i=0;i<HN;i++) for (int j=0;j<ON;j++) wHO[i][j] = ((double)rand()/RAND_MAX)-0.5;
    for (int i=0;i<HN;i++) bH[i] = ((double)rand()/RAND_MAX)-0.5;
    for (int i=0;i<ON;i++) bO[i] = ((double)rand()/RAND_MAX)-0.5;

    // Training loop
    for (int epoch=0; epoch<5000; epoch++) {
        for (int s=0; s<4; s++) {
            double h[HN], o[ON];

            // Forward pass
            for (int j=0;j<HN;j++) {
                h[j] = bH[j];
                for (int i=0;i<IN;i++) h[j] += X[s][i]*wIH[i][j];
                h[j] = sigmoid(h[j]);
            }
            for (int j=0;j<ON;j++) {
                o[j] = bO[j];
                for (int i=0;i<HN;i++) o[j] += h[i]*wHO[i][j];
                o[j] = sigmoid(o[j]);
            }

            // Errors
            double errO[ON], errH[HN];
            for (int j=0;j<ON;j++) {
                errO[j] = (Y[s][j]-o[j]) * sigmoidDeriv(o[j]);
                bO[j] += LR*errO[j];
            }
            for (int j=0;j<HN;j++) {
                errH[j] = 0;
                for (int k=0;k<ON;k++) errH[j] += errO[k]*wHO[j][k];
                errH[j] *= sigmoidDeriv(h[j]);
                bH[j] += LR*errH[j];
            }

            // Update weights
            for (int i=0;i<HN;i++) for (int j=0;j<ON;j++) wHO[i][j] += LR*errO[j]*h[i];
            for (int i=0;i<IN;i++) for (int j=0;j<HN;j++) wIH[i][j] += LR*errH[j]*X[s][i];
        }
    }

    // Testing
    printf("Trained XOR Neural Network:\n");
    for (int s=0; s<4; s++) {
        double h[HN], o[ON];

        for (int j=0;j<HN;j++) {
            h[j] = bH[j];
            for (int i=0;i<IN;i++) h[j] += X[s][i]*wIH[i][j];
            h[j] = sigmoid(h[j]);
        }
        for (int j=0;j<ON;j++) {
            o[j] = bO[j];
            for (int i=0;i<HN;i++) o[j] += h[i]*wHO[i][j];
            o[j] = sigmoid(o[j]);
        }

        printf("%d XOR %d = %.4f\n",(int)X[s][0],(int)X[s][1],o[0]);
    }
    return 0;
}
