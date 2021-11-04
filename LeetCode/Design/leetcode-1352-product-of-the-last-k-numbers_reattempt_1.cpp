// LeetCode-1352: https://leetcode.com/problems/product-of-the-last-k-numbers/
// CodeAndNotes: https://medium.com/@codeandnotes/leetcode-1352-product-of-the-last-k-numbers-77ad392098df

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_LEN 40000

class ProductOfNumbers {
   private:
    bool debug;
    int endIdx;
    vector<long long int> prods;

    vector<int> getProds() {
        this->debug = false;

        int crrLen = this->endIdx + 1;
        if (crrLen <= 0) {
            return {};
        }

        vector<int> prods(this->prods.begin(), (this->prods.begin() + this->endIdx + 1));
        return prods;
    }

    void setDebug(bool debug) {
        this->debug = debug;
    }

   public:
    friend class ProductOfNumbersTest;

    ProductOfNumbers() {
        this->endIdx = -1;

        vector<long long int> prods(MAX_LEN, -1);
        this->prods = prods;
    }

    void add(int num) {
        if (num == 0) {
            // reset beginIdx & endIdx (all existing running prods to be discarded)
            this->endIdx = -1;
            // and return
            return;
        }

        // increment endIdx
        this->endIdx++;

        int newLen = this->endIdx + 1;
        if (newLen == 1) {
            // if just 1 element, set that as product
            this->prods[this->endIdx] = num;
        } else {
            // otherwise calculate and store running product
            // (this could've resulted in integer overflow, but test cases are designed such that it doesnt)
            this->prods[this->endIdx] = this->prods[this->endIdx - 1] * num;
        }
    }

    int getProduct(int k) {
        if (k <= 0) {
            return 0;
        }
        int crrLen = this->endIdx + 1;

        int prod = 0;
        if (k > crrLen) {
            // some zero exists within last k nums
            prod = 0;
        } else if (k == crrLen) {
            // the current running product is the result
            prod = (int)this->prods[this->endIdx];
        } else {
            // product of range (last k numbers) can be calculated by simple arithmetic divsion
            long long int prevProd = this->prods[this->endIdx - k];
            long long int crrProd = this->prods[this->endIdx];
            prod = (int)(crrProd / prevProd);
        }

        return prod;
    }
};

class ProductOfNumbersTest {
   public:
    void testAdd() {
        ProductOfNumbers pon = ProductOfNumbers();
        vector<int> prodsOutExpected, prodsOutComputed;

        prodsOutExpected = {};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);

        pon.add(12);

        prodsOutExpected = {12};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);

        pon.add(1);

        prodsOutExpected = {12, 12};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);

        pon.add(3);

        prodsOutExpected = {12, 12, 36};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);

        pon.add(0);

        prodsOutExpected = {};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);

        pon.add(9);

        prodsOutExpected = {9};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
    }

    void testGetProduct() {
        ProductOfNumbers pon = ProductOfNumbers();
        int kIn;
        vector<int> prodsOutExpected, prodsOutComputed;
        int prodOutExpected, prodOutComputed;

        kIn = 0;
        prodsOutExpected = {};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 0;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 3;
        prodsOutExpected = {};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 0;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        pon.add(2);

        kIn = 3;
        prodsOutExpected = {2};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 0;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 0;
        prodsOutExpected = {2};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 0;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 1;
        prodsOutExpected = {2};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 2;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        pon.add(6);

        kIn = 1;
        prodsOutExpected = {2, 12};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 6;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 2;
        prodsOutExpected = {2, 12};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 12;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 3;
        prodsOutExpected = {2, 12};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 0;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        pon.add(1);

        kIn = 3;
        prodsOutExpected = {2, 12, 12};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 12;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        pon.add(3);

        kIn = 5;
        prodsOutExpected = {2, 12, 12, 36};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 0;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 4;
        prodsOutExpected = {2, 12, 12, 36};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 36;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 3;
        prodsOutExpected = {2, 12, 12, 36};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 18;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 2;
        prodsOutExpected = {2, 12, 12, 36};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 3;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 1;
        prodsOutExpected = {2, 12, 12, 36};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 3;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        pon.add(5);

        kIn = 5;
        prodsOutExpected = {2, 12, 12, 36, 180};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 180;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        pon.add(4);

        kIn = 5;
        prodsOutExpected = {2, 12, 12, 36, 180, 720};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 360;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        // reset
        pon.add(0);

        // LC sample test case
        pon.add(3);
        pon.add(0);
        pon.add(2);
        pon.add(5);
        pon.add(4);

        kIn = 2;
        prodsOutExpected = {2, 10, 40};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 20;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 3;
        prodsOutExpected = {2, 10, 40};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 40;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        kIn = 4;
        prodsOutExpected = {2, 10, 40};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 0;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);

        pon.add(8);

        kIn = 2;
        prodsOutExpected = {2, 10, 40, 320};
        prodsOutComputed = pon.getProds();
        assert(prodsOutExpected == prodsOutComputed);
        prodOutExpected = 32;
        prodOutComputed = pon.getProduct(kIn);
        assert(prodOutExpected == prodOutComputed);
    }
};

int main() {
    ProductOfNumbersTest ponTest = ProductOfNumbersTest();

    ponTest.testAdd();
    ponTest.testGetProduct();

    return 0;
}

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */