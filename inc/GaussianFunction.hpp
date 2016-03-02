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
 *  \date March 02, 2016
 */
#ifndef __GAUSSIANFUNCITON__HPP__
#define __GAUSSIANFUNCITON__HPP__

#include <vector>

class GaussianFunction {
public:
    GaussianFunction() {baseline_ = 0;};
    ~GaussianFunction(){};

    double operator() (double *x, double *p);
 
    void SetBaseline(const double &a){baseline_ = a;};
    double GetBaseline(void) {return(baseline_);};

    /** \return amp_ */
    double GetAmplitude(void){return(amp_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetAmplitude(const double &a) {amp_ = a;}
    
    /** \return beta_ */
    double GetSigma(void){return(sigma_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetSigma(const double &a) {sigma_ = a;};
    
    /** \return phase_ */
    double GetPhase(void){return(mu_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetPhase(const double &a) {mu_ = a;};
private:
    double mu_, amp_, sigma_;
    double baseline_;
};
#endif
