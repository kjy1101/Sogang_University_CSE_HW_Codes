#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

	// We still want to draw on a black background, so we need to draw
	// the background before we do anything with the brush
	ofBackground(255, 255, 255);
	ofSetLineWidth(4);

	draw_flag = 0;
	load_flag = 0;
	dot_diameter = 20.0f;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(127, 23, 31);  // Set the drawing color to brown

	// Draw shapes for ceiling and floor
	ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofSetLineWidth(5);


	ofSetLineWidth(5);

	if (draw_flag) {

		/* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
		 Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
		 */
		for (int i = 0; i < num_of_line; i++) {
			ofDrawLine(Line_x1_array[i], Line_y1_array[i], Line_x2_array[i], Line_y2_array[i]);
		}
		
		for (int i = 0; i < num_of_dot; i++) {
			if (i == water_dot) {
				ofSetColor(255, 0, 0);
				ofDrawCircle(Dot_x1_array[i], Dot_y1_array[i], 10);
			}
			else {
				ofSetColor(0);
				ofDrawCircle(Dot_x1_array[i], Dot_y1_array[i], 10);
			}
		}
		 // 2nd week portion.
		ofSetLineWidth(2);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'v') {
		// HACK: only needed on windows, when using ofSetAutoBackground(false)
		glReadBuffer(GL_FRONT);
		ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
	}
	if (key == 'q') {
		// Reset flags
		draw_flag = 0;

		// Free the dynamically allocated memory exits.

		cout << "Dynamically allocated memory has been freed." << endl;

		_Exit(0);
	}
	if (key == 'd') {
		if (!load_flag) return;

		/* COMSIL1-TODO 2: This is draw control part.
		You should draw only after when the key 'd' has been pressed.
		*/

		draw_flag = 1;
	}
	if (key == 's') {
		// 2nd week portion.
	}
	if (key == 'e') {
		// 2nd week portion.
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'l') {
		// Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt for Waterfall");

		// Check whether the user opened a file
		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");

			// We have a file, so let's check it and process it
			processOpenFileSelection(openFileResult);
			load_flag = 1;
		}
	}

	/* COMSIL1-TODO 4: This is selection dot control part.
	 You can select dot in which water starts to flow by left, right direction key (<- , ->).
	 */

	if (key == OF_KEY_RIGHT) {
		int x = Dot_x1_array[water_dot];
		int y = Dot_y1_array[water_dot];
		int flag = 0;
		//현재 물나오는 지점과 같은 x좌표의 아래에 점이 있는지 확인
		while (y <= Y_MAX) {
			y++;
			for (int i = 0; i < num_of_dot; i++) {
				if ((x == Dot_x1_array[i]) && (y == Dot_y1_array[i])) {
					water_dot = i;
					flag = 1;
				}
			}
			if (flag == 1) break;
		}
		//아래에 점 없음
		if (flag == 0) {
			while (x <= X_MAX) {
				x++;
				if (x == X_MAX + 1) x = 0;
				y = Y_MAX;
				for (int i = 0; i < num_of_dot; i++) {
					if ((x == Dot_x1_array[i]) && (Dot_y1_array[i] <= y)) {
						water_dot = i;
						y = Dot_y1_array[i];
						flag = 2;
					}
				}
				if (flag == 2) break;
			}
		}

		cout << "Selected Dot Coordinate is (" << Dot_x1_array[water_dot] << ", " << Dot_y1_array[water_dot] << ")" << endl;
	}
	if (key == OF_KEY_LEFT) {
		int x = Dot_x1_array[water_dot];
		int y = Dot_y1_array[water_dot];
		int flag = 0;
		//현재 물나오는 지점과 같은 x좌표의 아래에 점이 있는지 확인
		while (y <= Y_MAX) {
			y++;
			for (int i = 0; i < num_of_dot; i++) {
				if ((x == Dot_x1_array[i]) && (y == Dot_y1_array[i])) {
					water_dot = i;
					flag = 1;
				}
			}
			if (flag == 1) break;
		}
		//아래에 점 없음
		if (flag == 0) {
			while (x >= 0) {
				x--;
				if (x == -1) x = X_MAX;
				y = Y_MAX;
				for (int i = 0; i < num_of_dot; i++) {
					if ((x == Dot_x1_array[i]) && (Dot_y1_array[i] <= y)) {
						water_dot = i;
						y = Dot_y1_array[i];
						flag = 2;
					}
				}
				if (flag == 2) break;
			}
		}
		cout << "Selected Dot Coordinate is (" << Dot_x1_array[water_dot] << ", " << Dot_y1_array[water_dot] << ")" << endl;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
	//Path to the comma delimited file
	//string fileName = "input.txt";

	string fileName = openFileResult.getName();
	ofFile file(fileName);

	if (!file.exists()) {
		cout << "Target file does not exists." << endl;
		_Exit(0);
	}
	else cout << "We found the target file." << endl;

	ofBuffer buffer(file);

	/* This variable is for indicating which type of input is being received.
	 IF input_type == 0, then work of getting line input is in progress.
	 IF input_type == 1, then work of getting dot input is in progress.
	 */
	int input_type = 0;
	int line_dot_count = 0;
	int idx = 0;

	/* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
	 You must maintain those information. But, currently below code is not complete.
	 Also, note that all of coordinate should not be out of screen size.
	 However, all of coordinate do not always turn out to be the case.
	 So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
	*/


	// Read file line by line
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
		string line = *it;
	
		// Split line into strings
		vector<string> words = ofSplitString(line, " ");

		line_dot_count++;
		if (line_dot_count == num_of_line + 2) {
			input_type = 1;
		}
//		cout << "count" << line_dot_count << endl;
		if (words.size() == 1) {
			if (input_type == 0) { // Input for the number of lines.
				num_of_line = atoi(words[0].c_str());
				cout << "The number of line is: " << num_of_line << endl;
				Line_x1_array = new int[num_of_line];
				Line_y1_array = new int[num_of_line];
				Line_x2_array = new int[num_of_line];
				Line_y2_array = new int[num_of_line];
			}
			else { // Input for the number of dots.
				num_of_dot = atoi(words[0].c_str());
				cout << "The number of dot is: " << num_of_dot << endl;
				Dot_x1_array = new int[num_of_dot];
				Dot_y1_array = new int[num_of_dot];
				idx = 0;
			}
		}
		else if (words.size() >= 2) {
			int x1, y1, x2, y2;
			if (input_type == 0) { // Input for actual information of lines
				x1 = atoi(words[0].c_str());
				y1 = atoi(words[1].c_str());
				x2 = atoi(words[2].c_str());
				y2 = atoi(words[3].c_str());

				if ((x1 >= 0 && x1 <= X_MAX) && (y1 >= 40 && y1 <= Y_MAX) && (x2 >= 0 && x2 <= X_MAX) && (y2 >= 40 && y2 <= Y_MAX)) {
					Line_x1_array[idx] = x1;
					Line_y1_array[idx] = y1;
					Line_x2_array[idx] = x2;
					Line_y2_array[idx] = y2;
					idx++;
				}
			}
			else { // Input for actual information of dots.
				x1 = atoi(words[0].c_str());
				y1 = atoi(words[1].c_str());

				if ((x1 >= 0 && x1 <= X_MAX) && (y1 >= 40 && y1 <= Y_MAX)) {
					Dot_x1_array[idx] = x1;
					Dot_y1_array[idx] = y1;
					if ((x1 == Dot_x1_array[water_dot])&&(y1 <= Dot_y1_array[water_dot])) {
						water_dot = idx;
					}
					else if (x1 < Dot_x1_array[water_dot]) {
						water_dot = idx;
					}
					idx++;
				}
			}
		} // End of else if.
	} // End of for-loop (Read file line by line).
	//initializeWaterLines();
}

void ofApp::initializeWaterLines() {
	;
}