#include <vector>
#include <iostream>

using namespace std;
//每个孩子都有一个满足度 grid，每个饼干都有一个大小 size，只有饼干的大小大于等于一个孩子的满足度，该孩子才会获得满足。求解最多可以获得满足的孩子数量ii。
//因为满足度最小的孩子最容易得到满足，所以先满足满足度最小的孩子。
void isdf()
{
}
int findContentNum(const std::vector<int> &childVec, const std::vector<int> &foodVec)
{
    if (childVec.empty() || foodVec.empty())
        return 0;
    auto cIdx = 0, fIdx = 0;
    while (cIdx < childVec.size() && fIdx < foodVec.size())
    {
        if (childVec[cIdx] <= foodVec[fIdx])
        {
            ++cIdx;
        }
        ++fIdx;
    }
    return cIdx;
}
int main()
{

    std::vector<int> child = {1, 2, 4, 6};
    std::vector<int> food = {2, 4, 6};

    //假设vec中从小到大,如果有一个孩子没有满足，之后的也不会满足了
    cout << "123" << endl;
    cout << findContentNum(child, food) << endl;
    return 0;
}