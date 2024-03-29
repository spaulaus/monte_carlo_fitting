 /**************************************************************************
  *  Copyright S. V. Paulauskas 2014                                       *
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
  **************************************************************************
*/

/*! \file GaussianFunction.hpp
 *  \brief A class to handle the processing of traces
 *  \author S. V. Paulauskas
 *  \date 03 October 2014
 */
#include <iostream>

#include <cmath>

#include "GaussianFunction.hpp"

using namespace std;

double GaussianFunction::operator()(double *x, double *par) {
    double t = x[0];
    double phase = par[0];
    double amplitude = par[1];
    double sigma = par[2];
    double baseline = par[3];

    double coeff = amplitude/(sigma*sqrt(2*M_PI));
    double exponent = -pow((t-phase)/sigma,2)*0.5;

    return( coeff * exp(exponent) + baseline);
}
