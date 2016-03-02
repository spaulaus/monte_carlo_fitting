/*! \file MonteFit.hpp
 * \brief Header for a simple Monte Carlo fitting routine.
 * \author S. V. Paulauskas
 * \date February 25, 2016
 *
 * Copyright S. V. Paulauskas 2016
 * stanpaulauskasATgmailDOTcom
 * Distributed under GNU General Public Licence v3
 */
#ifndef __MONTEFIT_HPP__
#define __MONTEFIT_HPP__

#include <random>
#include <vector>

#include "GaussianFunction.hpp"

class MonteFit {
public:
    /** Default Constructor */
    MonteFit ();
    /** Default Destructor */
    ~MonteFit();

    /** \return maxIter_ */
    double GetMaxIterations(void){return(maxIter_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetMaxIterations(const double &a) {maxIter_ = a;}

    /** \return tolerance_ */
    double GetTolerance(void){return(tolerance_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetTolerance(const double &a) {tolerance_ = a;}
    
    /** \return data_ */
    std::vector<std::pair<double,double> > GetData(void){return(data_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetData(const std::vector< std::pair<double, double> > &a) {data_ = a;}
    
    void SetFunction(GaussianFunction *a) {gaus_ = a;}; 

    void Minimize(void);
private:
    unsigned int maxIter_;
    double tolerance_;
    double currentMin_;
    std::vector<std::pair<double,double> > data_;

    std::vector<double> results_;

    double GenerateParameterSets(void);
    void Initialize();

    GaussianFunction *gaus_;
    
    double *func;
    std::mt19937_64 *engine_;
    std::uniform_real_distribution<double> *dist_;
};
#endif //__MONTEFIT_HPP__
