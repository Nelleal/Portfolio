#pragma once
#include <iostream>
#include <vector>

using namespace std;

// body ---------------------------------------------------------------------------------------------------

int clampInt(int min, int max, int value);
float clampFloat(float min, float max, float value);
float convertTimeToLerpT(float min, float max);
int getRandomIntRange(int min, int max);
int getRandomIntValue(vector<int> values);

float lerp(float a, float b, float t);
float getLerpQuadraticEaseOut(float t);
float getLerpBounceOut(float t);

int getOffsetSprites(int spriteCount, int spriteSize, int padding);


