#pragma once

#include "ECommon.h"
#include "EVector.h"
namespace E3D
{
	enum class LIGHT_TYPE
	{
		LIGHT_AMEIENT = 0,		//������
		LIGHT_DIRECTION = 1,	//ƽ�й�
		LIGHT_POINT = 2,		//���Դ
	};

	struct ELight
	{
		EInt		id;				//�ƹ�ķ���ID��ȫ��Ψһ
		EBool		lightOn;		//�ƹ��Ƿ�����

		LIGHT_TYPE	lightType;		//�ƹ�����
		EFloat		power;			//�ƹ��ǿ�ȣ�Ĭ��Ϊ1.0f
		EFloat		shadowFactor;	//�ƹⱳ��ǿ�ȣ�Ĭ��Ϊ0.05f
		EColor		ambient;		//�ƹ�Ļ���ɫ��������ʹ�ã�
		EColor		diffuse;		//�ƹ���������ɫ
		EColor		specular;		//�ƹ�߹���ɫ

		EVector4D	position;		//�ƹ���������λ��
		EVector4D	direction;		//��Դ���򣬵�ƹ���Ч
		EVector4D	transPositon;	//�ƹ����������ϵλ��
		EVector4D	transDirection;	//���������ϵ��Դ���򣬵�ƹ���Ч

		EFloat		kc, kl, kq;		//˥������

		EFloat		spot_inner;		//�۹����׶��
		EFloat		

	};


}