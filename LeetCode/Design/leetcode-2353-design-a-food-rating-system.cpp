// LeetCode-2353: https://leetcode.com/problems/design-a-food-rating-system/

#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <string>
#include <cassert>

using namespace std;

class FoodRatings {
private:
    unordered_map<string, map<int, set<string>>> cuisineFoodRatingMap;
    unordered_map<string, string> foodCuisineMap;
    unordered_map<string, int> foodRatingMap;

    void init(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        for (int i = 0; i < foods.size(); i++) {
            string food = foods[i];
            string cuisine = cuisines[i];
            int rating = ratings[i];

            foodCuisineMap[food] = cuisine;
            changeRating(food, rating);
        }
    }

public:
    friend class FoodRatingsTest;

    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        init(foods, cuisines, ratings);
    }

    // this 'inline' keyword drops LC runtime from 495ms to 464ms
    inline void changeRating(string food, int newRating) {
        string cuisine = foodCuisineMap[food];

        // add entry for cuisine
        if (cuisineFoodRatingMap.find(cuisine) == cuisineFoodRatingMap.end()) {
            cuisineFoodRatingMap[cuisine] = map<int, set<string>>();
        }

        // remove old rating of food
        if (foodRatingMap.find(food) != foodRatingMap.end()) {
            int oldRating = foodRatingMap[food];
            cuisineFoodRatingMap[cuisine][oldRating].erase(food);

            // important to clean up empty sets
            if (cuisineFoodRatingMap[cuisine][oldRating].empty()) {
                cuisineFoodRatingMap[cuisine].erase(oldRating);
            }
        }

        // update new rating
        cuisineFoodRatingMap[cuisine][newRating].insert(food);
        foodRatingMap[food] = newRating;
    }

    string highestRated(string cuisine) {
        return *cuisineFoodRatingMap[cuisine].rbegin()->second.begin();
    }
};

class FoodRatingsTest {
public:
    void testChangeRating() {
        vector<string> foods;
        vector<string> cuisines;
        vector<int> ratings;
        unordered_map<string, map<int, set<string>>> cuisineFoodRatingMapExpected;

        // ------ Test case 1 -------
        foods = {"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"};
        cuisines = {"korean", "japanese", "japanese", "greek", "japanese", "korean"};
        ratings = {9, 12, 8, 15, 14, 7};

        FoodRatings foodRatings1 = FoodRatings(foods, cuisines, ratings);
        cuisineFoodRatingMapExpected = {
                {"korean",   {
                                     {7,  {"bulgogi"}},
                                     {9,  {"kimchi"}}
                             }},
                {"japanese", {
                                     {8,  {"sushi"}},
                                     {12, {"miso"}},
                                     {14, {"ramen"}}
                             }},
                {"greek",    {
                                     {15, {"moussaka"}}
                             }}
        };
        assert(cuisineFoodRatingMapExpected == foodRatings1.cuisineFoodRatingMap);

        assert(foodRatings1.highestRated("korean") == "kimchi");
        assert(foodRatings1.highestRated("japanese") == "ramen");

        foodRatings1.changeRating("sushi", 16);
        cuisineFoodRatingMapExpected = {
                {"korean",   {
                                     {7,  {"bulgogi"}},
                                     {9,  {"kimchi"}}
                             }},
                {"japanese", {
                                     {12, {"miso"}},
                                     {14, {"ramen"}},
                                     {16, {"sushi"}}
                             }},
                {"greek",    {
                                     {15, {"moussaka"}}
                             }}
        };
        assert(cuisineFoodRatingMapExpected == foodRatings1.cuisineFoodRatingMap);

        assert(foodRatings1.highestRated("japanese") == "sushi");

        foodRatings1.changeRating("ramen", 16);
        cuisineFoodRatingMapExpected = {
                {"korean",   {
                                     {7,  {"bulgogi"}},
                                     {9,  {"kimchi"}}
                             }},
                {"japanese", {
                                     {12, {"miso"}},
                                     {16, {"ramen", "sushi"}}
                             }},
                {"greek",    {
                                     {15, {"moussaka"}}
                             }}
        };
        assert(cuisineFoodRatingMapExpected == foodRatings1.cuisineFoodRatingMap);
        assert(foodRatings1.highestRated("japanese") == "ramen");
    }
};

int main() {
    FoodRatingsTest foodRatingsTest = FoodRatingsTest();

    foodRatingsTest.testChangeRating();

    return 0;
}
