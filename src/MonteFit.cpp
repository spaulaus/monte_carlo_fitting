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
    Initialize();
}

MonteFit::~MonteFit(void){
    delete(engine_);
    delete(dist_);
}

void MonteFit::Initialize() {
    engine_ = new mt19937_64(chrono::system_clock::now().time_since_epoch().count());
    dist_ = new uniform_real_distribution<double>(0,10);
    currentMin_ = 1.e7;
}

double MonteFit::GenerateParameterSets(void) {
    return(dist_->operator()(*engine_));
}

void MonteFit::Minimize(void) {
    vector<double> params(3,0);
    for(unsigned int i = 0; i < maxIter_; i++) {
        params[0] = GenerateParameterSets();
        params[1] = GenerateParameterSets();
        params[2] = GenerateParameterSets();

        double diff = 0;
        for(vector<pair <double, double> >::iterator it = data_.begin();
            it != data_.end(); it++)
            diff += (fabs((*it).second - gaus_->operator()(&((*it).first), &params[0])) / (*it).second);

        if(diff < currentMin_) {
            currentMin_ = diff;
            results_ = params;
        }
        
        if(diff < tolerance_) {
            results_ = params;
            break;
        }
    }//for(unsigned int i ...)
    
    for(double i = -5; i <= 15; i += 0.5)
        cout << i << " " << gaus_->operator()(&i, &results_[0]) << endl;
}

