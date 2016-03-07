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

class MonteFit {
public:
    /** Default Constructor */
    MonteFit ();
    /** Default Destructor */
    ~MonteFit();

    /** \return amp_ */
    double GetAmplitude(void){return(amp_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetAmplitude(const double &a) {amp_ = a;}

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

    /** \return beta_ */
    double GetSigma(void){return(beta_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetSigma(const double &a) {beta_ = a;};

    /** \return phase_ */
    double GetPhase(void){return(phase_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetPhase(const double &a) {phase_ = a;};

    /** \return gamma_ */
    double GetDecayConst(void){return(gamma_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetDecayConst(const double &a) {gamma_ = a;};

    unsigned int GetNumIterations(void){return(numIter_);};

    double Gaussian(const double &t, const double &sigma,
                    const double &amp, const double &phase);
    
    void Minimize(void);
private:
    unsigned int maxIter_, numIter_;
    double amp_, beta_, gamma_, phase_, tolerance_;
    double currentMin_;
    std::vector<std::pair<double,double> > data_;

    double rAmp_, rBeta_, rPhase_;

    double GenerateParameterSets(void);
    
    std::mt19937_64 *engine_;
    std::uniform_real_distribution<double> *dist_;
};
#endif //__MONTEFIT_HPP__
