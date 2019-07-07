
#include "Gnuplot.hpp"

// Plot the result using Gnuplot 
void PlotResults (vector<double> &CAAR_Beat, vector<double> &CAAR_Meet, vector<double> &CAAR_Miss)
{
    getchar();
    int nIntervals = 119;
    int stepSize = 1;
    
    int* DateRange = (int*) malloc((nIntervals+1)*sizeof(int));
    
    DateRange[0] = -59;
    int x0;
    for (int i = 0; i < nIntervals; i++)
    {
        x0 = DateRange[i];
        DateRange[i+1] = x0 + stepSize;
    }
    
    FILE *gnuplotPipe, *tempDataFile;
    const char *tempDataFileName1 = "Beat";
    const char *tempDataFileName2 = "Meet";
    const char *tempDataFileName3 = "Miss";
    double x1, y1, x2, y2, x3, y3;
    
    gnuplotPipe = popen("/opt/local/bin/gnuplot","w");
    if (gnuplotPipe)
    {
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n",tempDataFileName1,
                                                                                             tempDataFileName2,
                                                                                             tempDataFileName3);
        fflush(gnuplotPipe);
        
        tempDataFile = fopen(tempDataFileName1,"w");
        for (int i = 0; i <= nIntervals; i++)
        {
            x1 = DateRange[i];
            y1 = CAAR_Beat[i];
            fprintf(tempDataFile, "%lf %lf\n", x1, y1);
        }
        fclose(tempDataFile);
        
        tempDataFile = fopen(tempDataFileName2,"w");
        for (int i = 0; i <= nIntervals; i++)
        {
            x2 = DateRange[i];
            y2 = CAAR_Meet[i];
            fprintf(tempDataFile, "%lf %lf\n", x2, y2);
        }
        fclose(tempDataFile);
        
        tempDataFile = fopen(tempDataFileName3,"w");
        for (int i = 0; i <= nIntervals; i++)
        {
            x3 = DateRange[i];
            y3 = CAAR_Miss[i];
            fprintf(tempDataFile, "%lf %lf\n", x3, y3);
        }
        fclose(tempDataFile);
        
        cout << endl;
        printf("# Press enter to continue ... # ");
        getchar();
        remove(tempDataFileName1);
        remove(tempDataFileName2);
        remove(tempDataFileName3);
        fprintf(gnuplotPipe,"exit \n");
        
    } else
    {
        printf("gnuplot not found...");
    }
    
}

