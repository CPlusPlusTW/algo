#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class SlidingWindow {
public:
    static int calcArraySum (std::vector<int> const& d, int const& start, int const& end) {
        int sum = 0;
        for (auto i=start; i<end; i++) {
            sum += d.at(i);
        }
        return sum;
    }
    int findMinLen (int const& target, vector<int> const& nums) {
        if (nums.empty()) { return 0; }
        int left = 0, right = 0, length = INT_MAX, mask;
        while (right < nums.size()) {
            right++;
            while (calcArraySum(nums, left, right) >= target) {
                mask = right - left;
                if (length == mask) {
                    saveResult(false, left, right);
                } else if (length > mask) {
                    length = mask;
                    saveResult(true, left, right);
                }
                left++;
            }
        }
        return length == INT_MAX ? 0 : length;
    }
    void saveResult (bool const& clear, int const& left, int const& right) {
        if (clear) {
            candidate.clear();
        }
        candidate.push_back(left);
        candidate.push_back(right);
    }
    void printResult (int const& length, vector<int> const& nums) {
        for (auto i=0; i<candidate.size(); i=i+2) {
            int const& left = candidate.at(i);
            int const& right = candidate.at(i+1);
            for (auto it=nums.begin()+left; it!=nums.begin()+right; it++) {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        }
    }
private:
    std::vector<int> candidate;
};

int main(int argc, char** argv)
{
    int target = 0;
    std::string filename;
    if (argc == 3) {
        target = atoi(argv[1]);
        filename = std::string(argv[2]);
    }

    std::vector<int> v;
    /*v.push_back(3);
    v.push_back(17);
    v.push_back(42);
    v.push_back(1);
    v.push_back(26);
    v.push_back(8);
    v.push_back(0);
    v.push_back(63);*/

    if (!filename.empty()) {
        std::ifstream ifs(filename.data(), std::ios::in);
        if (ifs.is_open()) {
            int i;
            while (ifs >> i) {
                v.push_back(i);
            }
            ifs.close();
        }
    }

    SlidingWindow s;
    auto start = chrono::high_resolution_clock::now();
    auto len = s.findMinLen(target, v);
    auto end = chrono::high_resolution_clock::now();

    s.printResult(len, v);
    std::cout << "duration: " << chrono::duration <double, nano> (end-start).count() << " ns" << endl;
}
