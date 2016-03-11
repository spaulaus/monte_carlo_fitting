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

#include "MonteFit.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    //Instance of the MC fitting;
    MonteFit func;

    //Generating the function that we are going to fit.
    vector< pair<double,double> > data;
    for(double i = -5; i <= 15; i += 0.5)
        data.push_back(make_pair(i, func.Gaussian(i,2.,3.,5.)));

    //Pass the data to the fitter 
    func.SetData(data);
    func.SetTolerance(0.02);
    func.SetMaxIterations(1e4);

    func.Minimize();
}
