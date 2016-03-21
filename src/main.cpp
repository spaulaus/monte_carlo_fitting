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
#include <iostream>
#include <vector>

#include "GaussianFunction.hpp"
#include "MonteFit.hpp"


using namespace std;

int main(int argc, char* argv[]) {
    //Instance of the MC fitting;
    MonteFit fitter;

    GaussianFunction *gauss = new GaussianFunction();

    double phase = 5.0, amp = 3.0, sigma = 2.0;
    vector< pair<double,double> > guesses;
    guesses.push_back(make_pair(sigma,1));
    guesses.push_back(make_pair(amp, 1));
    guesses.push_back(make_pair(phase-0.5, 0.5));

    //Generating the function that we are going to fit.
    vector< pair<double,double> > data;
    for(double i = -5; i <= 15; i += 0.5)
        data.push_back(make_pair(i, fitter.Gaussian(i,sigma,amp,phase)));

    //Pass the data to the fitter 
    fitter.SetInitialGuesses(guesses);
    fitter.SetData(data);
    fitter.SetTolerance(0.02);
    fitter.SetMaxIterations(1e4);

    //Actually perform the fitting
    fitter.Minimize();
}
