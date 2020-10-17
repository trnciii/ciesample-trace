
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"
#include <math.h>
#include "box.hpp"

// 登場する関数
void myinit(GLFWwindow** window);
void reshape(GLFWwindow* window, int w, int h);
void display(void);

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
}


//--再描画--------------------------------------------------------------------
void reshape(GLFWwindow* window, int w, int h)
{
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h ); //ウィンドウ全体をビューポートにする
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
   
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
    gluLookAt(
        3.0, 4.0, 5.0,    //どこから見てるか
        0.0, 0.0, 0.0,    //どこを見てるか
        0.0, 1.0, 0.0    //どの向きが上向きか
    );
}

//--描画内容--------------------------------------------------------------------
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // box.cpp内の関数を使ってボックスを描画。
    // パラメータは、makebox(ｘ方向の長さ, y方向の長さ, z方向の長さ)
    makebox(1.0,1.0,1.0);
}

//--メイン関数------------------------------------------------------------------
int main(void)
{
    //初期化処理 (ウィンドウサイズや表示位置、タイトル、背景色、...を決める)
    GLFWwindow* window; // ウィンドウの変数をつくる
    myinit(&window); // ウィンドウのポインタを渡して初期化
    

    //コールバック関数の登録 (キーボードやマウスの動きを捕まえる)
    glfwSetWindowSizeCallback(window, reshape);
    
    
    //イベント処理ループ
    do{
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while( !glfwWindowShouldClose(window) );//ウィンドウが表示されるかぎりループする

   glfwTerminate();

    return 0;
}

