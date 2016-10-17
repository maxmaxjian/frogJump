#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

class solution {
  public:
    bool canCross(const std::vector<int> & stones) {
        assert(stones[0] == 0 && stones[1] == 1);
        std::vector<int> start{0,1};
        std::vector<std::vector<int>> paths = pathsFrom(stones, start);

        std::vector<std::vector<int>> result;
        for (auto path : paths) {
            if (path.back() == stones.back()) {
                result.push_back(path);
            }
            std::for_each(path.begin(), path.end(), [](int i){std::cout<<i<<" ";});
            std::cout << std::endl;
        }
        return !result.empty();
    }

  private:
    std::vector<std::vector<int>> pathsFrom(const std::vector<int> & stones, const std::vector<int> & curr) {
        // std::cout << "prev = " << curr[curr.size()-2] << ", curr = " << curr.back() << std::endl;
        std::vector<std::vector<int>> result;
        if (curr.back() == stones.back())
            result.push_back(curr);
        else {
            std::vector<int> next = getNext(stones, curr);
            // std::for_each(next.begin(), next.end(), [](int i){std::cout<<i<<" ";});
            // std::cout << std::endl;
            if (next.empty())
                result.push_back(curr);
            else {
                for (auto nx : next) {
                    // std::cout << "nx = " << nx << std::endl;
                    auto tmp = curr;
                    tmp.push_back(nx);
                    auto temp = pathsFrom(stones, tmp);
                    for (auto t : temp)
                        result.push_back(t);
                }
            }
        }
        return result;
    }

    std::vector<int> getNext(const std::vector<int> & stones, const std::vector<int> & path) {
        int prevJump = path.back()-path[path.size()-2];

        std::vector<int> currJump{prevJump-1, prevJump, prevJump+1};
        std::vector<int> next;
        for (auto jump : currJump) {
            if (jump > 0 && std::find(stones.begin(), stones.end(), path.back()+jump) != stones.end())
                next.push_back(path.back()+jump);
        }
        return next;
    }
};

int main() {
    std::vector<int> stones{0,1,3,5,6,8,12,17};
    // std::vector<int> stones{0,1,2,3,4,8,9,11};

    solution soln;
    bool cross = soln.canCross(stones);
    std::cout << std::boolalpha
              << cross << std::endl;
}
