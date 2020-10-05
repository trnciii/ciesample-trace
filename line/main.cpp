/*---------------------------------------------------------------------------
まず、一本だけ線を描いてみましょう。
ウインドウの大きさは、main関数の中で(600×600)、
座標系はmyReshapeの中の、glOrthoの中で与えています。　x,y,zすべて-1.0〜1.0です。
左右方向がx, 上下方向がy, 奥行き方向がzです。

この座標空間の中で、(-0.5, 0.0)から(0.5, 0.0) へ線を引きます。
display関数の中、glBegin(GL_LINES); と glEnd();　の中に点を並べると、
その点の間が直線でつながれます。
----------------------------------------------------------------------------*/
//#define GLFW_DLL
#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"
#include <math.h>

//--初期化処理------------------------------------------------------------------
void myinit(GLFWwindow** window)
{
    glfwInit();
    *window = glfwCreateWindow(600, 600, "lines", NULL, NULL); // 600*600の大きさで lines という名前のウィンドウをつくる
    glfwMakeContextCurrent(*window);
    glClearColor(0, 0, 0, 1); // 背景色の設定
}

//--描画内容--------------------------------------------------------------------
void display(void){
    glClear(GL_COLOR_BUFFER_BIT);    //画面全体を背景色で塗りつぶす

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                //単位行列を行列スタックに読み込む

    glColor3f(1.0f, 1.0f, 1.0f);    //頂点カラーの指定( R, G, B すべてが1.0fなら白)
    glBegin(GL_LINES);                //glBegin(GL_LINES)とglEnd()の間に
        glVertex2f( -0.5f, 0.0f);   //描画したい直線の頂点を並べる。
        glVertex2f(  0.5f, 0.0f);
    glEnd();                        //ここまでで、ひとつのオブジェクトの宣言がおわる
}

//--メイン関数------------------------------------------------------------------
int main(void)
{
    //初期化処理 (ウィンドウサイズや表示位置、タイトル、背景色、...を決める)
    //----------------------------------------------------------------
    GLFWwindow* window; // ウィンドウの変数をつくる
    myinit(&window); // ウィンドウのポインタを渡して初期化
    
    //イベント処理ループ
    //--------------------------------------------------------
    do{
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while( !glfwWindowShouldClose(window) );//ウィンドウが表示されるかぎりループする

    glfwTerminate();

    return 0;
}
