#include <iostream>
#include <gtest/gtest.h>
using namespace std;

//xml output file of UT result 
static const string ksTestOutputFile = "xml:UTXAConfigurationFactory_result.xml";

int main(int argc, char* argv[])
{
	testing::GTEST_FLAG(output)=ksTestOutputFile;
	testing::InitGoogleTest(&argc, argv);  

	(void)RUN_ALL_TESTS();

	cout << "Press Any Key to continue" << endl;
	char c;
	cin  >> c;

	return 0;
}