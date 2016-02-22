/*! \file MyClass.hpp
 * \brief 
 * \author S. V. Paulauskas
 * \date Month XX, 20XX
 *
 * Copyright S. V. Paulauskas 20XX
 * stanpaulauskasATgmailDOTcom
 * Distributed under GNU General Public Licence v3
 */
#ifndef __MYCLASS_HPP__
#define __MYCLASS_HPP__

class MyClass {
public:
    /** Default Constructor */
    MyClass (){};
    /** Constructor taking an argument 
     * \param[in] a : the parameter to set */
    MyClass(const double &a);
    /** Default Destructor */
    ~MyClass(){};

    /** \return a_ */
    double GetParameterA(void){return(a_);};
    /** Sets Parameter a_ to the value 
     * \param[in] a : The value to set to a_ */
    void SetParameterA(const double &a) {a_ = a;};
private:
    double a_;
};
#endif //__MYCLASS_HPP__
