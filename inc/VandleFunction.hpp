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

/*! \file VandleFunction.hpp
 *  \brief A class to handle the processing of traces
 *  \author S. V. Paulauskas
 *  \date 03 October 2014
 */
#ifndef __VANDLEFUNCITON__HPP__
#define __VANDLEFUNCITON__HPP__

#include <vector>

#include "FittingFunction.hpp"

class VandleFunction : public FittingFunction{
public:
    VandleFunction() {};
    ~VandleFunction(){};

    double operator() (double *x, double *p);

    /** Defines the Fitting function for standard PMTs
     * \param [in] x : the vector of gsl starting parameters
     * \param [in] FitData : The data to use for the fit
     * \param [in] f : pointer to the function
     * \return an integer that GSL does something magical with */
    static int Function(int numPoints, int numPars, double *pars,
                        double *residuals, double **dvec, void *vars);
    
    void SetBaseline(const double &a){baseline_ = a;};
    double GetBaseline(void) {return(baseline_);};
private:
    double baseline_;
};

///Solely defined for the sake of using the GSL with this class
class FittingData {
public:
    FittingData(){};
    ~FittingData(){};
    
    std::vector<double> *x,  *y, *erry;
    double qdc, baseline;
};
#endif
