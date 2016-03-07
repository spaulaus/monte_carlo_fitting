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
    for(vector< uniform_real_distribution<> *>::iterator it = distList_.begin();
        it != distList_.end(); it++)
        delete((*it));
}

void MonteFit::Initialize() {
    engine_ = new mt19937_64(chrono::system_clock::now().time_since_epoch().count());
    currentMin_ = 1.e7;
    numIter_ = 0;
    maxIter_ = 1e6;
    tolerance_ = 1e-6;
}

void MonteFit::SetInitialGuesses(const std::vector< std::pair<double, double> > &a) {
        iGuess_ = a;
        for(vector< pair<double, double> >::const_iterator it = a.begin();
            it != a.end(); it++)
            distList_.push_back(new uniform_real_distribution<double>((*it).first,
                                                                     (*it).second));
}

void MonteFit::Minimize(void) {
    //Maybe do a smart iteration, so that we update the range for the fitting to
    //be constrained by the best two/three results that we got this time around
    vector<double> params(3,0);
    int counter = 0;
    for(unsigned int i = 0; i < maxIter_; ++i, ++numIter_) {
        params[0] = distList_.at(0)->operator()(*engine_);
        params[1] = distList_.at(1)->operator()(*engine_);
        params[2] = distList_.at(2)->operator()(*engine_);

        double diff = 0;
        //code catch for 0's in the data.
        for(vector<pair <double, double> >::iterator it = data_.begin();
            it != data_.end(); it++)
            diff += (pow((*it).second - gaus_->operator()(&((*it).first), &params[0]),2) / (*it).second);

        if(diff < 5) {
            cout << counter << "," << diff << ","
                 << params[0] << "," << params[1] << "," << params[2] << endl;
            counter++;
        }
            
        if(diff < currentMin_) {
            currentMin_ = diff;
            results_ = params;
        }
        
        if(diff < tolerance_) {
            results_ = params;
            break;
        }
    }//for(unsigned int i ...)
}

