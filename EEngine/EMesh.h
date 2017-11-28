#pragma once

#include "ECommon.h"
#include "ECore.h"
#include "EMaterial.h"
#include "EObject.h"

namespace E3D
{
	enum class COLLSION_TYPE
	{
		COLLSION_COLLSION,
		COLLSION_IGNORE,
	};

	class EMesh : public EObject
	{
	public:
		~EMesh();

		void setScale(const EVector3D& scale);
		void setPosition(const EVector3D& pos);
		EVector3D getPosition() const;
		void move(const EVector3D& mov);

		//�������Ƿ���Mesh�İ�Χ����,������򷵻�true, ���򷵻�false
		EBool intersect(const EVector3D& point);
		
		void setVisible(EBool visible) { mIsVisible = visible; }
		EBool isVisible() const { return mIsVisible; }

		//�Ƿ���Ҫִ���޳�����
		void setCullFlag(EBool needCull) { mObject->needCull = needCull; }

		//��y����ת
		void yaw(EFloat yDegree);
		//��z����ת
		void roll(EFloat rDegree);
		//��x����ת
		void pitch(EFloat pDegree);
		
		void setCollsionType(COLLSION_TYPE type) { mCollsionType = type; }
		COLLSION_TYPE getCollsionType() const { return mCollsionType; }

		EMaterial* getMaterial(EInt index = 0);
		void setMaterial(EInt index, EString matName);

		EObject4D* getObject() const { return mObject; }
		EInt getPolyonNumber() const { return mPolyonNumber; }
		EInt getVertexNumber() const { return mVertexNumber; }
		EInt getSubmenshNumber() const { return mSubmeshNumber; }
		
		//��ȡ�������ת�������ԽǶȱ�ʾ
		EVector3D getRotateVec() const { return mRotate; }

		//�Դ�ģ�ͽ���clone�������ٴζ��̶�ȡģ��
		EMesh* clone();

	protected:
		friend class ESceneManager;
		EMesh();
		EMesh(const EString& name, const EString& meshName);

		EObject4D*		mObject;

		EInt			mPolyonNumber;	//ģ�Ͷ���θ���
		EInt			mVertexNumber;	//ģ�Ͷ������
		EInt			mSubmeshNumber;	//ģ����ģ�͸���
		EVector3D		mRotate;		//ģ�͸�����ת����
		EBool			mIsVisible;
		COLLSION_TYPE	mCollsionType;
	};
}