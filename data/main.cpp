#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>
#include <random>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;

int main() {
	
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> dist(0, 99);
	
    ofstream ofs;
    ofs.open("test.txt");
    if (ofs.is_open()) {
		for (int i=0; i<1000; i++) {
			ofs << dist(e) << "\n";
		}
        ofs.close();
    }
	
    std::vector<int> nums;
    std::ifstream ifs("test.txt", std::ios::in);
    if (ifs.is_open()) {
		int i;
		while (ifs >> i) {
			nums.push_back(i);
		}
        ifs.close();
    }

	for(int n : nums) {
		cout << n << " ";
	}
	cout << "\n";
}
