#include "trace.h"

#define CUBE_NUM	256
#define MAX_LIFE	256.0

GLfloat red[]       = { 0.8f, 0.3f, 0.3f, 1.0f };
GLfloat green[]     = { 0.2f, 0.8f, 0.2f, 1.0f };
GLfloat yellow[]    = { 1.0f, 1.0f, 0.0f, 1.0f };

double stick_x = 0.0;
double stick_y = 0.0;

double cube_x[256];
double cube_y[256];

int cube_life[256];

// 登場する関数(いつもの)
void myinit(GLFWwindow** window);
void reshape(GLFWwindow* window, int w, int h);
void display(void);

// 入力を受け付ける関数
void KeyFunc(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonFunc(GLFWwindow* window, int button, int action, int mods);
void MousePosFunc(GLFWwindow* window, double x, double y);
void MouseWheelFunc(GLFWwindow* window, double x, double y);

//--初期化—------------------------------------------------------------------
void myinit(GLFWwindow** window)
{
	glfwInit();
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    
	int w = 600; // ウィンドウの幅
	int h = 600; // ウィンドウの高さ
	*window = glfwCreateWindow(w, h, "surface", NULL, NULL); // w*hの大きさで surface という名前のウィンドウをつくる
	glfwMakeContextCurrent(*window);
	glClearColor(0, 0, 0, 1); // 背景色の設定
	
	reshape(*window, w, h); // 視点の初期化をおこなう
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light0pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };    //ライト０の位置を定義
	GLfloat light_diffuse[] ={ 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_ambient[] ={ 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_specular[]={ 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_emission[]={ 0.0f, 0.0f, 0.0f, 1.0f };

	glLightfv( GL_LIGHT0, GL_POSITION, light0pos );
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  light_diffuse );
	glLightfv( GL_LIGHT0, GL_AMBIENT,  light_ambient );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );
	glLightfv( GL_LIGHT0, GL_EMISSION, light_emission );

	GLfloat low_shiness[] = {50};                //鏡面反射係数を定義
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shiness );
	
	for( int i = 0; i < CUBE_NUM; i++ )
	{
		cube_life[i] = 0;
	}
}


//--再描画--------------------------------------------------------------------
void reshape(GLFWwindow* window, int w, int h)
{
	glViewport( 0, 0, (GLsizei)w, (GLsizei)h ); //ウィンドウ全体をビューポートにする
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho( -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 );
}

//--キーボード関数--------------------------------------------------------------
void KeyFunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// ↑
	if( key == GLFW_KEY_UP && action == GLFW_PRESS ){
		printf("↑\n");
	}
	
	// ↓
	if( key == GLFW_KEY_DOWN && action == GLFW_PRESS ){
		printf("↓\n");
	}
	
	// ←
	if( key == GLFW_KEY_LEFT && action == GLFW_PRESS ){
		printf("←\n");
	}
	
	// →
	if( key == GLFW_KEY_RIGHT && action == GLFW_PRESS ){
		printf("→\n");
	}
	
	// スペースキー
	if( key == GLFW_KEY_SPACE && action == GLFW_PRESS ){
		printf("SPACE\n");
	}
	
	// Aキー
	if( key == 'A' && action == GLFW_PRESS ){
		printf( "A\n" );
	}
}

//--マウスボタン関数------------------------------------------------------------
void MouseButtonFunc(GLFWwindow* window, int button, int action, int mods)
{
}

//--マウスの位置関数------------------------------------------------------------
void MousePosFunc(GLFWwindow* window, double x, double y)
{
	// 画面サイズの取得
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	
	stick_x =  ( x - w/2 ) / (w/2);//マウスを右に動かしたら、スティッキも右に
	stick_y = -( y - h/2 ) / (h/2);//マウスを下に動かしたら、スティッキも下に
}

//--マウスのホイール関数--------------------------------------------------------
void MouseWheelFunc(GLFWwindow* window, double x, double y)
{
}


//--描画内容--------------------------------------------------------------------
void display(int frame)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//バッファクリア
	glClearColor(0.0, 0.0, 0.5, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//オブジェクトを準備
	GLUquadricObj *sphere = gluNewQuadric();
	GLUquadricObj *cylinder = gluNewQuadric();


	// ステッキの描画
	glPushMatrix();
		glTranslated( stick_x, stick_y, 0.0 );
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
		gluSphere(sphere, 0.05, 10, 10);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
		glRotated(90.0, 1.0, 0.0, 0.4);
		gluCylinder(cylinder, 0.01, 0.01, 0.4, 10, 10);
	glPopMatrix();
}

//--メイン関数------------------------------------------------------------------
int main(void)
{
	//初期化処理 (ウィンドウサイズや表示位置、タイトル、背景色、...を決める)
	GLFWwindow* window; // ウィンドウの変数をつくる
	myinit(&window); // ウィンドウのポインタを渡して初期化
	

	//コールバック関数の登録 (キーボードやマウスの動きを捕まえる)
	glfwSetWindowSizeCallback(window, reshape);             // ウィンドウの大きさが変わると呼び出される
	glfwSetKeyCallback(window, KeyFunc);                    // キーボードを触ると呼び出される
	glfwSetMouseButtonCallback(window, MouseButtonFunc);    // マウスのボタンを押すと呼び出される
	glfwSetCursorPosCallback(window, MousePosFunc);         // マウスを動かすと呼び出される
	glfwSetScrollCallback(window, MouseWheelFunc);          // マウスホイールを動かすと呼び出される
	
	
	//イベント処理ループ
	int frame = 0;
	
	do{
		frame++;
		if(frame>300) frame = 0;
		
		display(frame);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}while( !glfwWindowShouldClose(window) );//ウィンドウが表示されるかぎりループする

   glfwTerminate();

	return 0;
}

