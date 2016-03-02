/*! \file MonteFit.hpp
 * \brief 
 * \author S. V. Paulauskas
 * \date February 25, 2016
 *
 * Copyright S. V. Paulauskas 2016
 * stanpaulauskasATgmailDOTcom
 * Distributed under GNU General Public Licence v3
 */
#include <chrono>
#include <iostream>

#include <cmath>

#include "MonteFit.hpp"

using namespace std;

MonteFit::MonteFit(void) {
    engine_ = new mt19937_64(chrono::system_clock::now().time_since_epoch().count());
    dist_ = new uniform_real_distribution<double>(0,10);
    currentMin_ = 1.e7;
}

MonteFit::~MonteFit(void){
    delete(engine_);
    delete(dist_);
}

double MonteFit::Gaussian(const double &t, const double &amp,
                          const double &sigma, const double &phase) {
    double coeff = amp/(sigma*sqrt(2*M_PI));
    double exponent = -pow((t-phase)/sigma,2)*0.5;
    return( coeff * exp(exponent) );
}

double MonteFit::GenerateParameterSets(void) {
    return(dist_->operator()(*engine_));
}

void MonteFit::Minimize(void) {
    for(unsigned int i = 0; i < maxIter_; i++) {
        double sigma = GenerateParameterSets();
        double phase = GenerateParameterSets();
        double amp    = GenerateParameterSets();
        
        double diff = 0;
        for(vector<pair <double, double> >::const_iterator it = data_.begin();
            it != data_.end(); it++)
            diff += (fabs((*it).second - Gaussian((*it).first, sigma, amp, phase)) / (*it).second);

        if(diff < currrentMin_)
            currentMin_ = diff;
        
        if(diff < tolerance_) {
            rBeta_ = sigma;
            rPhase_ = phase;
            rAmp_ = amp;
        }
    }//for(unsigned int i ...)
}

