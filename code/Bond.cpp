
class Bond
{
	public:
		Bond(double T, double F, double c=0, int freq=2);
		~Bond();
		// public methods
		void set_flat_coupons(double c);
		int set_coupons(std::vector<double> & c);
		int FV_duration(double t0, double y, // skip for Summer 2018
		double &B,
		double &Macaulay_duration,
		double &modified_duration) const;
		int yield(double B_target, double tol, int max_iter, double t0,
		double & y, int & num_iter) const;
		int FairValue(double t0, double y) const;
		double maturity() const { return T_maturity; }
	
	private:
		// private data
		double Face;
		double T_maturity;
		int cpn_freq;
		int num_coupon_periods;
		std::vector<double> coupons;
};

Bond::Bond(double T, double F, double c, int freq){
	if (F >= 0) Face = F;
	if (freq >= 1) cpn_freq = freq;
	const double tol = 1.0e-6;
	num_coupon_periods = int(cpn_freq*T + tol);
	if (num_coupon_periods >= 0)T_maturity = num_coupon_periods / cpn_freq;
	if (c < 0) c = 0;
	if (num_coupon_periods > 0) coupons.resize(num_coupon_periods, c);
};

Bond::~Bond(){
	coupons.clear();
	num_coupon_periods = 0;
};

int Bond::set_coupons(std::vector<double> & c){
	if (c.size() < num_coupon_periods) return 1;
	for (int i = 0; i < num_coupon_periods - 1; i++){
		if (c[i] <= 0.0) coupons[i] = 0.0;
		else coupons[i] = c[i];
	};
	return 0;
};

void Bond::set_flat_coupons(double c){
	if (c < 0.0) c = 0.0;
	for (int i = 0; i < num_coupon_periods - 1; i++){
		coupons[i] = c;
	};
};

int Bond::FairValue(double t0, double y) const{
	int B = 0;
	if (num_coupon_periods <= 0 || t0 >= T_maturity) return 1;
	double y_decimal = 0.01 * y;
	int f = cpn_freq;
	int n = num_coupon_periods;
	const double tol = 1.0e-6;

	for (int i = 1; i <= n; i++){
		int t_i = double(i)/double(cpn_freq);
		const double tol = 1.0e-6;
		if (t_i >= t0 + tol){
			B += (coupons[i] / f) / pow((1 + (y/f)), f*(t_i - t0));
			cout<<B<<endl;
		}
	}
	return 0;
}