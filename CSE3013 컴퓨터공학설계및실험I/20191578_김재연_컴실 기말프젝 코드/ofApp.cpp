#include "ofApp.h"
int red=80, green=188, blue=223; //����ȿ���� ���� �� rgb���� ������Ű�� ���� ����ġ�� ������ �����Ѵ�.
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(500); // Limit the speed of our program to 15 frames per second

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
	if (water_flag==1) {			//water flag�� 1�� �����Ǹ�
		c = a; d = b;				//c,e,g,i,���� a�� �ְ� d, f, h, j���� b�� �ִ´�.
		e = a; f = b;
		g = a; h = b;
		i = a; j = b;
		if (idx1 % 2 == 1) {					//path_O �迭�� Ȧ����° ����
			b++;								//y��ǥ�� 1 �ø���.
			if ((b - path_y[idx1] < 1) && (path_y[idx1] - b < 1)) {
				idx1++;							//���� ���Ҹ� ����Ų��.
			}
			d -= Dot_r_array[water_dot];		//�ֹ��� ������ ��ġ�� ���� ������Ʈ�Ѵ�.
			f = f - 2 * Dot_r_array[water_dot];
			h = h - 3 * Dot_r_array[water_dot];
			j = j - 4 * Dot_r_array[water_dot];
		}
		else {										//path_O �迭�� ¦����° ����
			if (path_x[idx1 - 1] >= path_x[idx1]) { //������->�������� �带 ��
				a--;								//x��ǥ�� 1 ���δ�.
				b -= slope[idx2];					//y��ǥ�� ���� ���⸸ŭ ���δ�.
				d = b + 10 * slope[idx2];			//�ֹ��� ������ ��ġ�� ���� ������Ʈ�Ѵ�.
				f = b + 20 * slope[idx2];
				h = b + 30 * slope[idx2];
				j = b + 40 * slope[idx2];
			}
			else {							//����->���������� �带 ��
				a++;						//x��ǥ�� 1 �ø���.
				b += slope[idx2];			//y��ǥ�� ���� ���⸸ŭ �ø���.
				d = b - 10 * slope[idx2];	//�ֹ��� ������ ��ġ�� ���� ������Ʈ�Ѵ�.
				f = b - 20 * slope[idx2];
				h = b - 30 * slope[idx2];
				j = b - 40 * slope[idx2];
			}
			if (slope[idx2] != 0) {										//��簡 0�� �ƴϸ�(��簡 �����ϸ�)
				if ((b - path_y[idx1] < 1) && (path_y[idx1] - b < 1)) {	//���� ������ 1 �̸��� ��
					idx1++;												//���� ���Ҹ� ����Ų��.
					idx2++;
				}
			}
			else {							//��簡 0�̸�(��簡 ������)
				if (a == path_x[idx1]) {	//x��ǥ�� path_x�� ���ҿ� ������ ��
					idx1++;					//���� ���Ҹ� ����Ų��.
					idx2++;
				}
			}
			if (c - a < 0) {				//a���� �������� ���������� �ֹ����� ������ �Ӹ�(a)���� ���ʿ� �־���Ѵ�.
				c = a; e = a; g = a; i = a;
				c -= Dot_r_array[water_dot];
				e = e - 2 * Dot_r_array[water_dot];
				g = g - 3 * Dot_r_array[water_dot];
				i = i - 4 * Dot_r_array[water_dot];
			}
			else if (c - a > 0) {			//a���� �������� ���������� �ֹ����� ������ �Ӹ�(a)���� �����ʿ� �־���Ѵ�.
				c = a; e = a; g = a; i = a;
				c += Dot_r_array[water_dot];
				e = e + 2 * Dot_r_array[water_dot];
				g = g + 3 * Dot_r_array[water_dot];
				i = i + 4 * Dot_r_array[water_dot];
			}
			
		}

		if (idx1 == path_idx+1) {	//����� ���� �����ϸ�
			idx1 = 1;				//�ε��� ���� �ʱ�ȭ�ϰ�
			idx2 = 0;
			water_flag = 0;			//water_flag�� 0���� �ʱ�ȭ�Ͽ� ������� ���̻� �׸��� �ʴ´�.
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofFill();
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
			ofDrawLine(Line_x1_array[i], Line_y1_array[i], Line_x2_array[i], Line_y2_array[i]); //������ �׸���.
		}
		
		for (int i = 0; i < num_of_dot; i++) {
			if (i == water_dot) {												//���� ������ ����
				ofSetColor(255, 0, 0);											//������ ������ �׸���.
				ofDrawCircle(Dot_x1_array[i], Dot_y1_array[i], Dot_r_array[i]);
			}
			else {																//���� ������ �ʴ� ����
				ofSetColor(0);													//������ ������ �׸���.
				ofDrawCircle(Dot_x1_array[i], Dot_y1_array[i], Dot_r_array[i]);
			}
		}
		 // 2nd week portion.
		ofSetLineWidth(2);
	}

	if (water_flag==1) {
		red = 80, green = 188, blue = 223;
		ofSetColor(0, 128, 0);
		ofDrawCircle(a, b, Dot_r_array[water_dot]);	//�ֹ����� �Ӹ��� �׸���.
		ofSetColor(129, 193, 71);
		ofDrawCircle(c, d, Dot_r_array[water_dot]);	//�ֹ����� ������ �׸���.
		ofSetColor(0, 255, 0);
		ofDrawCircle(e, f, Dot_r_array[water_dot]);
		ofSetColor(0, 153, 0);
		ofDrawCircle(g, h, Dot_r_array[water_dot]);
		ofSetColor(80, 200, 120);
		ofDrawCircle(i, j, Dot_r_array[water_dot]);
	}

	else if (water_flag == 2) {
	//	ofSetColor(80, 188, 223);
		ofSetColor(red++, green++, blue++); //�ֹ����� �������� ������ ��, ������ ���� �� �����ϴ� ȿ���� ���� �� rgb������ ��� 255���� �ø���.
		if (red >= 225 && green >= 225 && blue >= 225) {
			ofDrawCircle(a, b, Dot_r_array[water_dot]); //������� ����� �Ǹ� ����ȿ��(y��ǥ�� ����)�� �����Ѵ�.
		}
		else {
			ofDrawCircle(a, b--, Dot_r_array[water_dot]); //������� ����� �� ���� ����ȿ��(y��ǥ�� ����)�� �����Ѵ�.
		}
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
		for (int i = 0; i <= path_idx; i++) {	//��� �迭�� �ִ� ������ ��� �ʱ�ȭ�Ѵ�.
			path_x[i] = 0;
			path_y[i] = 0;
		}
		path_idx = 0;
		for (int i = 0; i <= slope_idx; i++) {	//��� �迭�� �ִ� ���鵵 ��� �ʱ�ȭ�Ѵ�.
			slope[i] = 0;
		}
		slope_idx = 0;

		int start_x, start_y, stop_x, stop_y=0, end_x, end_y;
		//start_O�� �������� �����ϴ� ��, stop_O�� �������� �������� �� ���а� �´�� ��, end_O�� ������ ���� �ٴٶ��� ���� ��
		double cal_slope;
		double temp_y;
		start_x = Dot_x1_array[water_dot];
		start_y = Dot_y1_array[water_dot];
		while (stop_y<Y_MAX) {		//������� ���ߴ� ������ y��ǥ�� Y_MAX���� ���� ���� �ݺ��Ѵ�.
			stop_x = start_x;
			stop_y = Y_MAX;

			for (int i = 0; i < num_of_line; i++) {	//������ ���е鿡 ���ؼ�
				if ((stop_x > Line_x1_array[i]) && (stop_x < Line_x2_array[i])) {	//���� ����� ��������
					temp_y = ((Line_y2_array[i] - Line_y1_array[i])*(stop_x - Line_x1_array[i])) / (Line_x2_array[i] - Line_x1_array[i]);
					temp_y += Line_y1_array[i];	//������ ���� y��ǥ�� ����ϰ�
					if ((temp_y < stop_y) && (temp_y >= start_y)) {	//������ ���� ���� ������
						stop_y = temp_y;	//stop_y�� ����� ���� �ִ´�.
						picked_line_idx = i;
					}
				}
				//������ �������� �������� �� ���� stop_y��� �Ѵ�.
				//������ ���� �������� �������� ������ �����ʺ��� ���� ��
				if ((stop_x == Line_x1_array[i]) && (Line_y1_array[i] < Line_y2_array[i])) {
					temp_y = Line_y1_array[i];
					if ((temp_y < stop_y) && (temp_y >= start_y)) {
						stop_y = temp_y;
						picked_line_idx = i;
					}
				}
				//������ ������ �������� �������� ������ �����ʺ��� ���� ��
				if ((stop_x == Line_x2_array[i]) && (Line_y1_array[i] > Line_y2_array[i])) {
					temp_y = Line_y2_array[i];
					if ((temp_y < stop_y) && (temp_y >= start_y)) {
						stop_y = temp_y;
						picked_line_idx = i;
					}
				}
				
			}
			
			if (stop_y < Y_MAX) {	//stop_y�� Y_MAX���� ���� ��, �� ���� �ٴڱ��� �������� �ʾ��� ��
				if (Line_y1_array[picked_line_idx] >= Line_y2_array[picked_line_idx]) {	//������ �����ʺ��� ���� �����̶��
					end_x = Line_x1_array[picked_line_idx];	//���� ������ ���� �̵��Ѵ�.
					end_y = Line_y1_array[picked_line_idx];
				}
				else {										//�������� ���ʺ��� ���� �����̶��
					end_x = Line_x2_array[picked_line_idx];	//������ ������ ���� �̵��Ѵ�.
					end_y = Line_y2_array[picked_line_idx];
				}
				cal_slope = Line_y2_array[picked_line_idx] - Line_y1_array[picked_line_idx];	//������ ���⸦ ����Ѵ�.
				cal_slope /= (Line_x2_array[picked_line_idx] - Line_x1_array[picked_line_idx]);
				path_x[path_idx] = start_x;	//path_O�迭�� ������ start_O�� �ְ�
				path_y[path_idx] = start_y;
				path_idx++;
				path_x[path_idx] = stop_x;	//���а� �´��� �� stop_O�� �ְ�
				path_y[path_idx] = stop_y;
				path_idx++;
				path_x[path_idx] = end_x;	//������ ���� �귯 ������ �� end_O�� �ִ´�.
				path_y[path_idx] = end_y;
				slope[slope_idx] = cal_slope;	//�ش� ������ ���⵵ slope�迭�� �ִ´�.
				slope_idx++;
				start_x = end_x;			//���� ��� ����� ���� ������ ������ �̹� ����� �������� �����Ѵ�.
				start_y = end_y;
			}

			else {							//�ٴڱ��� �����ߴٸ�
				path_x[path_idx] = start_x;	//path_O�� start_O�� stop_O���� �ְ� �����Ѵ�.
				path_y[path_idx] = start_y;
				path_idx++;
				path_x[path_idx] = stop_x;
				path_y[path_idx] = stop_y;
				break;
			}
		}

		water_flag = 1;	//water flag�� 1�� �����ϰ�
		a = path_x[0];	//�ֹ����� �Ӹ� ��ǥ�� a, b�� �̵������ ù��° ������ �����Ѵ�.
		b = path_y[0];
	}

	if (key == 'e') {
		// 2nd week portion.
		water_flag = 2;	//water flag�� 2�� �����ϰ�
		idx1 = 1;		//idx1, idx2�� ���� �ʱ�ȭ�Ѵ�.
		idx2 = 0;
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
		SelectWaterDot(); //������ Ű�� ����� �� ���� �������� ���� �� �� ����� ���� ���� ���� ���� ���� ������ �����Ѵ�.
		cout << "Selected Dot Coordinate is (" << Dot_x1_array[water_dot] << ", " << Dot_y1_array[water_dot] << ")" << endl;
	}

	if (key == OF_KEY_LEFT) {
		int x = Dot_x1_array[water_dot];
		int y = Dot_y1_array[water_dot];
		int flag = 0;
		//���� �������� ������ ���� x��ǥ�� �Ʒ��� ���� �ִ��� Ȯ��
		while (y <= Y_MAX) {
			y++;
			for (int i = 0; i < num_of_dot; i++) {
				if ((x == Dot_x1_array[i]) && (y == Dot_y1_array[i])) {	//���� ã����
					water_dot = i;	//water dot ����
					flag = 1;
				}
			}
			if (flag == 1) break;
		}
		//�Ʒ��� �� ����
		if (flag == 0) {
			while (x >= 0) {
				x--;	//x��ǥ�� 1�� ���δ�.(�˻� ������ �������� �̵�)
				if (x == -1) x = X_MAX;	//x�� ������ ����� ������ ������ ������.
				y = Y_MAX;
				for (int i = 0; i < num_of_dot; i++) {
					if ((x == Dot_x1_array[i]) && (Dot_y1_array[i] <= y)) {	//���� ã����
						water_dot = i;		//water dot ����
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
				//������ x1, y1, x2, y2��ǥ�� ������ �迭�� �޸𸮸� �Ҵ��Ѵ�.
				Line_x1_array = new int[num_of_line];
				Line_y1_array = new int[num_of_line];
				Line_x2_array = new int[num_of_line];
				Line_y2_array = new int[num_of_line];
			}
			else { // Input for the number of dots.
				num_of_dot = atoi(words[0].c_str());
				cout << "The number of dot is: " << num_of_dot << endl;
				//���� x1, y1, r���� ������ �迭�� �޸𸮸� �Ҵ��Ѵ�.
				Dot_x1_array = new int[num_of_dot];
				Dot_y1_array = new int[num_of_dot];
				Dot_r_array = new int[num_of_dot];
				idx = 0;
			}
		}
		else if (words.size() >= 2) {
			int x1, y1, x2, y2, r;
			if (input_type == 0) { // Input for actual information of lines
				x1 = atoi(words[0].c_str());
				y1 = atoi(words[1].c_str());
				x2 = atoi(words[2].c_str());
				y2 = atoi(words[3].c_str());

				if ((x1 >= 0 && x1 <= X_MAX) && (y1 >= 40 && y1 <= Y_MAX) && (x2 >= 0 && x2 <= X_MAX) && (y2 >= 40 && y2 <= Y_MAX)) {
					//��� ȭ�� ���� ǥ�� ������ ���� �� x1, y1, x2, y2���� ������ �迭�� �����Ѵ�.
					if (x1 <= x2) {
						Line_x1_array[idx] = x1;
						Line_y1_array[idx] = y1;
						Line_x2_array[idx] = x2;
						Line_y2_array[idx] = y2;
					}
					else {
						Line_x1_array[idx] = x2;
						Line_y1_array[idx] = y2;
						Line_x2_array[idx] = x1;
						Line_y2_array[idx] = y1;
					}
					idx++;
				}
			}
			else { // Input for actual information of dots.
				x1 = atoi(words[0].c_str());
				y1 = atoi(words[1].c_str());
				r = atoi(words[2].c_str());

				if ((x1 >= 0 && x1 <= X_MAX) && (y1 >= 40 && y1 <= Y_MAX)) {
					//��� ȭ�� ������ ǥ�� ������ ���� �� x1, y1, r�� ������ �迭�� �����Ѵ�.
					Dot_x1_array[idx] = x1;
					Dot_y1_array[idx] = y1;
					Dot_r_array[idx] = r; //���� �������� �����Ѵ�.
					idx++;
				}
				element item;			//element�� ���� item�� �� ������ ������ �����Ѵ�.
				item.x = Dot_x1_array[idx - 1];
				item.y = Dot_y1_array[idx - 1];
				item.r = Dot_r_array[idx - 1];
				item.idx = idx - 1;
				insert_min_heap(item); //���� ������ ���� ũ�⸦ �������� ���� ���� ������ min_heap�� ��´�.
									   //���� ������ ���� ũ�� == ������� ũ��
			}
		} // End of else if.
	} // End of for-loop (Read file line by line).
	//initializeWaterLines();
	SelectWaterDot(); //ù��°�� ���� ���� ���� �����Ѵ�.(ũ�Ⱑ ���� ���� ��)
}

void ofApp::initializeWaterLines() {
	;
}


void ofApp::insert_min_heap(element item) { //���� ���� ������ min heap�� ��´�.
	int i;
	i = ++min_n;								//min heap�� ����ִ� ������ ������ �ø���.(����)
	if (i > 1) {								//�� ������ 2�� �̻��� ��
		while (1) {								//���� ������ �ݺ��Ѵ�.
			if (item.r < min_heap[i / 2].r) {	//item(i)�� r������ �θ�(i/2)�� r���� ũ��
				min_heap[i] = min_heap[i / 2];	//min heap�� i��°�� i/2��° ���� �ִ´�.
				i /= 2;							//item�� ��ġ�� ��Ÿ���� i�� i/2�� ������Ʈ�Ѵ�.
			}
			if ((item.r >= min_heap[i / 2].r) || (i == 1)) break; //�θ𺸴� ũ�ų� ���ų� i�� 1�̸� �����Ѵ�.
		}
	}
	min_heap[i] = item; //�� ������ ���� ���� min heap�� i��°�� item�� �����Ѵ�.
}

void ofApp::SelectWaterDot() { //min heap�� ����ִ� �� �� ũ�Ⱑ ���� ���� ���� �����Ѵ�.
	int parent, child;
	element item, temp;
	item = min_heap[1];			//item���� min heap�� 1��° ��, �� ���� ���� ���� �ִ´�.
	temp = min_heap[min_n--];	//temp���� min heap�� ������ ���� �ְ�, min_n�� 1 ���δ�.
	parent = 1;
	child = 2;
	while (child <= min_n) {	//child�� min_n���� �۰ų� ���� ���� �ݺ��Ѵ�.(Ʈ���� �籸��)
		if ((child < min_n) && (min_heap[child].r > min_heap[child + 1].r)) child++; //������ child�� �����Ѵ�.
		if (temp.r <= min_heap[child].r) break;	//temp�� r���� �ڽ��� r�� ũ�ų� ���� �� �����Ѵ�.
		min_heap[parent] = min_heap[child];		//�θ� �ڽ��� �ִ´�.
		parent = child;							//�θ�� �ڽ��� ���� �����Ѵ�.
		child *= 2;
	}
	min_heap[parent] = temp;	//�� ������ ���� ���� min heap�� �θ� temp�� �ִ´�.(Ʈ���� �籸�� �Ϸ�)
	if (min_n >= 0) {			//���� min_n�� 0 �̻��̶�� min heap�� ���Ұ� �����ִٴ� ���̹Ƿ�
		water_dot = item.idx;	//water dot�� item.idx�� ������Ʈ�Ѵ�.
		cout << "You chose the " << num_of_dot - min_n << "th/" << num_of_dot << " point in min heap." << endl;
	}
	else {						//�׷��� ������ ���̻� min heap�� ���Ұ� �������� �ʴٴ� ������ �����޼����� ����Ѵ�.
		cout << "You can't press the right key anymore. Press the left key." << endl;
	}
}