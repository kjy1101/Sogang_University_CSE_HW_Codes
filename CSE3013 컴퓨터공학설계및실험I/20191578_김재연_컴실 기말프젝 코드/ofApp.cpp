#include "ofApp.h"
int red=80, green=188, blue=223; //증발효과를 위해 각 rgb값을 증가시키기 위해 기준치를 변수에 저장한다.
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
	if (water_flag==1) {			//water flag가 1로 설정되면
		c = a; d = b;				//c,e,g,i,에는 a를 넣고 d, f, h, j에는 b를 넣는다.
		e = a; f = b;
		g = a; h = b;
		i = a; j = b;
		if (idx1 % 2 == 1) {					//path_O 배열의 홀수번째 원소
			b++;								//y좌표를 1 늘린다.
			if ((b - path_y[idx1] < 1) && (path_y[idx1] - b < 1)) {
				idx1++;							//다음 원소를 가리킨다.
			}
			d -= Dot_r_array[water_dot];		//애벌레 몸통의 위치를 각각 업데이트한다.
			f = f - 2 * Dot_r_array[water_dot];
			h = h - 3 * Dot_r_array[water_dot];
			j = j - 4 * Dot_r_array[water_dot];
		}
		else {										//path_O 배열의 짝수번째 원소
			if (path_x[idx1 - 1] >= path_x[idx1]) { //오른쪽->왼쪽으로 흐를 때
				a--;								//x좌표를 1 줄인다.
				b -= slope[idx2];					//y좌표는 일정 기울기만큼 줄인다.
				d = b + 10 * slope[idx2];			//애벌레 몸통의 위치를 각각 업데이트한다.
				f = b + 20 * slope[idx2];
				h = b + 30 * slope[idx2];
				j = b + 40 * slope[idx2];
			}
			else {							//왼쪽->오른쪽으로 흐를 때
				a++;						//x좌표를 1 늘린다.
				b += slope[idx2];			//y좌표는 일정 기울기만큼 늘린다.
				d = b - 10 * slope[idx2];	//애벌레 몸통의 위치를 각각 업데이트한다.
				f = b - 20 * slope[idx2];
				h = b - 30 * slope[idx2];
				j = b - 40 * slope[idx2];
			}
			if (slope[idx2] != 0) {										//경사가 0이 아니면(경사가 존재하면)
				if ((b - path_y[idx1] < 1) && (path_y[idx1] - b < 1)) {	//둘의 오차가 1 미만일 때
					idx1++;												//다음 원소를 가리킨다.
					idx2++;
				}
			}
			else {							//경사가 0이면(경사가 없으면)
				if (a == path_x[idx1]) {	//x좌표가 path_x의 원소와 동일할 때
					idx1++;					//다음 원소를 가리킨다.
					idx2++;
				}
			}
			if (c - a < 0) {				//a값이 이전보다 증가했으면 애벌레의 몸통은 머리(a)보다 왼쪽에 있어야한다.
				c = a; e = a; g = a; i = a;
				c -= Dot_r_array[water_dot];
				e = e - 2 * Dot_r_array[water_dot];
				g = g - 3 * Dot_r_array[water_dot];
				i = i - 4 * Dot_r_array[water_dot];
			}
			else if (c - a > 0) {			//a값이 이전보다 감소했으면 애벌레의 몸통은 머리(a)보다 오른쪽에 있어야한다.
				c = a; e = a; g = a; i = a;
				c += Dot_r_array[water_dot];
				e = e + 2 * Dot_r_array[water_dot];
				g = g + 3 * Dot_r_array[water_dot];
				i = i + 4 * Dot_r_array[water_dot];
			}
			
		}

		if (idx1 == path_idx+1) {	//경로의 끝에 도달하면
			idx1 = 1;				//인덱스 값을 초기화하고
			idx2 = 0;
			water_flag = 0;			//water_flag도 0으로 초기화하여 물방울을 더이상 그리지 않는다.
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
			ofDrawLine(Line_x1_array[i], Line_y1_array[i], Line_x2_array[i], Line_y2_array[i]); //선분을 그린다.
		}
		
		for (int i = 0; i < num_of_dot; i++) {
			if (i == water_dot) {												//물이 나오는 점은
				ofSetColor(255, 0, 0);											//빨간색 점으로 그린다.
				ofDrawCircle(Dot_x1_array[i], Dot_y1_array[i], Dot_r_array[i]);
			}
			else {																//물이 나오지 않는 점은
				ofSetColor(0);													//검은색 점으로 그린다.
				ofDrawCircle(Dot_x1_array[i], Dot_y1_array[i], Dot_r_array[i]);
			}
		}
		 // 2nd week portion.
		ofSetLineWidth(2);
	}

	if (water_flag==1) {
		red = 80, green = 188, blue = 223;
		ofSetColor(0, 128, 0);
		ofDrawCircle(a, b, Dot_r_array[water_dot]);	//애벌레의 머리를 그린다.
		ofSetColor(129, 193, 71);
		ofDrawCircle(c, d, Dot_r_array[water_dot]);	//애벌레의 몸통을 그린다.
		ofSetColor(0, 255, 0);
		ofDrawCircle(e, f, Dot_r_array[water_dot]);
		ofSetColor(0, 153, 0);
		ofDrawCircle(g, h, Dot_r_array[water_dot]);
		ofSetColor(80, 200, 120);
		ofDrawCircle(i, j, Dot_r_array[water_dot]);
	}

	else if (water_flag == 2) {
	//	ofSetColor(80, 188, 223);
		ofSetColor(red++, green++, blue++); //애벌레의 움직임을 멈췄을 때, 물방울로 변한 후 증발하는 효과를 위해 각 rgb값들을 모두 255까지 올린다.
		if (red >= 225 && green >= 225 && blue >= 225) {
			ofDrawCircle(a, b, Dot_r_array[water_dot]); //물방울이 흰색이 되면 증발효과(y좌표의 감소)를 중지한다.
		}
		else {
			ofDrawCircle(a, b--, Dot_r_array[water_dot]); //물방울이 흰색이 될 동안 증발효과(y좌표의 감소)를 실행한다.
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
		for (int i = 0; i <= path_idx; i++) {	//경로 배열에 있는 값들을 모두 초기화한다.
			path_x[i] = 0;
			path_y[i] = 0;
		}
		path_idx = 0;
		for (int i = 0; i <= slope_idx; i++) {	//경사 배열에 있는 값들도 모두 초기화한다.
			slope[i] = 0;
		}
		slope_idx = 0;

		int start_x, start_y, stop_x, stop_y=0, end_x, end_y;
		//start_O는 움직임이 시작하는 점, stop_O는 수직으로 떨어졌을 때 선분과 맞닿는 점, end_O는 선분의 끝에 다다랐을 때의 점
		double cal_slope;
		double temp_y;
		start_x = Dot_x1_array[water_dot];
		start_y = Dot_y1_array[water_dot];
		while (stop_y<Y_MAX) {		//물방울이 멈추는 지점의 y좌표가 Y_MAX보다 작을 동안 반복한다.
			stop_x = start_x;
			stop_y = Y_MAX;

			for (int i = 0; i < num_of_line; i++) {	//각각의 선분들에 대해서
				if ((stop_x > Line_x1_array[i]) && (stop_x < Line_x2_array[i])) {	//선분 가운데로 떨어지면
					temp_y = ((Line_y2_array[i] - Line_y1_array[i])*(stop_x - Line_x1_array[i])) / (Line_x2_array[i] - Line_x1_array[i]);
					temp_y += Line_y1_array[i];	//떨어진 점의 y좌표를 계산하고
					if ((temp_y < stop_y) && (temp_y >= start_y)) {	//적절한 범위 내에 들어오면
						stop_y = temp_y;	//stop_y에 계산한 값을 넣는다.
						picked_line_idx = i;
					}
				}
				//선분의 끝점으로 떨어지면 그 점을 stop_y라고 한다.
				//선분의 왼쪽 끝점으로 떨어지고 왼쪽이 오른쪽보다 높을 때
				if ((stop_x == Line_x1_array[i]) && (Line_y1_array[i] < Line_y2_array[i])) {
					temp_y = Line_y1_array[i];
					if ((temp_y < stop_y) && (temp_y >= start_y)) {
						stop_y = temp_y;
						picked_line_idx = i;
					}
				}
				//선분의 오른쪽 끝점으로 떨어지고 왼쪽이 오른쪽보다 낮을 때
				if ((stop_x == Line_x2_array[i]) && (Line_y1_array[i] > Line_y2_array[i])) {
					temp_y = Line_y2_array[i];
					if ((temp_y < stop_y) && (temp_y >= start_y)) {
						stop_y = temp_y;
						picked_line_idx = i;
					}
				}
				
			}
			
			if (stop_y < Y_MAX) {	//stop_y가 Y_MAX보다 작을 때, 즉 아직 바닥까지 도달하지 않았을 때
				if (Line_y1_array[picked_line_idx] >= Line_y2_array[picked_line_idx]) {	//왼쪽이 오른쪽보다 낮은 선분이라면
					end_x = Line_x1_array[picked_line_idx];	//왼쪽 끝점을 향해 이동한다.
					end_y = Line_y1_array[picked_line_idx];
				}
				else {										//오른쪽이 왼쪽보다 낮은 선분이라면
					end_x = Line_x2_array[picked_line_idx];	//오른쪽 끝점을 향해 이동한다.
					end_y = Line_y2_array[picked_line_idx];
				}
				cal_slope = Line_y2_array[picked_line_idx] - Line_y1_array[picked_line_idx];	//선분의 기울기를 계산한다.
				cal_slope /= (Line_x2_array[picked_line_idx] - Line_x1_array[picked_line_idx]);
				path_x[path_idx] = start_x;	//path_O배열에 시작점 start_O를 넣고
				path_y[path_idx] = start_y;
				path_idx++;
				path_x[path_idx] = stop_x;	//선분과 맞닿은 점 stop_O를 넣고
				path_y[path_idx] = stop_y;
				path_idx++;
				path_x[path_idx] = end_x;	//선분을 따라 흘러 도달한 점 end_O를 넣는다.
				path_y[path_idx] = end_y;
				slope[slope_idx] = cal_slope;	//해당 선분의 기울기도 slope배열에 넣는다.
				slope_idx++;
				start_x = end_x;			//다음 경로 계산을 위해 시작점 정보를 이번 경로의 끝점으로 설정한다.
				start_y = end_y;
			}

			else {							//바닥까지 도달했다면
				path_x[path_idx] = start_x;	//path_O에 start_O와 stop_O만을 넣고 종료한다.
				path_y[path_idx] = start_y;
				path_idx++;
				path_x[path_idx] = stop_x;
				path_y[path_idx] = stop_y;
				break;
			}
		}

		water_flag = 1;	//water flag를 1로 설정하고
		a = path_x[0];	//애벌레의 머리 좌표인 a, b를 이동경로의 첫번째 값으로 설정한다.
		b = path_y[0];
	}

	if (key == 'e') {
		// 2nd week portion.
		water_flag = 2;	//water flag를 2로 설정하고
		idx1 = 1;		//idx1, idx2를 각각 초기화한다.
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
		SelectWaterDot(); //오른쪽 키를 사용해 한 번도 도달하지 않은 점 중 사이즈가 가장 작은 점을 물이 나올 점으로 선택한다.
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
				if ((x == Dot_x1_array[i]) && (y == Dot_y1_array[i])) {	//점을 찾으면
					water_dot = i;	//water dot 세팅
					flag = 1;
				}
			}
			if (flag == 1) break;
		}
		//아래에 점 없음
		if (flag == 0) {
			while (x >= 0) {
				x--;	//x좌표를 1씩 줄인다.(검사 범위를 왼쪽으로 이동)
				if (x == -1) x = X_MAX;	//x가 범위를 벗어나면 오른쪽 끝으로 돌린다.
				y = Y_MAX;
				for (int i = 0; i < num_of_dot; i++) {
					if ((x == Dot_x1_array[i]) && (Dot_y1_array[i] <= y)) {	//점을 찾으면
						water_dot = i;		//water dot 세팅
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
				//선분의 x1, y1, x2, y2좌표를 저장할 배열에 메모리를 할당한다.
				Line_x1_array = new int[num_of_line];
				Line_y1_array = new int[num_of_line];
				Line_x2_array = new int[num_of_line];
				Line_y2_array = new int[num_of_line];
			}
			else { // Input for the number of dots.
				num_of_dot = atoi(words[0].c_str());
				cout << "The number of dot is: " << num_of_dot << endl;
				//점의 x1, y1, r값을 저장할 배열에 메모리를 할당한다.
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
					//모두 화면 내에 표시 가능한 수일 때 x1, y1, x2, y2값을 각각의 배열에 저장한다.
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
					//모두 화면 내에게 표시 가능한 수일 때 x1, y1, r을 각각의 배열에 저장한다.
					Dot_x1_array[idx] = x1;
					Dot_y1_array[idx] = y1;
					Dot_r_array[idx] = r; //점의 반지름도 저장한다.
					idx++;
				}
				element item;			//element형 변수 item에 각 점들의 정보를 저장한다.
				item.x = Dot_x1_array[idx - 1];
				item.y = Dot_y1_array[idx - 1];
				item.r = Dot_r_array[idx - 1];
				item.idx = idx - 1;
				insert_min_heap(item); //물이 나오는 점의 크기를 기준으로 점에 대한 정보를 min_heap에 담는다.
									   //물이 나오는 점의 크기 == 물방울의 크기
			}
		} // End of else if.
	} // End of for-loop (Read file line by line).
	//initializeWaterLines();
	SelectWaterDot(); //첫번째로 물이 나올 점을 선택한다.(크기가 가장 작은 점)
}

