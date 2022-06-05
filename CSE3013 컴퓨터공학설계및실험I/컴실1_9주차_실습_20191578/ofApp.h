#pragma once

#include "ofMain.h"
#define X_MAX 1024
#define Y_MAX 728

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
	int num_of_line=0, num_of_dot;
	float dot_diameter;
	int *Line_x1_array;
	int *Line_y1_array;
	int *Line_x2_array;
	int *Line_y2_array;
	int *Dot_x1_array;
	int *Dot_y1_array;
	int water_dot = 0;

	/* WaterFall-related member functions */

	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.

};
