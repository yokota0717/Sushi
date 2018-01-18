#pragma once
#include "../Figure/Vec.h"
#include "../Figure/Shape.h"

//当たり判定を行うクラス
class Collider {
	Collider() {};
	~Collider() {};

	//線分segmentと直線lineの区別いるかな...

	//あたり判定関数
	virtual bool Collision(Vec) = 0;				//点
	virtual bool Collision(Vec,Vec) = 0;			//線分
	virtual bool Collision(Box2D) = 0;				//矩形
	virtual bool Collision(Circle) = 0;				//円

	
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