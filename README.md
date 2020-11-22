この資料は、従来版の後半第1回 - キーボードやマウスによる入力 に対応します。

## 目次
* [準備](#準備)
* [プログラムの解説](#プログラムの解説)
	* [キーボードに連動する関数](#キーボードに連動する関数)
	* [コールバック関数の登録](#コールバック関数の登録)
	* [他のコールバック関数](#他のコールバック関数)
* [方向キーで立方体を動かす](#方向キーで立方体を動かす)
	* [プログラムの書き換え](#プログラムの書き換え)
	* [課題1](#課題1)
* ["押しっぱなし"の取得](#"押しっぱなし"の取得)
	* [フラグによる制御](#フラグによる制御)
	* [課題2](#課題2)
* [](#)


## 準備
ここのコードをダウンロード、解凍してください。sample.xcodeproj を開き実行すると立方体が表示されることを確認してください。
また、矢印キーを押すとコンソールに対応した文字が出力されることを確認してください。
コンソールはXcodeウィンドウの右下にあります。

|ウィンドウ|コンソール|
|:-:|:-:|
| <img src="docs/cube.png" width="400"> | <img src="docs/console.png" width="350"> |

## プログラムの解説
今回からキーボードやマウスの動きなど、ユーザーによる入力を利用したプログラムを書きます。
そのために**コールバック関数**という仕組みを利用します。
これはGLFWのほうで検知した特定の動作に対して、登録した好きな関数を実行できるというものです。

実際にキーボードにあわせて矢印を出力する部分がどのように書かれているか見ていきます。

### キーボードに連動する関数
キーボードが押されたときに動作する関数として、`KeyFunc`を定義しました。
関数の引数は[仕様](https://www.glfw.org/docs/3.3/group__input.html#ga0192a232a41e4e82948217c8ba94fdfd)で決まっており、キーの種類や動作を表す変数として関数内で使うことができます。

```cpp
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
```

この関数では、どのキーが押されたかによって処理を分岐し、文字を出力しています。

キーの種類は関数の第二引数`int key` に入っています。
文字の場合は文字コード、矢印など特殊なものはGLFWで用意された `GLFW_KEY_UP` などの値が入っています。

キーが押されたことを判定するために、分岐のときに第四引数`int action` の値も同時に確認します。
この変数には、押された瞬間に`GLFW_PRESS`、離された瞬間には`GLFW_RELEASE`がはいっています。

### コールバック関数の登録
プログラムの最初に、定義した関数`KeyFunc`をGLFWにわかるように登録します。
これは `main`関数内の `glfwSetKeyCallback(window, KeyFunc);` という部分で行っています。

### 他のコールバック関数
キーボードの検出のほかにも以下のコールバック関数を用意しています。
プログラムを読み、それぞれの引数と関数を登録している部分を確認してください。

|関数名	|内容	|引数(使うもの)	|
|:-		|:-		|:-				|
|KeyFunc            |キーボードの動作を検出		|キーや動作の種類		|
|MouseButtonFunc    |マウスボタンの動作を検出	|ボタンと動作の種類		|
|MousePosFunc       |マウスの移動を検出     	|座標(x, y)			|
|MouseWheelFunc     |ホイールの動作を検出		|ホイールの移動(x, y)	|


## 方向キーで立方体を動かす
入力された方向キーで立方体を移動させます。↑キーで上、↓キーで下に動くようにします。

### プログラムの書き換え

まず、位置を格納する大域変数を用意します。

```cpp
#include "GLFW/glfw3.h"
#include <math.h>
#include "box.hpp"
#include <stdio.h>
#include <stdio.h>

double pos_z = 0; // 追加

// 登場する関数(いつもの)
void myinit(GLFWwindow** window);
```
次に`KeyFunc`の中でキーボードの入力によって`pos_z`を更新します。
```cpp
void KeyFunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // ↑
    if( key == GLFW_KEY_UP && action == GLFW_PRESS ){
        printf("↑\n");
        pos_z -= 0.5; // 追加
    }
    
    // ↓
    if( key == GLFW_KEY_DOWN && action == GLFW_PRESS ){
        printf("↓\n");
        pos_z += 0.5; // 追加
    }
// ...
```

最後`display`のほうで立方体を`pos_z`だけ移動させます。

```cpp
void display(int frame)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated( 0.0, 0.0, pos_z );
    makebox(1.0, 1.0, 1.0, GL_POLYGON);
}
```
これで実行すると、矢印キーの上下に応じて立方体が移動します。

### 課題1
矢印キーの左右に応じて立方体が移動するようにしてください。


## "押しっぱなし"の取得
今までの流れで、矢印キーを押す事で立方体が動くようになりました。
ただ、動かし続けるためにはキーボードを連打する必要があります。
ここでは、「押しっぱなし」の取得をしたいと思います。

### フラグによる制御
`KeyFunc`ではキーが押された/離された瞬間のみを検知することができますが、その後キーが押されたままであるかはわかりません。
そのため、キーが押されているか否かの変数を用意して、これをもとに移動をおこないます。

以下のように変数の用意と移動の書き換えをおこないます。
ここで使う`bool` は真偽値を扱う型で、値として`true` または `false` をとります。

```cpp
double pos_x = 0.0;
double pos_z = 0.0;

// 大域変数として以下の各方向のフラグを定義
bool up	= false;
bool down	= false;
bool left	= false;
bool right	= false;

// 中略

//--描画内容--------------------------------------------------------------------
void display(int frame)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // フラグがtrueのときに各方向に移動する
    if( up ){
        pos_z -= 0.1;
    }
    if( down ){
        pos_z += 0.1;
    }
    if( left ){
        pos_x -= 0.1;
    }
    if( right ){
        pos_x += 0.1;
    }

    glTranslated( pos_x, 0.0, pos_z );
    makebox(1.0, 1.0, 1.0, GL_POLYGON);
}
```

最後に、`KeyFunc`の中で各方向のフラグを更新します。

### 課題2
`KeyFunc`を書き換えて、矢印キーとフラグ変数`up, down, left, right`が連動するようにしてください。
キーを押した瞬間に`true`, キーを離した瞬間に`false`を代入すればいいです。

## 方向キーでキャラクターを動かす



















