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
#include <vector>

#include "VandleFunction.hpp"
#include "MonteFit.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    vector<pair<double,double> > data;
    ///Read in the trace that we plan to fit
    double junk, junk1, junk2;
    ifstream infile("data/trc/vandle/mediumTrc08.dat");
    if(!infile)
        cerr << "Cannot open input file. Try again, son." << endl;
    else {
        while(infile) {
            if (isdigit(infile.peek())) {
                infile >> junk >> junk1 >> junk2;
                if(junk < 110 && junk > 60)
                    data.push_back(make_pair(junk,junk1));
            } else
                infile.ignore(1000,'\n');
        }
    }

    ///Instance the function to generate the data to fit.
    VandleFunction *vandle = new VandleFunction();

    ///Setting the parameters for the fitting data. 
    vector<double> pars;
    double phase = 5.0, amp = 3.0, sigma = 2.0, gamma = 0.005, baseline = 0.0;
    pars.push_back(phase);
    pars.push_back(amp);
    pars.push_back(sigma);
    pars.push_back(gamma);
    pars.push_back(baseline);
    
    ///Setting up the fitting ranges for the parameters.
    vector< pair<double,double> > guesses;
    guesses.push_back(make_pair(sigma,1));
    guesses.push_back(make_pair(amp, 1));
    guesses.push_back(make_pair(phase-0.5, 0.5));
    guesses.push_back(make_pair(0.0, 0.0));
    
    //Instance of the MC fitting;
    MonteFit fitter;

    ///Set the fitting function that we are going to minimize
    fitter.SetFunction(vandle);

    ///Pass the fitting range to the fitter 
    fitter.SetInitialGuesses(guesses);

    ///Initialize pass the data that we want to fit.
    fitter.SetData(data);

    ///Set the stopping criteria for the fit
    fitter.SetTolerance(0.02);

    ///Set the maximum number of iterations that the fit is allowed.
    fitter.SetMaxIterations(1e4);

    ///Set the number of parameters to fit.
    fitter.SetNumPar(4);

    ///Actually perform the fitting
    fitter.Minimize();

    //Return the results of the fit
    vector<double> results = fitter.GetResults();
}
