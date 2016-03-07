/*! \file main.cpp
 * \brief main for a simple MC fitting class
 * \author S. V. Paulauskas
 * \date February 25, 2016
 */
 /***************************************************************************
  *  Copyright S. V. Paulauskas 2012-2014                                  *
  *                                                                        *
  *  This program is free software: you can redistribute it and/or modify  *
  *  it under the terms of the GNU General Public License as published by  *
  *  the Free Software Foundation, version 3.0 License.                    *
  *                                                                        *
  *  This program is distributed in the hope that it will be useful,       *
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
  *  GNU General Public License for more details.                          *
  *                                                                        *
  *  You should have received a copy of the GNU General Public License     *
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
  *************************************************************************/
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

#include "VandleTimingFunction.hpp"
#include "GaussianFunction.hpp"
#include "MonteFit.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    //Instance of the MC fitting;
    MonteFit fitter;

    double phase = 5.0, amp = 3.0, sigma = 2.0;
    
    GaussianFunction *gaus = new GaussianFunction();
    
    vector<double> params;
    params.push_back(phase);
    params.push_back(amp);
    params.push_back(sigma);

    vector< pair<double,double> > guesses;
    guesses.push_back(make_pair(-100, 100));
    guesses.push_back(make_pair(-100, 100));
    guesses.push_back(make_pair(-100, 100));

    //Generating the function that we are going to fit.
    vector< pair<double,double> > data;
    for(double i = -5; i <= 15; i += 0.5)
        data.push_back(make_pair(i, gaus->operator()(&i, &params[0])));

    //Pass the data to the fitter
    fitter.SetFunction(gaus);
    fitter.SetInitialGuesses(guesses);
    fitter.SetData(data);
    fitter.SetTolerance(1e-4);
    fitter.SetMaxIterations(1e5);

    cout << "counter,diff,mu,amp,sigma" << endl;
    
    //Actually perform the fitting
    std::chrono::time_point<std::chrono::system_clock> start =
        std::chrono::system_clock::now();
    fitter.Minimize();
    std::chrono::time_point<std::chrono::system_clock> end =
        std::chrono::system_clock::now();

    std::chrono::duration<double> diff = (end-start);

    // ofstream timeout("mintime.dat", ios::app);
    // timeout << diff.count() << endl;
    // timeout.close();

    //cout << diff.count() << " " << fitter.GetNumIterations() << endl;

    //Obtain the vector containing the results
    vector<double> results = fitter.GetResults();

    //Output our results to a text file for plotting.
    ofstream out("fitResults.dat");
    out << "# Number of iterations necessary " << fitter.GetNumIterations() << endl
        << "#phase = " << results[0] << " " << endl
        << "#amplitude = " << results[1] << " " << endl
        << "#sigma = " << results[2] << " " << endl
        <<"#-------------------------------------------------------" << endl;
    
    for(double i = -5; i <= 15; i += 0.5)
        out << i << " " << gaus->operator()(&i, &results[0]) << endl;
    out.close();

}
