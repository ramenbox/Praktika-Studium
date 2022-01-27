#pragma once

class CKomplex {
private:
	double Re, Im;

public:
	CKomplex();
	CKomplex(double a, double b);
	CKomplex(double phi);

	void setRe(double Re) { this->Re = Re; }
	void setIm(double Im) { this->Im = Im; }
	double getRe(void) { return Re; }
	double getIm(void) { return Im; }

	void operator+= (const CKomplex& a);
	void operator*= (const double& a);

	friend CKomplex operator+ (const CKomplex& a, const CKomplex& b);
	friend CKomplex operator* (const CKomplex& a, const CKomplex& b);

	double abs(void);
};