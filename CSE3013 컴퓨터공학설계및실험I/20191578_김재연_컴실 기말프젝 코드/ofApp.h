#pragma once

#include "ofMain.h"
#define X_MAX 1024	//ȭ�鿡 ǥ�� ������ x��ǥ�� �ִ밪
#define Y_MAX 728	//ȭ�鿡 ǥ�� ������ y��ǥ�� �ִ밪
#define MAX_ELEMENTS 1000000	//min heap�� �����ϴ� ���ҵ��� �ִ� ����


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
	int num_of_line=0, num_of_dot;	//������ ������ ���� ������ ����
	float dot_diameter;
	int *Line_x1_array;				//������ x1 ��ǥ�� �����ϴ� �迭
	int *Line_y1_array;				//������ y1 ��ǥ�� �����ϴ� �迭
	int *Line_x2_array;				//������ x2 ��ǥ�� �����ϴ� �迭
	int *Line_y2_array;				//������ y2 ��ǥ�� �����ϴ� �迭
	int *Dot_x1_array;				//���� x1 ��ǥ�� �����ϴ� �迭
	int *Dot_y1_array;				//���� y1 ��ǥ�� �����ϴ� �迭
	int *Dot_r_array;				//���� �������� �����ϴ� �迭
	int water_dot = 0;				//���� ������ ���� ���° �ε����� �ִ��� ����

	//waterline related variables
	int path_x[100] = { 0 };		//�ֹ����� �̵��ϴ� ����� x��ǥ�� �����ϴ� �迭
	int path_y[100] = { 0 };		//�ֹ����� �̵��ϴ� ����� y��ǥ�� �����ϴ� �迭
	int path_idx = 0;				//�ֹ����� �̵��ϴ� ��ι迭�� ���� ����Ű�� �ε���
	int water_flag = 0;				//�ֹ����� �׸��� ���� �����ϴ� flag
	int picked_line_idx = 0;		//���õ� ������ �ε���
	double slope[100] = { 0 };		//�ֹ����� �̵��ϴ� ����� ��縦 �����ϴ� �迭
	int slope_idx = 0;				//�ֹ����� �̵��ϴ� ����� ���迭 ���� ����Ű�� �ε���

	//waterline print related variables
	int idx1 = 1; //path idx
	int idx2 = 0; //slope idx

	double a = -1, b = -1;			//�ֹ����� ��ġ�� �׸��� ���� x, y��ǥ�� �����صδ� ����
	double c = -1, d = -1;			//a, b�� �ֹ����� �Ӹ�
	double e = -1, f = -1;			//�������� �ֹ����� ����
	double g = -1, h = -1;
	double i = -1, j = -1;

	/* WaterFall-related member functions */

	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.

	void SelectWaterDot();				//���� ���� ���� ���� �������ִ� �Լ�
	struct element{						//���� ������ ���� ����ü
		int x, y, r, idx;				//x�� x��ǥ, y�� y��ǥ, r�� ������, idx�� ���° �ε���
	};
	element min_heap[MAX_ELEMENTS];		//min heap�� ������ element�� �迭
	int min_n = 0;						//min heap�� �ִ� ���ҵ��� ����
	void insert_min_heap(element item);	//min heap�� ���Ҹ� �����ϴ� �Լ�
};
