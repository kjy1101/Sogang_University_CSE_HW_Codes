#include "ofApp.h"
#include <iostream>
#include <stack>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isdfs = false;
	isOpen = 0;
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth()-windowWidth)/2, (ofGetScreenHeight()-windowHeight)/2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked
	
	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS",false,false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default)
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();

} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if(title == "Open") {
		readFile();
	}
	if(title == "Exit") {
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if(title == "Show DFS") {
		//bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			DFS();
			bShowInfo = bChecked;
		}
		else
			cout << "you must open file first" << endl;
		
	}

	if(title == "Show BFS") {
		doTopmost(bChecked); // Use the checked value directly

	}

	if(title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if(title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
//	ofSetColor(100);
	ofSetColor(0, 0, 128);
	ofSetLineWidth(5);
	int i, j;
	
	// TO DO : DRAW MAZE; 
	// 저장된 자료구조를 이용해 미로를 그린다.
	// add code here
	Node *cur;
	int x, y;
	int up = 0, left = 0;
	for (int i = 0; i < HEIGHT*WIDTH; i++) {
		cur = vertex[i]->next;
		x = (i % WIDTH) * 50;
		y = (i / WIDTH) * 50;
		up = 0;
		left = 0;
		while (cur != NULL) {
			if (cur->index == i - WIDTH) {
				//위
				up = 1;
			}
			else if (cur->index == i - 1) {
				//왼쪽
				left = 1;
			}
			cur = cur->next;
		}
		if (up == 0) {
			ofDrawLine(x, y, x + 50, y);
		}
		if (left == 0) {
			ofDrawLine(x, y, x, y + 50);
		}
	}
	ofDrawLine(WIDTH*50, 0, WIDTH*50, HEIGHT * 50);
	ofDrawLine(0, HEIGHT*50, WIDTH * 50, HEIGHT*50);

	if (dfsdraw_flag == 1) dfsdraw();

	if (isdfs)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen)
			dfsdraw();
		else
			cout << "You must open file first" << endl;
	}
	if(bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight()-20);
	}

} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if(bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else { 
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU)); 
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth()-ofGetWidth())/2, (ofGetScreenHeight()-ofGetHeight())/2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if(bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if(bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if(GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	// Escape key exit has been disabled but it can be checked here
	if(key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if(bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if(key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if(key == 'f') {
		bFullscreen = !bFullscreen;	
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
bool ofApp::readFile()
{
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;
	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		cout << "file name is " << fileName << endl;
		filePath = openFileResult.getPath();
		printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(fileName);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				cout << "We found the target file." << endl;
				isOpen = 1;
			}

			ofBuffer buffer(file);
			freeMemory();
			dfsdraw_flag = 0;
			// Input_flag is a variable for indication the type of input.
			// If input_flag is zero, then work of line input is progress.
			// If input_flag is one, then work of dot input is progress.
			int input_flag = 0;

			// Idx is a variable for index of array.
			int idx = 0;

			// Read file line by line
			int cnt = 0;

			// TODO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다

			// 1. HEIGHT와 WIDTH 계산하기
			string line;
			for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
				line = *it;
		//		cout << line << endl;
				cnt++;
			}

			int cnt_w = 0;
			while (1) {
				if (line[cnt_w] == '\0') break;
				cnt_w++;
			}
			
			HEIGHT = (cnt - 1) / 2;
			WIDTH = (cnt_w - 1) / 2;
		//	cout << "height: " << HEIGHT << endl;
		//	cout << "width: " << WIDTH << endl;

			//2. 그래프를 나타낼 adjacency list 만들기
			vertex = (Node**)malloc(sizeof(Node*)*(HEIGHT*WIDTH));
			for (int i = 0; i < HEIGHT*WIDTH; i++) {
				vertex[i] = (Node*)malloc(sizeof(Node));
				vertex[i]->index = i;
				vertex[i]->next = NULL;
			}

			int line_num = 0;
			for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
				line = *it;
			//	cout << line << endl;

				//위쪽 벽 라인
				if (line_num % 2 == 0) {
					for (int i = 0; i < WIDTH * 2; i += 2) {
						if (line[i + 1] == ' ') {
							//line[i]: '+', line[i+1]: '-' or ' '
							//빈칸이면 edge 생성(위쪽벽이 뚫려있음)
						//	cout << "up wall[" << i + 1 << "] is space." << endl;
							//n번째 줄을 읽고 있을 때 vertex의 인덱스 [i/2]+WIDTH*n
							int v_index = (i / 2) + WIDTH * (line_num / 2);
							Node *newnode = (Node*)malloc(sizeof(Node));
							newnode->index = v_index - WIDTH;
							newnode->next = vertex[v_index]->next;
							vertex[v_index]->next = newnode;
							//반대도 이어줘야 함
							Node *newnode2 = (Node*)malloc(sizeof(Node));
							newnode2->index = v_index;
							newnode2->next = vertex[v_index - WIDTH]->next;
							vertex[v_index - WIDTH]->next = newnode2;

						//	cout << "vertex[" << v_index << "] -> " << vertex[v_index]->next->index << endl;
						//	cout << "vertex[" << v_index-WIDTH << "] -> " << vertex[v_index-WIDTH]->next->index << endl;
						}
					}
				}
				
				//왼쪽 벽 라인
				else {
					for (int i = 0; i < WIDTH * 2; i += 2) {
						if (line[i] == ' ') {
							//line[i]: '|' or ' ', line[i+1]: ' '
							//빈칸이면 edge 생성(왼쪽벽이 뚫려있음)
						//	cout << "left wall[" << i << "] is space." << endl;
							//n번째 줄을 읽고 있을 때 vertex의 인덱스 [i/2]+WIDTH*n
							int v_index = (i / 2) + WIDTH * ((line_num - 1) / 2);
							Node *newnode = (Node*)malloc(sizeof(Node));
							newnode->index = v_index - 1;
							newnode->next = vertex[v_index]->next;
							vertex[v_index]->next = newnode;
							//반대도 이어줘야 함
							Node *newnode2 = (Node*)malloc(sizeof(Node));
							newnode2->index = v_index;
							newnode2->next = vertex[v_index - 1]->next;
							vertex[v_index - 1]->next = newnode2;

						//	cout << "vertex[" << v_index << "] -> " << vertex[v_index]->next->index << endl;
						//	cout << "vertex[" << v_index - 1 << "] -> " << vertex[v_index - 1]->next->index << endl;
						}
					}
				}

				line_num++;
			}

			//3. adjacency list 확인
		/*	cout << "==ADJACENCY LIST==" << endl;
			Node *cur;
			for (int i = 0; i < HEIGHT*WIDTH; i++) {
				cur = vertex[i]->next;
				cout << "vertex[" << i << "]";
				while (cur != NULL) {
					cout << " -> " << cur->index;
					cur = cur->next;
				}
				cout << endl;
			}*/
			return true;
		}
		else {
			printf("  Needs a '.maz' extension\n");
			return false;
		}
	}
}
void ofApp::freeMemory() {
//	cout << "Free memory start" << endl;
	//TO DO
	// malloc한 memory를 free해주는 함수
	Node *cur;
	Node *prev;
	for (int i = 0; i < HEIGHT*WIDTH; i++) {
		cur = vertex[i]->next;
		while (cur != NULL) {
			prev = cur;
			cur = cur->next;
			if (prev != NULL) {
				free(prev);
			}
		}
	}
	for (int i = 0; i < HEIGHT*WIDTH; i++) {
		free(vertex[i]);
	}
//	cout << "Free memory end" << endl;
}

bool ofApp::DFS()//DFS탐색을 하는 함수
{
	//TO DO
	//DFS탐색을 하는 함수 (3주차)
	//S.push(), S.size(), S.top(), S.pop(), S.empty()

	int target = HEIGHT*WIDTH - 1;
	int *visited = new int[HEIGHT*WIDTH];
	for (int i = 0; i < HEIGHT*WIDTH; i++) {
		visited[i] = 0;
	}

	stack <int> S;
	S.push(0);
	visited[0] = 1;
	int unvisited_flag = 0;
	int unvisited_node;
	Node *cur;
	other_idx = 0;

	while (1) {
	//	if (S.empty()) break;
		if (S.top() == target) break;
		unvisited_flag = 0;
		cur = vertex[S.top()]->next;
		while (cur != NULL) {
			if (visited[cur->index] == 0) {
				unvisited_flag = 1;
				unvisited_node = cur->index;
			}
			cur = cur->next;
		}
		if (unvisited_flag == 1) {
			//unvisited flag가 1이면 아직 방문하지 않은 인접 정점이 적어도 한 개 있다는 뜻
			S.push(unvisited_node);
			visited[unvisited_node] = 1;
		}
		else {
			//unvisited flag가 0이면 모든 인접 정점을 다 방문했다는 뜻
			other_path[other_idx] = S.top();
			other_idx++;
			S.pop();
			other_path[other_idx] = S.top();
			other_idx++;
		}
	}
	idx = 0;
	while (!S.empty()) {
		path[idx] = S.top();
		idx++;
		S.pop();
	}

/*	for (int i = 0; i < idx; i++) {
		cout << path[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < other_idx; i+=2) {
		cout << other_path[i] << ", " << other_path[i + 1] << endl;
	}
	cout << endl;*/
	dfsdraw_flag = 1;
	return 0;
}

void ofApp::dfsdraw()
{
	//TO DO 
	//DFS를 수행한 결과를 그린다. (3주차 내용)
	int i, x1, y1, x2, y2;
	ofSetColor(0, 200, 12);
	ofSetLineWidth(7);
	for (i = 0; i < other_idx; i += 2) {
		x1 = (other_path[i] % WIDTH) * 50 + 25;
		y1 = (other_path[i] / WIDTH) * 50 + 25;
		x2 = (other_path[i + 1] % WIDTH) * 50 + 25;
		y2 = (other_path[i + 1] / WIDTH) * 50 + 25;
		ofDrawLine(x1, y1, x2, y2);
	}

	ofSetColor(200, 0, 12);
	for (i = 0; i < idx - 1; i++) {
		x1 = (path[i] % WIDTH) * 50 + 25;
		y1 = (path[i] / WIDTH) * 50 + 25;
		x2 = (path[i+1] % WIDTH) * 50 + 25;
		y2 = (path[i+1] / WIDTH) * 50 + 25;
		ofDrawLine(x1, y1, x2, y2);
	}
	
}

