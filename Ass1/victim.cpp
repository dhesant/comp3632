#include <cstdio>
#include <ctime>
using namespace std;

int main(int argc, char** argv) {
	struct tm * my_tm; //time structure
	time_t my_tt; //time variable
	time(&my_tt);
	my_tm = localtime(&my_tt);
	printf("It is now %s", asctime(my_tm));
	return 0;
}
