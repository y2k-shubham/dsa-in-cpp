// LeetCode-213: https://leetcode.com/problems/house-robber-ii/
// this problem adds twist on LeetCode-198: https://leetcode.com/problems/house-robber/

/**
 * @file leetcode-213-house-robber-ii.cpp
 * @author y2k-shubham
 * @brief (make sure you thoroughly understand soln of LeetCode-198 before diving into this one)
 * we can still adopt that two sum approach: an inclusive sum (that includes current element)
 * and an exclusive sum, but on top of that we must ensure that both first & last elements
 * dont get included in the final answer
 * 
 * - clearly, the first element may be included in either incSum or the excSum (or both, since
 * current excSum is itself max of previous inc & exc sums).
 * - so then as we move through the array, we ought to carry this information (whether
 * previous incSum or excSum includes first element or not)
 * 
 * - now in the beginning (when only first element is taken into consideration), we already
 * know that our incSum includes the first element & excSum doesnt
 * - when computing the above two attributes for 2nd element, we can say that incSum for
 * second element does NOT include 1st element; while excSum for 2nd element may or
 * may not include the first element, depending on whether it comprised of previous (first
 * element's incSum or excSum)
 * 
 * - similarly we can keep passing this info until the end
 * - as for the final element, we can include it in the answer, only if prev excSum did NOT
 * include the first element.
 *    - however upon second thought, this sounds bizzare -> the last
 * element's value alone could potentially be bigger than the rest of them put together, then
 * we simply can't ignore it
 * - so the workaround (correct soln) is that we perform the aforementioned computation twice,
 *    - once from front of array to end
 *    - and then from end of array to front
 *   then the bigger of the two results will be our final answer
 * 
 * @version 0.1
 * @date 2020-11-22
 * 
 * @copyright Copyright (c) 2020
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

// LC submission: speed: 100 %tile, memory: 96 %tile
int robUtil(vector<int>& nums) {
    int len = nums.size();

    int prevIncSum = nums[0];
    int prevExcSum = 0;

    bool prevIncHasFirstEle = true;
    bool prevExcHasFirstEle = false;

    for (int i = 1; i < len - 1; i++) {
        int crrIncSum = prevExcSum + nums[i];
        bool crrIncHasFirstEle = prevExcHasFirstEle;

        int crrExcSum;
        bool crrExcHasFirstEle;
        if (prevExcSum > prevIncSum) {
            crrExcSum = prevExcSum;
            crrExcHasFirstEle = prevExcHasFirstEle;
        } else {
            crrExcSum = prevIncSum;
            crrExcHasFirstEle = prevIncHasFirstEle;
        }

        prevIncSum = crrIncSum;
        prevExcSum = crrExcSum;

        prevIncHasFirstEle = crrIncHasFirstEle;
        prevExcHasFirstEle = crrExcHasFirstEle;
    }

    if (prevExcHasFirstEle) {
        // cant include last ele at all
        return max(prevExcSum, prevIncSum);
    } else {
        // can include last ele also
        return max((prevExcSum + nums[len - 1]), prevIncSum);
    }
}

int rob(vector<int>& nums) {
    int res1 = robUtil(nums);

    reverse(nums.begin(), nums.end());
    int res2 = robUtil(nums);

    return max(res1, res2);
}
