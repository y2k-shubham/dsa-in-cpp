#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <stdbool.h>

using namespace std;

int c;
int temp;
int T;
int i;
string FRONT;
string BACK;
string LEFT;
string RIGHT;
string TOP;
string BOTTOM;

inline void scanStringFRONT() {
	FRONT = "";
	temp = getchar();

	while ((temp < 'a') || (temp > 'z')) {
		temp = getchar();
	}

	while ((temp >= 'a') && (temp <= 'z')) {
		FRONT += (char) temp;
		temp = getchar();
	}
}

inline void scanStringBACK() {
	BACK = "";
	temp = getchar();

	while ((temp < 'a') || (temp > 'z')) {
		temp = getchar();
	}

	while ((temp >= 'a') && (temp <= 'z')) {
		BACK += (char) temp;
		temp = getchar();
	}
}

inline void scanStringLEFT() {
	LEFT = "";
	temp = getchar();

	while ((temp < 'a') || (temp > 'z')) {
		temp = getchar();
	}

	while ((temp >= 'a') && (temp <= 'z')) {
		LEFT += (char) temp;
		temp = getchar();
	}
}

inline void scanStringRIGHT() {
	RIGHT = "";
	temp = getchar();

	while ((temp < 'a') || (temp > 'z')) {
		temp = getchar();
	}

	while ((temp >= 'a') && (temp <= 'z')) {
		RIGHT += (char) temp;
		temp = getchar();
	}
}

inline void scanStringTOP() {
	TOP = "";
	temp = getchar();

	while ((temp < 'a') || (temp > 'z')) {
		temp = getchar();
	}

	while ((temp >= 'a') && (temp <= 'z')) {
		TOP += (char) temp;
		temp = getchar();
	}
}

inline void scanStringBOTTOM() {
	BOTTOM = "";
	temp = getchar();

	while ((temp < 'a') || (temp > 'z')) {
		temp = getchar();
	}

	while ((temp >= 'a') && (temp <= 'z')) {
		BOTTOM += (char) temp;
		temp = getchar();
	}
}

bool are_same(string str_1, string str_2) {
    if ((str_2[0] == str_2[0]) && (str_1[2] == str_2[2])) {
        return true;
    } else {
        return false;
    }
}

int main() {
    scanf("%d", &T);

	for (i = 1; i <= T; i++) {
		scanStringFRONT();
        scanStringBACK();
        scanStringLEFT();
        scanStringRIGHT();
        scanStringTOP();
        scanStringBOTTOM();

        if ((are_same(FRONT, TOP) || are_same(FRONT, BOTTOM)) && (are_same(FRONT, LEFT) || are_same(FRONT, RIGHT))) {
            printf("YES\n");
        } else if ((are_same(BACK, TOP) || are_same(BACK, BOTTOM)) && (are_same(BACK, LEFT) || are_same(BACK, RIGHT))) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
	}

	return 0;
}
