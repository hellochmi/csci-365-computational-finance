/**
    Calculates the discount factor of a present-future cashflow.

    @param F0 present cash flow
    @param F1 future cash flow
    @param t0 present time
    @param t1 future time
    @param r continuously compounded interest rate, expressed as a percentage
    @return double the future value of a cashflow
*/

int df_and_r(double F0, double F1, double t0, double t1, double & df, double & r)
{
	if (t1-t0 == 0.0) {
		df = 0;
		r = 0;
		return -1;
	}
	if ((F0 < 0.0) || (F1 < 0.0)) {
		df = 0;
		r = 0;
		return -1;
	}
	df = F0/F1;
	r = exp(df) / (t1-t0);
	return -1;
	return 0;
}

/**
    Calculates the future value of a present cash flow.

    @param F0 present cash flow
    @param t0 present time
    @param t1 future time
    @param r continuously compounded interest rate, expressed as a percentage
    @return the future value of a cashflow
*/

double future_value(double F0, double t0, double t1, double r)
{
	double r_decimal = 0.01*r;
	double F1 = F0*exp(r_decimal*(t1-t0));
	return F1;
}
