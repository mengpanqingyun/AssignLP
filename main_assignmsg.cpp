#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "inout.h"
#include "readpara.h"
#include "wyarray.h"
#include "proassign.h"
#include "solvernle.h"
using namespace std;


int main (int argc, char **argv) {
   
    double start = time(NULL);
    //int maxLine = 6;
    //string scoreFileName("data/aaa.txt");
    //string targetFileName("data/aab.txt");

    //int maxLine = 37962;     // 17 msgs, 10000 users
    //string scoreFileName("data/u2p_score_0412.txt");
    //string targetFileName("data/u2p_target_0412.txt");
      
    /*
    int maxLine = 16070;   // 17 msgs, 1000 users
    //int maxLine = 1991;   // 2 msgs, 1000 users
    string scoreFileName("data/u2p_score_0319.txt");
    string targetFileName("data/u2p_target_0319.txt");
    string logFilename("output/u2p_0319_log.txt");
    string outFilename("output/u2p_0319_result.txt");
    */

    //
    int maxLine = 5089149;  // 391 msgs, 370498 users
    string scoreFileName("data/u2p_score_0424.txt");
    string targetFileName("data/u2p_target_0424.txt");
    string logFilename("output/u2p_0424_log.txt");
    string outFilename("output/u2p_0424_result.txt");
    //


    /* read parameters from file */
    ReaderFileAss *rdf = new ReaderFileAss(scoreFileName, targetFileName, maxLine); 
    rdf->getDataDimension ();
    rdf->readScoreFromFile ();
    //rdf->readTargetFromFile ();
    rdf->setTarget (0);
    //rdf->printScore();
    //rdf->printTarget();
    //exit(0);

    int nx = rdf->nusr * rdf->nmsg;

    // define the specific problem
    ProAssign *ass = new ProAssign(0.001, rdf->score, rdf->bottom, rdf->nusr, rdf->nmsg, "entropy");

    // define varibles
    double *x = new double[nx];
    double *ce = new double[rdf->nusr];
    double *cn = new double[rdf->nmsg];

    // define the solver
    SolverNle *sol = new SolverNle(ass, outFilename, logFilename);

    // run the solver
    sol->AugLag (x, ce, cn);





    // finished ...
    double stop = time(NULL);
    double durationTime = (double)difftime(stop, start);

    if (durationTime < 60)
       cout << endl << "Cost：" << durationTime << " sec" << endl;
    else if (durationTime < 3600)
       cout << endl << "Cost：" << durationTime/60.0 << " min" << endl;
    else
       cout << endl << "Cost：" << durationTime/3600.0 << " hour" << endl;

    ofstream fp(outFilename, ios::app);
    if (durationTime < 60)
       fp << " Cost : " << durationTime << " sec" << endl;
    else if (durationTime < 3600)
       fp << "Cost：" << durationTime/60.0 << " min" << endl;
    else
       fp << "Cost：" << durationTime/3600.0 << " hour" << endl;
    fp.close();


    rdf->free();
}
