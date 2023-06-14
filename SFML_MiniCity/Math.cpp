#include "Math.h"

int clampInt(int min, int max, int value) {
	if (value < min) {
		return(min);
	}
	if (value > max) {
		return(max);
	}
	return(value);
}

float clampFloat(float min, float max, float value) {
	if (value < min) {
		return(min);
	}
	if (value > max) {
		return(max);
	}
	return(value);
}

int getRandomIntRange(int min, int max) {
	int r = min + rand() % (max - min + 1);
	return(r);
}

int getRandomIntValue(vector<int> values) {
	int r = values[getRandomIntRange(0, values.size() - 1)];
	return(r);
}

float convertTimeToLerpT(float min, float max){
	return min / max;
}

float lerp(float a, float b, float t) {
	return b + (a - b) * t;
};

float getLerpQuadraticEaseOut(float t) {
	t = 1.0 - (1.0 - t) * (1.0 - t);
	return t;
};

float getLerpBounceOut(float t) {
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (t < 1.0 / d1) {
		t = n1 * t * t;
	}
	if (t < 2.0 / d1) {
		t -= 1.5 / d1;
		return n1 * t * t + 0.75;
	}
	if (t < 2.5 / d1) {
		t -= 2.25 / d1;
		return n1 * t * t + 0.9375;
	}
	
	t -= 2.625 / d1;
	return n1 * t * t + 0.984375;
};


int getOffsetSprites(int spriteCount, int spriteSize, int padding) {
	return ((spriteSize + padding )* spriteCount - padding ) / 2 - padding;
}