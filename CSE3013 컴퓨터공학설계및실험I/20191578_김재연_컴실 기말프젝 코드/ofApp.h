#pragma once

#include "ofMain.h"
#define X_MAX 1024	//화면에 표시 가능한 x좌표의 최대값
#define Y_MAX 728	//화면에 표시 가능한 y좌표의 최대값
#define MAX_ELEMENTS 1000000	//min heap을 구성하는 원소들의 최대 개수


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
	/* WaterFall-related member variables Regions */

	// flag variables
	int draw_flag;
	int load_flag;

	// Line segment and dot related variables
	int num_of_line=0, num_of_dot;	//선분의 개수와 점의 개수를 저장
	float dot_diameter;
	int *Line_x1_array;				//선분의 x1 좌표를 저장하는 배열
	int *Line_y1_array;				//선분의 y1 좌표를 저장하는 배열
	int *Line_x2_array;				//선분의 x2 좌표를 저장하는 배열
	int *Line_y2_array;				//선분의 y2 좌표를 저장하는 배열
	int *Dot_x1_array;				//점의 x1 좌표를 저장하는 배열
	int *Dot_y1_array;				//점의 y1 좌표를 저장하는 배열
	int *Dot_r_array;				//점의 반지름을 저장하는 배열
	int water_dot = 0;				//물이 나오는 점이 몇번째 인덱스에 있는지 저장

	//waterline related variables
	int path_x[100] = { 0 };		//애벌레가 이동하는 경로의 x좌표를 저장하는 배열
	int path_y[100] = { 0 };		//애벌레가 이동하는 경로의 y좌표를 저장하는 배열
	int path_idx = 0;				//애벌레가 이동하는 경로배열의 값을 가리키는 인덱스
	int water_flag = 0;				//애벌레를 그릴지 말지 결정하는 flag
	int picked_line_idx = 0;		//선택된 선분의 인덱스
	double slope[100] = { 0 };		//애벌레가 이동하는 경로의 경사를 저장하는 배열
	int slope_idx = 0;				//애벌레가 이동하는 경로의 경사배열 값을 가리키는 인덱스

	//waterline print related variables
	int idx1 = 1; //path idx
	int idx2 = 0; //slope idx

	double a = -1, b = -1;			//애벌레의 위치를 그리기 위한 x, y좌표를 저장해두는 변수
	double c = -1, d = -1;			//a, b는 애벌레의 머리
	double e = -1, f = -1;			//나머지는 애벌레의 몸통
	double g = -1, h = -1;
	double i = -1, j = -1;

	/* WaterFall-related member functions */

	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.

	void SelectWaterDot();				//다음 물이 나올 점을 선택해주는 함수
	struct element{						//점의 정보를 담을 구조체
		int x, y, r, idx;				//x는 x좌표, y는 y좌표, r은 반지름, idx는 몇번째 인덱스
	};
	element min_heap[MAX_ELEMENTS];		//min heap을 저장할 element형 배열
	int min_n = 0;						//min heap에 있는 원소들의 개수
	void insert_min_heap(element item);	//min heap에 원소를 삽입하는 함수
};
