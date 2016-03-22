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
#include "VandleFunction.hpp"

class MonteFit {
public:
    /** Default Constructor */
    MonteFit ();
    /** Default Destructor */
    ~MonteFit();

    /** \return data_ */
    std::vector<std::pair<double,double> > GetData(void){return(data_);};
    /** \return maxIter_ */
    double GetMaxIterations(void){return(maxIter_);};
    ///\return Number of Iterations for the fit
    unsigned int GetNumIterations(void){return(numIter_);};
    ///\return A vector containing the results of the fit.
    std::vector<double> GetResults(void){return(results_);};
    /** \return tolerance_ */
    double GetTolerance(void){return(tolerance_);};
        
    ///The actual work horse of the operation
    void Minimize(void);
    /** Sets the data_ vector that the minimization will be working with
     * \param[in] a : The data set that will be minimized( data_ )*/
    void SetData(const std::vector< std::pair<double, double> > &a) {data_ = a;}
    ///Sets the function to be minimized
    void SetFunction(FittingFunction *a){func = a;};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetInitialGuesses(const std::vector< std::pair<double, double> > &a);
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetMaxIterations(const double &a) {maxIter_ = a;}
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetTolerance(const double &a) {tolerance_ = a;}
private:
    unsigned int maxIter_;///< The Maximum Number of Iterations
    unsigned int numIter_;///< The Number of iterations that it took to minimize
    double tolerance_; ///< The stopping criteria for the fitting.
    double currentMin_; ///< The current minimum of the data.
    std::vector<std::pair<double,double> > data_; ///< The data that we will be minimizing to
    std::vector<double> results_; ///< The results of the minimization

    FittingFunction *func; ///< The function that will be used as the comparison to the data

    std::mt19937_64 *engine_; ///< The Mersenne 64-bit RNG engine
    std::vector<std::normal_distribution<> *> distList_; ///< Vector containing the RNG distributions
};
#endif //__MONTEFIT_HPP__
