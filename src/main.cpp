
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"
#include <math.h>
#include "box.hpp"
#include <stdio.h>

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
    
    int w = 600; // ウィンドウの幅
    int h = 600; // ウィンドウの高さ
    *window = glfwCreateWindow(w, h, "surface", NULL, NULL); // w*hの大きさで surface という名前のウィンドウをつくる
    glfwMakeContextCurrent(*window);
    glClearColor(0, 0, 0, 1); // 背景色の設定
    
    reshape(*window, w, h); // 視点の初期化をおこなう
    glEnable(GL_DEPTH_TEST);
}


//--再描画--------------------------------------------------------------------
void reshape(GLFWwindow* window, int w, int h)
{
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h ); //ウィンドウ全体をビューポートにする
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
   
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
    gluLookAt(
        0.0, 4.0, 5.0,    //どこから見てるか
        0.0, 0.0, 0.0,    //どこを見てるか
        0.0, 1.0, 0.0    //どの向きが上向きか
    );
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
}

//--マウスのホイール関数--------------------------------------------------------
void MouseWheelFunc(GLFWwindow* window, double x, double y)
{
}


//--描画内容--------------------------------------------------------------------
void display(int frame)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    makebox(1.0, 1.0, 1.0, GL_POLYGON);
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

