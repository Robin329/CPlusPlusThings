#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// test 1
typedef struct {
	string str;
	float f;
	double d;
	int i;
} init_struct;

// test 2
struct QuoteField {
	//tag==10028 报价时间
	std::string SCQuoteTime;
	//tag==132
	double bidPx_s;
	//tag==133
	double offerPx_s;
	//tag==134
	int bidsize;
	//tag==135
	int offersize;
};

int main()
{
	// test 1
	init_struct init;
	memset(&init, 0, sizeof(init));
	for (int i = 0; i < 10; ++i)
		cout << init.str << ", " << init.f << ", " << init.d << ", "
		     << init.i << endl;

	// test 2

	QuoteField quoteField;
	memset(&quoteField, 0, sizeof(QuoteField));
	printf("this is error example!\n");
	cout << quoteField.SCQuoteTime << endl;
	quoteField.SCQuoteTime = "2020-02-30 16:16:16";
	// quoteField.offersize = 100;
	// quoteField.offerPx_s = 3.1415;
	return 0;
}