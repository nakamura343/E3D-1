#pragma once

#include "EObject.h"
#include "ESceneManager.h"
#include <list>

namespace E3D
{
	//子弹类型
	enum class BulletType
	{
		BULLET_BALL,	//球形子弹
		BULLET_ROCKET,	//火箭型子弹
	};

	//坦克类型
	enum class TankType
	{
		TANK_AI,
		TANK_PLAYER,
	};

	//Tank的基类，Tank分两部分，一部分是脑袋，一部分是车身，脑袋可以旋转
	//脑袋是基于车身移动的
	class EBullet;
	class ECamera;
	class EGameManeger;
	class ETank : public EObject
	{
		typedef std::list<EBullet*>::iterator BulletIter;

	public:
		virtual ~ETank();

		//移动Tank
		void move(const EVector3D& mov);
		//向前移动Tank,指按照当前Tank的朝向为前
		EBool moveUp();
		//向后移动Tank,指按照当前Tank的朝向的饭防线
		EBool moveDown();

		//向左转Tank车体
		void turnLeft();
		//向右转turnRight();
		void turnRight();

		//瞄准器向左转
		void fireAimLeft();
		//瞄准器向右转
		void fireAimRight();

		//获得当前Tank的世界坐标
		EVector3D getPosition() const { return mBody->getPosition(); }
		void setPosition(const EVector3D& pos);

		//Tank沿轴旋转，参数为角度
		void yaw(EFloat degree);

		//设置子弹类型BULLER_BALL, BULLET_ROCKET
		void setBulletType(BulletType type) { mBulletType = type; }
		BulletType getBulletType() const { return mBulletType; }
		TankType getTankType() { return mTankType; }

		//是否可见
		EBool isVisible() const { return mBody->isVisible(); }
		void setVisible(EBool visible);

		//给定的点是否在Tank的包围盒内
		EBool intersect(const EVector3D& point);

		//被击中后自动调用
		virtual void onHited();
		//开火
		virtual void fire();
		//更新
		virtual void update();
		//获取摄像机应该移动的向量
		EVector3D getCameraStep() const { return mMoveVec; }

	protected:
		friend class EGameManager;
		friend class EPlyaerController;
		ETank(const EString& name, const EString& meshName, EGameManager* gameMgr);

	protected:
		//更新瞄准器朝向，子弹发射方向
		void updateFireDir(EFloat degree);

	protected:
		EMesh* mHead;
		EMesh* mBody;

		EVector3D		mMoveVec;	//摄像机应该移动的向量

		EVector3D		mFireDir;	//开火方向
		EFloat			mSpeed;		//移动速度
		EFloat			mFireFrequency;	//开火频率

		//ECamera* mCamera;
		EInt			mLastFire;	//开始时间记录
		EFloat			mColOffset;	//碰撞偏移量

		ESceneManager*	mScene;		
		EGameManager*	mGameMgr;

		BulletType		mBulletType;
		TankType		mTankType;
	};
}