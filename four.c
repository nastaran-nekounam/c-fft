#include "stdio.h"
#include "Complex.h"
#include "stdlib.h"
#include <math.h>

#define N 1024
#define n 10
#define Fs 10000
#define w 3000
void plot_sig(double signal[N]){
    FILE *gnuplot = popen("gnuplot", "w");
    if (!gnuplot) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    fprintf(gnuplot, "plot '-' u 1:2 t 'Fs = 10kHz f = 3kHz' w lp\n");
    for (int i = 0; i < N; ++i) {
        if (i<N/2) {
            fprintf(gnuplot,"%f %1f \n", (float)i/N*Fs, signal[i]);
        }
        else{
            fprintf(gnuplot,"%f %1f \n", (float)(i-N)/N*Fs, signal[i]);
        }
    }
    fprintf(gnuplot, "e\n");
    fprintf(stdout, "Click Ctrl+d to quit...\n");
    fflush(gnuplot);
    getchar();
    pclose(gnuplot);
    exit(EXIT_SUCCESS);
}

int main () 
{
    complex input_sig[N];
    double signal_abs[N];
    for (int i = 0; i < N; ++i) {
        input_sig[i] = cmplx(sin(2*PI*w*i/Fs), 0.0);
    }
    fftr(input_sig, N, 1.0/Fs); 
    for (int i = 0; i < N; ++i) {
        signal_abs[i] = ccabs(input_sig[i]);
    }
    
    plot_sig(signal_abs);

   	return 0;
}