void ofApp::initializeWaterLines() {
	;
}


void ofApp::insert_min_heap(element item) { //점에 대한 정보를 min heap에 담는다.
	int i;
	i = ++min_n;								//min heap에 들어있는 원소의 개수를 늘린다.(삽입)
	if (i > 1) {								//그 개수가 2개 이상일 때
		while (1) {								//다음 과정을 반복한다.
			if (item.r < min_heap[i / 2].r) {	//item(i)의 r값보다 부모(i/2)의 r값이 크면
				min_heap[i] = min_heap[i / 2];	//min heap의 i번째에 i/2번째 값을 넣는다.
				i /= 2;							//item의 위치를 나타내는 i는 i/2로 업데이트한다.
			}
			if ((item.r >= min_heap[i / 2].r) || (i == 1)) break; //부모보다 크거나 같거나 i가 1이면 종료한다.
		}
	}
	min_heap[i] = item; //위 연산을 통해 구한 min heap의 i번째에 item을 삽입한다.
}

void ofApp::SelectWaterDot() { //min heap에 담겨있는 점 중 크기가 가장 작은 점을 선택한다.
	int parent, child;
	element item, temp;
	item = min_heap[1];			//item에는 min heap의 1번째 값, 즉 가장 작은 점을 넣는다.
	temp = min_heap[min_n--];	//temp에는 min heap의 마지막 값을 넣고, min_n을 1 줄인다.
	parent = 1;
	child = 2;
	while (child <= min_n) {	//child가 min_n보다 작거나 같을 동안 반복한다.(트리의 재구성)
		if ((child < min_n) && (min_heap[child].r > min_heap[child + 1].r)) child++; //적절한 child를 선택한다.
		if (temp.r <= min_heap[child].r) break;	//temp의 r보다 자식의 r이 크거나 같을 때 종료한다.
		min_heap[parent] = min_heap[child];		//부모에 자식을 넣는다.
		parent = child;							//부모와 자식을 각각 조정한다.
		child *= 2;
	}
	min_heap[parent] = temp;	//위 연산을 통해 구한 min heap의 부모에 temp을 넣는다.(트리의 재구성 완료)
	if (min_n >= 0) {			//만약 min_n이 0 이상이라면 min heap에 원소가 남아있다는 뜻이므로
		water_dot = item.idx;	//water dot을 item.idx로 업데이트한다.
		cout << "You chose the " << num_of_dot - min_n << "th/" << num_of_dot << " point in min heap." << endl;
	}
	else {						//그렇지 않으면 더이상 min heap에 원소가 남이있지 않다는 뜻으로 에러메세지를 출력한다.
		cout << "You can't press the right key anymore. Press the left key." << endl;
	}
}