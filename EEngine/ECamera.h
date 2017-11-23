#pragma once
#include "ECommon.h"
#include <map>
#include "EGraphics.h"

namespace E3D
{
	class EFrustum;

	enum class RenderMode
	{
		RENDER_WIRE,	//�߿���Ⱦ
		RENDER_SOILD,	//ʵ����Ⱦ
	};

	class ECamera
	{
	public:
		~ECamera();

		void update();

		//���ý��ü������
		void setZNear(EFloat znear);
		//����Զ�ü������
		void setZFar(EFloat zfar);

		//���������������
		void setPosition(const EVector3D& pos);
		//����������۲�㣬��lockTargetΪtrueʱ�������۲��
		void setTarget(const EVector3D& target, EBool lockTarget = false);
		void releaseTarget() { mLockTarget = false; }

		//������������ϵ�ƶ�
		void move(const EVector3D& mov);
		//������������������ƶ�
		void moveRelative(const EVector3D& mov);

		//��y����ת
		void yaw(EFloat yDegree);
		//��x����ת
		void pitch(EFloat pDegree);

		//������Ⱦģʽ���߿��ʵ��
		void setRenderMode(RenderMode mode) { mRenderMode = mode; }
		RenderMode getRenderMode() const { return mRenderMode; }

		EFrustum* getFrustum() const { return mFrustum; }

	protected:
		friend class ESceneManager;
		ECamera();

	protected:
		EFrustum* mFrustum;

		EBool mLockTarget;
		EBool mNeedUpdate;

		RenderMode mRenderMode;
	};

}