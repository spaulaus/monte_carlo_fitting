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

/*! \file VandleTimingFunction.hpp
 *  \brief A class to handle the processing of traces
 *  \author S. V. Paulauskas
 *  \date 03 October 2014
 */
#include <iostream>

#include <cmath>

#include "VandleTimingFunction.hpp"

using namespace std;

double VandleTimingFunction::operator()(double *x, double *par) {
    double phase = par[0];
    double amplitude = par[1];
    double beta = par[2];
    double gamma = par[3];
    double diff = x[0] - phase;

    if(x[0] < phase)
        return(baseline_);

    double val = amplitude * exp(-beta*diff) * (1-exp(-pow(gamma*diff,4.)))
        + baseline_;

    return(val);
}

int VandleTimingFunction::Function (int numPoints, int numPars, double *pars,
                                    double *dy, double **dvec, void *vars){
    FittingData *data = (FittingData *)vars;
    double phi     = pars[0];
    double alpha   = pars[1];
    double beta = pars[2];
    double gamma = pars[3];

    cout << phi << " " << alpha << " " << beta << " " << gamma << endl;

    for(unsigned int t = 0; t < data->y->size(); t++) {
        double diff = data->y->at(t)-phi;

        if(t < phi)
            dy[t] = data->y->at(t);
        else
            dy[t] = (data->y->at(t) - data->qdc * alpha * exp(-beta*diff) *
                     (1-exp(-pow(gamma*diff,4.)))) / data->erry->at(t);
    }
    return(0);
}
