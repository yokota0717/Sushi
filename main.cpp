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
int Mouse, preMouse;
int mouseX, mouseY;
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//�F
int white = GetColor(255, 255, 255);
int red = GetColor(255, 0, 0);
//�摜�n���h��
int netaPic[9];
int sushiPic[9];
//�N���b�N�񐔃J�E���^�[
int clickNum;
//��������i�J�E���^�[
int makeCnt;
////�N���b�N�����l�^�ۊǗp
//int clickNeta;


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

Sushi sushi[9];		//���ɂȂ���i�l�^
Sushi order[9];		//�����i�l�^
Sushi kansei[9];	//�����`���i
//-------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------
//�֐�
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
	if (((Mouse & MOUSE_INPUT_LEFT)!=0)&&((preMouse&MOUSE_INPUT_LEFT)==0)) {	//���N���b�N���ꂽ�u�ԂȂ�
		Pos mousePos;
		mousePos.x = mouseX / 80;
		mousePos.y = mouseY / 80;
		if (mousePos.x == 0 && mousePos.y == 0) {	//�V�������N���b�N
			order[clickNum].neta = syari;
			clickNum++;
		}
		else if (mousePos.x == 1 && mousePos.y == 0) {	//�ʎq���N���b�N
			order[clickNum].neta = tamago;
			clickNum++;
		}
		else if (mousePos.x == 2 && mousePos.y == 0) {	//�T�[�������N���b�N
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
		if (mouseX >= 680 && mouseX < 780 && mouseY >= 0 && mouseY < 100) {		//Make��`�����N���b�N
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
//�G���g���[�|�C���g
//-------------------------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetOutApplicationLogValidFlag(FALSE);		//���O����
	SetMainWindowText("Test");					//�E�C���h�E�^�C�g����ύX
	SetGraphMode(800, 600, 16);					//��ʉ𑜓x�A�J���[�r�b�g�ύX
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);	//��ʃT�C�Y�ύX
	ChangeWindowMode(TRUE), SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�


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
	//���C�����[�v
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
		if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) break;  //Esc�L�[�������ꂽ��I��

	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}