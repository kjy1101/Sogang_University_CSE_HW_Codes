#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key); // Traps escape key if exit disabled
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		bool readFile();
		void freeMemory();
		bool DFS();
		void dfsdraw();
		bool BFS();
		void bfsdraw();

		int HEIGHT;//미로의 높이
		int WIDTH;//미로의 너비
	//	char** input;//텍스트 파일의 모든 정보를 담는 이차원 배열이다.
	//	int** visited;//방문여부를 저장할 포인터
	//	int maze_col;//미로칸의 열의 인덱스를 가리킨다.
	//	int maze_row;//미로칸의 행의 인덱스를 가리킨다.

		//그래프를 adjacency list로 나타내기 위한 구조체
		typedef struct Node {
			int index;
			struct Node *next;
		}Node;
		Node **vertex;

		int *path = new int[1000000];
		int *other_path = new int[1000000];
		int idx;
		int other_idx;
		int dfsdraw_flag = 0;

		int *parent = new int[1000000];
		int bfsdraw_flag = 0;
		int bfs_idx;
		int *bfs_path = new int[1000000];
		int *bfs_other_path = new int[1000000];
		int bfs_other_idx;

		int k;
		int isOpen; //파일이 열렸는지를 판단하는 변수. 0이면 안열렸고 1이면 열렸다.
		int isDFS;//DFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
		int isBFS;//BFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
		// Menu
		ofxWinMenu * menu; // Menu object
		void appMenuFunction(string title, bool bChecked); // Menu return function

		// Used by example app
		ofTrueTypeFont myFont;
        ofImage myImage;
		float windowWidth, windowHeight;
		HWND hWnd; // Application window
		HWND hWndForeground; // current foreground window

		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;
		bool isdfs;
		// Example functions
 		void doFullScreen(bool bFull);
		void doTopmost(bool bTop);

};
