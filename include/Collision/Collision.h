#pragma once
#include "../Figure/Vec.h"
#include "../Figure/Shape.h"

//�����蔻����s���N���X
class Collider {
	Collider() {};
	~Collider() {};

	//����segment�ƒ���line�̋�ʂ��邩��...

	//�����蔻��֐�
	virtual bool Collision(Vec) = 0;				//�_
	virtual bool Collision(Vec,Vec) = 0;			//����
	virtual bool Collision(Box2D) = 0;				//��`
	virtual bool Collision(Circle) = 0;				//�~

	
};

class Box2DCollider :public Collider {
	bool Collision(Vec) override;
	bool Collision(Vec, Vec) override;
	bool Collision(Box2D) override;
	bool Collision(Circle) override;

};

class CircleCollider :public Collider {
	bool Collision(Vec) override;
	bool Collision(Vec, Vec) override;
	bool Collision(Box2D) override;
	bool Collision(Circle) override;

};