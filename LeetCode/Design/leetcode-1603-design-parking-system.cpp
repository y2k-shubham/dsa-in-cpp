// LeetCode-1603: https://leetcode.com/problems/design-parking-system/
// Stupid question; please skip

class ParkingSystem {
private:
    int big;
    int medium;
    int small;
    
public:
    ParkingSystem(int big, int medium, int small) {
        this->big = big;
        this->medium = medium;
        this->small = small;
    }
    
    bool addCar(int carType) {
        switch (carType) {
            case 1:
                // big
                if (this->big > 0) {
                    this->big -= 1;
                    return true;
                } else {
                    return false;
                }
                break;
            
            case 2:
                // medium
                if (this->medium > 0) {
                    this->medium -= 1;
                    return true;
                } else {
                    return false;
                }
                break;
                
            case 3:
                // small
                if (this->small > 0) {
                    this->small -= 1;
                    return true;
                } else {
                    return false;
                }
                break;
                
            default:
                return INT_MIN;
                break;
        }
    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
