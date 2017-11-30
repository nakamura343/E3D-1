#pragma once

#include "EObject.h"
#include "ESceneManager.h"
#include <list>

namespace E3D
{
	//�ӵ�����
	enum class BulletType
	{
		BULLET_BALL,	//�����ӵ�
		BULLET_ROCKET,	//������ӵ�
	};

	//̹������
	enum class TankType
	{
		TANK_AI,
		TANK_PLAYER,
	};

	//Tank�Ļ��࣬Tank�������֣�һ�������Դ���һ�����ǳ����Դ�������ת
	//�Դ��ǻ��ڳ����ƶ���
	class EBullet;
	class ECamera;
	class EGameManeger;
	class ETank : public EObject
	{
		typedef std::list<EBullet*>::iterator BulletIter;

	public:
		virtual ~ETank();

		//�ƶ�Tank
		void move(const EVector3D& mov);
		//��ǰ�ƶ�Tank,ָ���յ�ǰTank�ĳ���Ϊǰ
		EBool moveUp();
		//����ƶ�Tank,ָ���յ�ǰTank�ĳ���ķ�����
		EBool moveDown();

		//����תTank����
		void turnLeft();
		//����תturnRight();
		void turnRight();

		//��׼������ת
		void fireAimLeft();
		//��׼������ת
		void fireAimRight();

		//��õ�ǰTank����������
		EVector3D getPosition() const { return mBody->getPosition(); }
		void setPosition(const EVector3D& pos);

		//Tank������ת������Ϊ�Ƕ�
		void yaw(EFloat degree);

		//�����ӵ�����BULLER_BALL, BULLET_ROCKET
		void setBulletType(BulletType type) { return mBulletType = type; }
		BulletType getBulletType() const { return mBulletType; }
		TankType getTankType() { return mTankType; }

		//�Ƿ�ɼ�
		EBool isVisible() const { return mBody->isVisible(); }
		void setVisible(EBool visible);

		//�����ĵ��Ƿ���Tank�İ�Χ����
		EBool intersect(const EVector3D& point);

		//�����к��Զ�����
		virtual void onHited();
		//����
		virtual void fire();
		//����
		virtual void update();
		//��ȡ�����Ӧ���ƶ�������
		EVector3D getCameraStep() const { return mMoveVec; }

	protected:
		friend class EGameManager;
		friend class EPlyaerController;
		ETank(const EString& name, const EString& meshName, EGameManager* gameMgr);

		//������׼�������ӵ����䷽��
		void updateFireDir(EFloat degree);

	protected:
		EMesh* mHead;
		EMesh* mBody;

		EVector3D		mMoveVec;	//�����Ӧ���ƶ�������

		EVector3D		mFireDir;	//������
		EFloat			mSpeed;		//�ƶ��ٶ�
		EFloat			mFireFrequency;	//����Ƶ��

		//ECamera* mCamera;
		EInt			mLastFire;	//��ʼʱ���¼
		EFloat			mColOffset;	//��ײƫ����

		ESceneManager*	mScene;		
		EGameManager*	mGameMgr;

		BulletType		mBulletType;
		TankType		mTankType;
	};
}