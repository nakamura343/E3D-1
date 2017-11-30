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
		//��ǰ�ƶ�Tank,���յ�ǰTank�ĳ���Ϊǰ
		EBool moveUp();

		//����תTank����
		void turnLeft();
		//����תturnRight();

		//��׼������ת
		void fireAimLeft();
		//��׼������ת
		void fireAimRight();

		//��õ�ǰTank����������
		EVector3D getPosition() const { return mBody->getPosition(); }
		void setPosition(const EVector3D& pos);

		//Tank������ת������Ϊ�Ƕ�
		void yaw(EFloat degree);
	};
}