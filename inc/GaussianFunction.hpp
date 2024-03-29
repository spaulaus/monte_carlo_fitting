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

#include "FittingFunction.hpp"

class GaussianFunction : public FittingFunction {
public:
    GaussianFunction() {};
    ~GaussianFunction(){};

    double operator() (double *x, double *p);
 };
#endif
