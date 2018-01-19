#include "DxLib.h"
#include "./include/Input/keyboard.h"
#include "./include/Figure/Vec.h"
#include "./include/Figure/Shape.h"
#include <string>

//-------------------------------------------------------------------------------------------------------------------
//メインループの処理をまとめる
int ProcessLoop() {
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -1;
	if (ClearDrawScreen() != 0) return -1;
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
//ウィンドウサイズ
const int	SCREEN_WIDTH = 800,
			SCREEN_HEIGHT = 600;
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//マウス準備
int Mouse, preMouse;
int mouseX, mouseY;
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//色
int white = GetColor(255, 255, 255);
int red = GetColor(255, 0, 0);
//画像ハンドル
int netaPic[9];
int sushiPic[9];
//クリック回数カウンター
int clickNum;
//作った寿司カウンター
int makeCnt;
////クリックしたネタ保管用
//int clickNeta;


//座標構造体
struct Pos {
	int x;
	int y;
};
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//DrawBox改造版
//白の枠を表示する
void DrawFrame(int x, int y, int w, int h) {
	DrawBox(x, y, x + w, y + h, white, false);
}
//DrawExtendGraph改造版
//座標と幅、高さで描画する
void DrawExtGraph(int x, int y, int w, int h, int picHandle) {
	DrawExtendGraph(x, y, x + w, y + h, picHandle, true);
}
//-------------------------------------------------------------------------------------------------------------------
//寿司
enum SushiNeta {
	syari,
	tamago,
	sarmon,

	non,
};
struct Sushi
{
	Pos pos;
	SushiNeta neta;
};

Sushi sushi[9];		//元になる寿司ネタ
Sushi order[9];		//作る寿司ネタ
Sushi kansei[9];	//完成形寿司
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//関数
void initSushi(Sushi& s, int i) {
	s.pos.x = i % 3;
	s.pos.y = i / 3;
	switch (i) {
	case 0:		s.neta = syari;		break;
	case 1:		s.neta = tamago;	break;
	case 2:		s.neta = sarmon;	break;
	default:	s.neta = non;
	}
}
void renderSushi(Sushi& s) {
	if (s.neta == non) return;
	DrawExtGraph(s.pos.x * 80, s.pos.y * 80, 80, 80, netaPic[s.neta]);
}

void initOrder(Sushi& s, int i) {
	s.pos.x = i % 3;
	s.pos.y = i / 3;
	s.neta = non;
}
void renderOrder(Sushi& s) {
	if (s.neta == non) return;
	DrawExtGraph(350 + s.pos.x * 80, s.pos.y * 80, 80, 80, netaPic[s.neta]);
}

void initKansei(Sushi& s, int i) {
	s.pos.x = 5 + 90 * i;
	s.pos.y = 400;
	s.neta = non;
}
void renderKansei(Sushi& s) {
	if (s.neta == non) return;
	DrawExtGraph(s.pos.x, s.pos.y, 80, 80, sushiPic[s.neta]);
	DrawFrame(s.pos.x, s.pos.y, 80, 80);
}

void clickSushi() {
	if (((Mouse & MOUSE_INPUT_LEFT)!=0)&&((preMouse&MOUSE_INPUT_LEFT)==0)) {	//左クリックされた瞬間なら
		Pos mousePos;
		mousePos.x = mouseX / 80;
		mousePos.y = mouseY / 80;
		if (mousePos.x == 0 && mousePos.y == 0) {	//シャリをクリック
			order[clickNum].neta = syari;
			clickNum++;
		}
		else if (mousePos.x == 1 && mousePos.y == 0) {	//玉子をクリック
			order[clickNum].neta = tamago;
			clickNum++;
		}
		else if (mousePos.x == 2 && mousePos.y == 0) {	//サーモンをクリック
			order[clickNum].neta = sarmon;
			clickNum++;
		}
	}
}

void ClearNeta() {
	for (int i = 0; i < 9; ++i) {
		order[i].neta = non;
	}
	clickNum = 0;
}
void ClearSushi() {
	for (int i = 0; i < 9; ++i) {
		kansei[i].neta = non;
	}
	makeCnt = 0;
}

void MakeSushi() {
	if (((Mouse & MOUSE_INPUT_LEFT) != 0) && ((preMouse&MOUSE_INPUT_LEFT) == 0)) {
		if (mouseX >= 680 && mouseX < 780 && mouseY >= 0 && mouseY < 100) {		//Make矩形内をクリック
			if (order[0].neta == syari && order[1].neta == syari) {
				if (order[2].neta == tamago) {
					kansei[makeCnt].neta = tamago;
					makeCnt++;
				}
				else if(order[2].neta == sarmon){
					kansei[makeCnt].neta = sarmon;
					makeCnt++;
				}
			}
			ClearNeta();
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//エントリーポイント
//-------------------------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetOutApplicationLogValidFlag(FALSE);		//ログ消し
	SetMainWindowText("Test");					//ウインドウタイトルを変更
	SetGraphMode(800, 600, 16);					//画面解像度、カラービット変更
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);	//画面サイズ変更
	ChangeWindowMode(TRUE), SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定


	LoadDivGraph("./resource/graph/neta.jpg", 9, 3, 3, 256, 256, netaPic);
	LoadDivGraph("./resource/graph/kansei.png", 9, 3, 3, 256, 256, sushiPic);

	clickNum = 0;
	makeCnt = 0;
	Mouse = GetMouseInput();

	int sushiTable[] = {
		0,1,2,
		3,4,5,
		6,7,8,
	};
	int orderTable[9] = {};

	for (int i = 0; i < 9; ++i) {
		initSushi(sushi[i], i);
		initOrder(order[i], i);
		initKansei(kansei[i], i);
	}

	//-------------------------------------------------------------------------------------------------------------------
	//メインループ
	//-------------------------------------------------------------------------------------------------------------------
	while (ProcessLoop() == 0) {	
		Keyboard_Update();
		preMouse = Mouse;
		Mouse = GetMouseInput();
		
		GetMousePoint(&mouseX, &mouseY);

		//int sushiNum = 0;
		//for (int y = 0; y < 3; ++y) {
		//	for (int x = 0; x < 4; ++x) {
		//		DrawExtGraph(10 + 80*x, 15 + 70*y, 100, 100, sushiPic[sushiNum]);
		//		sushiNum++;
		//	}
		//}

		clickSushi();
		MakeSushi();

		if (Mouse&MOUSE_INPUT_RIGHT)
			ClearSushi();

		for (int i = 0; i < 9; ++i) {
			renderSushi(sushi[i]);
			renderOrder(order[i]);
			renderKansei(kansei[i]);
		}
		DrawBox(680, 0, 780, 100, white, true);
		DrawFormatString(720, 50, red, "Make");
		//for (int y = 0; y < 3; ++y) {
		//	for (int x = 0; x < 3; ++x) {
		//		DrawFrame(420 + 90 * x, 90 * y, 80, 80);
		//	}
		//}
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) break;  //Escキーが押されたら終了

	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}