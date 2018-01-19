#include "DxLib.h"
#include "./include/Input/keyboard.h"
#include "./include/Figure/Vec.h"
#include "./include/Figure/Shape.h"
#include <string>

//-------------------------------------------------------------------------------------------------------------------
//���C�����[�v�̏������܂Ƃ߂�
int ProcessLoop() {
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -1;
	if (ClearDrawScreen() != 0) return -1;
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
//�E�B���h�E�T�C�Y
const int	SCREEN_WIDTH = 800,
			SCREEN_HEIGHT = 600;
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//�}�E�X����
int Mouse;
int mouseX, mouseY;
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//�F
int white = GetColor(255, 255, 255);
//�摜�n���h��
int sushiPic[12];
//�N���b�N�񐔃J�E���^�[
int clickNum;

//���W�\����
struct Pos {
	int x;
	int y;
};
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//DrawBox������
//���̘g��\������
void DrawFrame(int x, int y, int w, int h) {
	DrawBox(x, y, x + w, y + h, white, false);
}
//DrawExtendGraph������
//���W�ƕ��A�����ŕ`�悷��
void DrawExtGraph(int x, int y, int w, int h, int picHandle) {
	DrawExtendGraph(x, y, x + w, y + h, picHandle, true);
}
//-------------------------------------------------------------------------------------------------------------------
//���i
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

Sushi sushi[12];		//���ɂȂ���i�l�^
Sushi order[12];		//�����i�l�^
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//�֐�
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
//�G���g���[�|�C���g
//-------------------------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetOutApplicationLogValidFlag(FALSE);		//���O����
	SetMainWindowText("Test");					//�E�C���h�E�^�C�g����ύX
	SetGraphMode(800, 600, 16);					//��ʉ𑜓x�A�J���[�r�b�g�ύX
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);	//��ʃT�C�Y�ύX
	ChangeWindowMode(TRUE), SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�


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
	//���C�����[�v
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
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) break;  //Esc�L�[�������ꂽ��I��

	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}