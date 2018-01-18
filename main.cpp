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
int Mouse;
int mouseX, mouseY;
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//色
int white = GetColor(255, 255, 255);
//画像ハンドル
int sushiPic[12];
//クリック回数カウンター
int clickNum;

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
	maguro,
	toro,
	tamago,
	inari,
	ika,
	sarmon,
	buri,
	tako,
	ebi,
	akagai,
	ikura,
	uni,
	shimesaba,
	kanpachi,
	tekka,
	kappa,
	non,
};
struct Sushi
{
	Pos pos;
	SushiNeta neta;
};

Sushi sushi[12];		//元になる寿司ネタ
Sushi order[12];		//作る寿司ネタ
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//関数
void initSushi(Sushi& s, int i) {
	s.pos.x = i % 4;
	s.pos.y = i / 4;
	switch (i) {
	case 0:		s.neta = maguro;	break;
	case 1:		s.neta = toro;		break;
	case 2:		s.neta = tamago;	break;
	case 3:		s.neta = inari;		break;
	case 4:		s.neta = ika;		break;
	case 5:		s.neta = sarmon;	break;
	case 6:		s.neta = buri;		break;
	case 7:		s.neta = tako;		break;
	case 8:		s.neta = ebi;		break;
	case 9:		s.neta = akagai;	break;
	case 10:	s.neta = ikura;		break;
	case 11:	s.neta = uni;		break;
	default:	s.neta = non;
	}
}
void renderSushi(Sushi& s) {
	if (s.neta == non) return;
	DrawExtGraph(s.pos.x * 90, s.pos.y * 80, 80, 65, sushiPic[s.neta]);
}

void initOrder(Sushi& s, int i) {
	s.pos.x = i % 4;
	s.pos.y = i / 4;
	s.neta = non;
}
void renderOrder(Sushi& s) {
	if (s.neta == non) return;
	DrawExtGraph(420 + s.pos.x * 90, s.pos.y * 80, 80, 65, sushiPic[s.neta]);
}

void clickSushi() {
	if (Mouse & MOUSE_INPUT_LEFT) {
		Pos mousePos;
		mousePos.x = mouseX % 80 - 10;
		mousePos.y = mouseY % 80 - 15;
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


	LoadDivGraph("./resource/graph/sushi.jpg", 16, 4, 4, 113, 84, sushiPic);

	clickNum = 0;

	int sushiTable[] = {
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
	};
	int orderTable[12] = {};

	for (int i = 0; i < 12; ++i) {
		initSushi(sushi[i], i);
		initOrder(order[i], i);
	}

	//-------------------------------------------------------------------------------------------------------------------
	//メインループ
	//-------------------------------------------------------------------------------------------------------------------
	while (ProcessLoop() == 0) {	
		Keyboard_Update();
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

		for (int i = 0; i < 12; ++i) {
			renderSushi(sushi[i]);
			renderOrder(order[i]);
		}
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 4; ++x) {
				DrawFrame(420 + 85 * x, 10 + 85 * y, 80, 80);
			}
		}
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) break;  //Escキーが押されたら終了

	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}