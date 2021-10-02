// LeetCode-1801: https://leetcode.com/problems/number-of-orders-in-the-backlog/

#include <cassert>
#include <cstdio>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

// priority que with custom comparator https://stackoverflow.com/a/35538318/3679900
bool buyOrderPQueComparator(pair<int, int>& p1, pair<int, int>& p2) {
    if (p1.first < p2.first) {
        return true;
    } else if (p1.first > p2.first) {
        return false;
    } else {
        return p1.second >= p2.second;
    }
}

auto comp = [](pair<int, int>& p1, pair<int, int>& p2) -> bool {
    if (p1.first > p2.first) {
        return true;
    } else if (p1.first < p2.first) {
        return false;
    } else {
        return p1.second <= p2.second;
    }
};

class Compare {
   public:
    bool operator()(pair<int, int> p1, pair<int, int> p2) {
        if (p1.first > p2.first) {
            return true;
        } else if (p1.first < p2.first) {
            return false;
        } else {
            return p1.second <= p2.second;
        }
    }
};

class Solution {
   private:
    // constants: https://stackoverflow.com/a/16310265/3679900
    static constexpr int ORDER_TYPE_BUY = 0;
    static constexpr int ORDER_TYPE_SELL = 1;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> sellOrdersQue;
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&buyOrderPQueComparator)> buyOrdersQue{buyOrderPQueComparator};

    void showVec(vector <pair <int, int> >& vec, string name) {
        printf("%s is:-\n", name.c_str());

        printf("price:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i].first);
        }
        cout << endl;

        printf("qty:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i].second);
        }
        cout << endl;
    }

    vector<pair<int, int>> getBuyOrdersQue() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&buyOrderPQueComparator)> buyOrdersQue = this->buyOrdersQue;
        if (buyOrdersQue.empty()) {
            return {};
        }

        vector<pair<int, int>> vec(buyOrdersQue.size());
        int i = 0;
        while (!buyOrdersQue.empty()) {
            vec[i++] = buyOrdersQue.top();
            buyOrdersQue.pop();
        }

        return vec;
    }

    void queSellOrder(int price, int qty) {
        this->sellOrdersQue.push({price, qty});
    }

    void queBuyOrder(int price, int qty) {
        this->buyOrdersQue.push({price, qty});
    }

    bool canExecuteOrders() {
        if (this->buyOrdersQue.empty() || this->sellOrdersQue.empty()) {
            return false;
        }

        return sellOrdersQue.top().first <= buyOrdersQue.top().first;
    }

    void executeSingleOrder() {
        pair<int, int> buyOrder = this->buyOrdersQue.top();
        this->buyOrdersQue.pop();

        pair<int, int> sellOrder = this->sellOrdersQue.top();
        this->sellOrdersQue.pop();

        int minQty = min(buyOrder.second, sellOrder.second);

        buyOrder.second -= minQty;
        if (buyOrder.second > 0) {
            this->buyOrdersQue.push(buyOrder);
        }

        sellOrder.second -= minQty;
        if (sellOrder.second > 0) {
            this->sellOrdersQue.push(sellOrder);
        }
    }

    void executeAllPossibleOrders() {
        while (canExecuteOrders()) {
            executeSingleOrder();
        }
    }

    int countPendingSellOrders() {
        int ctr = 0;

        while (!this->sellOrdersQue.empty()) {
            ctr += this->sellOrdersQue.top().second;
            this->sellOrdersQue.pop();
        }

        return ctr;
    }

    int countPendingBuyOrders() {
        int ctr = 0;

        while (!this->buyOrdersQue.empty()) {
            ctr += this->buyOrdersQue.top().second;
            this->buyOrdersQue.pop();
        }

        return ctr;
    }

   public:
    friend class SolutionTest;

    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        for (int i = 0; i < orders.size(); i++) {
            vector<int> order = orders[i];

            switch (order[2]) {
                case ORDER_TYPE_BUY:
                    queBuyOrder(order[0], order[1]);
                    break;

                case ORDER_TYPE_SELL:
                    queSellOrder(order[0], order[1]);
                    break;

                default:
                    throw std::invalid_argument("invalid order type");
            }

            // execute orders
            executeAllPossibleOrders();
        }

        return countPendingBuyOrders() + countPendingSellOrders();
    }
};

class SolutionTest {
   public:
    void testQueBuyOrder() {
        Solution soln = Solution();
        vector<pair<int, int>> vecOutExpected, vecOutComputed;

        vecOutExpected = {};
        vecOutComputed = soln.getBuyOrdersQue();
        assert(vecOutExpected == vecOutComputed);

        soln.queBuyOrder(5, 14);

        vecOutExpected = {{5, 14}};
        vecOutComputed = soln.getBuyOrdersQue();
        assert(vecOutExpected == vecOutComputed);

        soln.queBuyOrder(7, 3);

        vecOutExpected = {{7, 3}, {5, 14}};
        vecOutComputed = soln.getBuyOrdersQue();
        // soln.showVec(vecOutComputed, "buyOrder queue");
        assert(vecOutExpected == vecOutComputed);

        soln.queBuyOrder(5, 9);

        vecOutExpected = {{7, 3}, {5, 9}, {5, 14}};
        vecOutComputed = soln.getBuyOrdersQue();
        // soln.showVec(vecOutComputed, "buyOrder queue");
        assert(vecOutExpected == vecOutComputed);

        soln.queBuyOrder(6, 11);

        vecOutExpected = {{7, 3}, {6, 11}, {5, 9}, {5, 14}};
        vecOutComputed = soln.getBuyOrdersQue();
        // soln.showVec(vecOutComputed, "buyOrder queue");
        assert(vecOutExpected == vecOutComputed);

        soln.queBuyOrder(3, 2);

        vecOutExpected = {{7, 3}, {6, 11}, {5, 9}, {5, 14}, {3, 2}};
        vecOutComputed = soln.getBuyOrdersQue();
        // soln.showVec(vecOutComputed, "buyOrder queue");
        assert(vecOutExpected == vecOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testQueBuyOrder();

    return 0;
}
