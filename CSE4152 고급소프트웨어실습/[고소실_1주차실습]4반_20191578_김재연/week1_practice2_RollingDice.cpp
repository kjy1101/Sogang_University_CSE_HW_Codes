#include "pch.h"
#include "tipsware.h"
#include "time.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <stdlib.h>

NOT_USE_MESSAGE

#define MAX_TRY 10000

int main()
{
	//srand(time(NULL));

	SelectPenObject(RGB(0, 0, 0));

	int hit = 0;
	int miss = 0;
	float relProb = 5.0 / 36.0;
	float prob = 0;
	
	// TODO 
	int random1, random2;
	float hit_num = 0.0;

	for (int i = 0; i < MAX_TRY; i++) {
		random1 = (rand() % 6) + 1;
		random2 = (rand() % 6) + 1;
		if (random1 + random2 == 8) {
			TextOut(120 * (i / 20), 20 * (i % 20), "try %d: %d,%d (hit!)", i, random1, random2);
			hit_num++;
		}
		else {
			TextOut(120 * (i / 20), 20 * (i % 20), "try %d: %d,%d", i, random1, random2);
		}
	}

	//TextOut(120 * (0 / 20), 20 * (0 % 20), "try %d: %d,%d (hit!)", 0 + 1, 6, 2);
	//TextOut(120 * (1 / 20), 20 * (1 % 20), "try %d: %d,%d", 0 + 2, 6, 6);
	
	//

	SetTextColor(RGB(128, 0, 0));
	// 실제 주사위 값
	TextOut(0, 420, "실제 값: %.6f", relProb);
	// 계산된 값
	prob = hit_num / MAX_TRY;
	TextOut(0, 440, "계산된 값: %.6f", prob);

	ShowDisplay();

	return 0;
}
