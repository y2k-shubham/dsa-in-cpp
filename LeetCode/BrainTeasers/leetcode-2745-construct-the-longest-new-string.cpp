// LeetCode-2745: https://leetcode.com/problems/construct-the-longest-new-string/

/**
 * == self editorial ==
 * observations
 * 1. AAs & BBs can't be chained sigularly as AA-AA;
 *    but they can be interleaved as AA-BB-.. indefinitely
 * 2. ABs can be self chained,
 * 3. ABs they can also be added at the end / beginning of any string
 *    for e.g. if there's a string AABB.., we can put as many ABs at it's front as we want
 *    similarly if there's a string ..AABB, then we can put as many ABs at it's end as we want
 *
 * From above observations we can develop following strategy
 * 1. start by using as many AAs & BBs as possible by interleaving themselves
 *    mathematically if x (no of AAs) < y (no of BBs), then we can
 *    use x AAs and x+1 BBs (and vice-versa)
 * 2. if x = y, we'll end up with a string having AA at one end and BB at other end
 *    otherwise we'll end up with a string having AA or BB at both ends
 * 3. regardless of which of the above two cases it is, we can still use up all ABs we are left with
 *
 * we can see that the left-over AAs or BBs can't be (and could not have been) used in any way
 */

class Solution {
public:
    int longestString(int x, int y, int z) {
        // no of AAs
        int numAAs = (x > y) ? (y + 1) : x;

        // no of BBs
        int numBBs = (x < y) ? (x + 1) : y;

        // no of ABa
        int numABs = z;

        int totalPairs = numAAs + numBBs + numABs;
        return totalPairs * 2;
    }
};
