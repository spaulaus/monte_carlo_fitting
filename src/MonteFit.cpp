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
    currentMin_ = 1.e7;
    maxIter_ = 1e4;
    tolerance_ = 0.2;
}

MonteFit::~MonteFit(void){
    delete(engine_);
    for(vector< normal_distribution<> *>::iterator it = distList_.begin();
        it != distList_.end(); it++)
        delete((*it));
    delete(results_);
}

void MonteFit::SetInitialGuesses(const std::vector< std::pair<double, double> > &a) {
        for(vector< pair<double, double> >::const_iterator it = a.begin();
            it != a.end(); it++)
            distList_.push_back(new normal_distribution<double>((*it).first,
                                                                     (*it).second));
}

void MonteFit::Minimize(void) {
    std::chrono::time_point<std::chrono::system_clock> start =
        std::chrono::system_clock::now();
    
    numIter_ = 0;
    for(unsigned int i = 0; i < maxIter_; i++, ++numIter_) {
        for(unsigned int j = 0; j < results_->size(); j++)
            results_->at(j) = distList_[j]->operator()(*engine_);
        
        double diff = 0;
        for(vector<pair <double, double> >::const_iterator it = data_.begin();
            it != data_.end(); it++)
            diff += pow((*it).second -
                        func->Gaussian((*it).first, results_), 2)
                     / (*it).second;

        if(diff < currentMin_)
            currentMin_ = diff;
        if(diff < tolerance_)
            break;
    }//for(unsigned int i ...)
    std::chrono::time_point<std::chrono::system_clock> end =
        std::chrono::system_clock::now();
    
    std::chrono::duration<double> minTime = (end-start);
    
    cout << minTime.count() << "," << currentMin_ << "," << results_->at(0) << ","
         << results_->at(1) << "," << results_->at(2) << "," << numIter_ << endl;
}

