// LeetCode-2070: https://leetcode.com/problems/most-beautiful-item-for-each-query/description/

#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Item {
public:
    int price;
    int beauty;

    Item(int price, int beauty) {
        this->price = price;
        this->beauty = beauty;
    }
};

class Solution {
private:
    vector<Item> convertToItemVec(vector<vector<int> >& vecVec) {
        int len = vecVec.size();
        vector<Item> items;
        for (auto& vec: vecVec) {
            items.push_back(Item(vec[0], vec[1]));
        }
        return items;
    }

    void sortItemVec(vector<Item>& items) {
        sort(items.begin(), items.end(), [](const Item& left, const Item& right) {
            if (left.price == right.price) {
                return (left.beauty < right.beauty);
            }
            return (left.price < right.price);
        });
    }

    map<int, int> buildItemPriceMaxBeautyBoundMap(vector<Item>& items) {
        int len = items.size();

        map<int, int> priceMaxBeautyBoundMap;
        int crrMaxBeauty = 0;
        for (int i = 0; i < len; i++) {
            int crrPrice = items[i].price;
            crrMaxBeauty = max(crrMaxBeauty, items[i].beauty);

            while ((i < len) && (items[i].price == crrPrice)) {
                crrMaxBeauty = max(crrMaxBeauty, items[i].beauty);
                i++;
            }

            priceMaxBeautyBoundMap[crrPrice] = crrMaxBeauty;

            if (i < len) {
                i--;
            }
        }

        return priceMaxBeautyBoundMap;
    }

    inline int findMaxBeauty(map<int, int>& priceMaxBeautyBoundMap, int price) {
        auto it = priceMaxBeautyBoundMap.lower_bound(price);
        if (it->first == price) {
            return priceMaxBeautyBoundMap[price];
        }

        if (it == priceMaxBeautyBoundMap.begin()) {
            return 0;
        }

        it--;
        return it->second;
    }

public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        vector<Item> itemVec = convertToItemVec(items);
        sortItemVec(itemVec);

        map<int, int> priceMaxBeautyBoundMap = buildItemPriceMaxBeautyBoundMap(itemVec);

        int len = queries.size();
        vector<int> results(len, 0);

        for (int i = 0; i < len; i++) {
            results[i] = findMaxBeauty(priceMaxBeautyBoundMap, queries[i]);
        }

        return results;
    }
};
