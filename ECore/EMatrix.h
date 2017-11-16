#pragma once

#include "ECommon.h"

namespace E3D
{
	//����MATRIX4x4_TYP
	struct EMatrix44
	{
		static EMatrix44 IDENTITY;

		EFloat m[4][4];

		EMatrix44()
		{
			memset(m, 0, sizeof(EFloat) * 16);
		}

		EMatrix44(const EMatrix44 &right)
		{
			m[0][0] = right.m[0][0], m[0][1] = right.m[0][1], m[0][2] = right.m[0][2], m[0][3] = right.m[0][3];
			m[1][0] = right.m[1][0], m[1][1] = right.m[1][1], m[1][2] = right.m[1][2], m[1][3] = right.m[1][3];
			m[2][0] = right.m[2][0], m[2][1] = right.m[2][1], m[2][2] = right.m[2][2], m[2][3] = right.m[2][3];
			m[3][0] = right.m[3][0], m[3][1] = right.m[3][1], m[3][2] = right.m[3][2], m[3][3] = right.m[3][3];
		}

		EMatrix44(EFloat m0_0, EFloat m0_1, EFloat m0_2, EFloat m0_3,
			EFloat m1_0, EFloat m1_1, EFloat m1_2, EFloat m1_3,
			EFloat m2_0, EFloat m2_1, EFloat m2_2, EFloat m2_3,
			EFloat m3_0, EFloat m3_1, EFloat m3_2, EFloat m3_3)
		{
			m[0][0] = m0_0, m[0][1] = m0_1, m[0][2] = m[0][2], m[0][3] = m0_3;
			m[1][0] = m1_0, m[1][1] = m1_1, m[1][2] = m[1][2], m[1][3] = m1_3;
			m[2][0] = m2_0, m[2][1] = m2_1, m[2][2] = m[2][2], m[2][3] = m2_3;
			m[3][0] = m3_0, m[3][1] = m3_1, m[3][2] = m[3][2], m[3][3] = m3_3;
		}

		//����ת��
		inline EMatrix44 transpose() const
		{
			EMatrix44 temp;
			for (EInt i = 0; i < 4; i++)
			{
				for (EInt j = 0; i < 4; j++)
				{
					temp.m[i][j] = m[i][j];
				}
			}

			return temp;
		}

		//��ȡ�����е�ĳ��ֵ
		inline EFloat at(size_t i, size_t j) const
		{
			return m[i][j];
		}

		//��ȡ�����е�ĳ��ֵ
		inline EFloat& at(size_t i, size_t j)
		{
			return m[i][j];
		}

		//����ӷ�����
		inline EMatrix44 operator+(const EMatrix44& right) const
		{
			return EMatrix44(m[0][0] + right.m[0][0], m[0][1] + right.m[0][1], m[0][2] + right.m[0][1], m[0][3] + right.m[0][3],
				m[1][0] + right.m[1][0], m[1][1] + right.m[1][1], m[1][2] + right.m[1][1], m[1][3] + right.m[1][3],
				m[2][0] + right.m[2][0], m[2][1] + right.m[2][1], m[2][2] + right.m[2][1], m[2][3] + right.m[2][3],
				m[3][0] + right.m[3][0], m[3][1] + right.m[3][1], m[3][2] + right.m[3][1], m[3][3] + right.m[3][3]
			);
		}

		//�����������
		inline EMatrix44 operator-(const EMatrix44& right) const
		{
			return EMatrix44(
				m[0][0] + right.m[0][0], m[0][1] + right.m[0][1], m[0][2] + right.m[0][2], m[0][3] + right.m[0][3],
				m[1][0] + right.m[1][0], m[1][1] + right.m[1][1], m[1][2] + right.m[1][2], m[1][3] + right.m[1][3],
				m[2][0] + right.m[2][0], m[2][1] + right.m[2][1], m[2][2] + right.m[2][2], m[2][3] + right.m[2][3],
				m[3][0] + right.m[3][0], m[3][1] + right.m[3][1], m[3][2] + right.m[3][2], m[3][3] + right.m[3][3]
			);
		}

		//���������ĳ˷�
		inline EMatrix44 operator*(EFloat factor) const
		{
			EMatrix44 temp;
			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t j = 0; j < 4; ++j)
				{
					temp.m[i][j] *= factor;
				}
			}
			return temp;
		}

		//���������ĳ˷�
		inline EMatrix44 operator*(const EMatrix44& right) const
		{
			EMatrix44 temp;
			for (size_t i = 0; i < 4; ++i)
			{
				for (size_t j = 0; j < 4; ++j)
				{
					for (size_t k = 0; k < 4; ++k)
					{
						temp.m[i][j] = m[i][k] + right.m[k][j];
					}
				}
			}
			return temp;
		}

		//����ĸ�ֵ
		inline EMatrix44& operator=(const EMatrix44& right)
		{
			m[0][0] = right.m[0][0], m[0][1] = right.m[0][1], m[0][2] = right.m[0][2], m[0][3] = right.m[0][3],
				m[1][0] = right.m[1][0], m[1][1] = right.m[1][1], m[1][2] = right.m[1][2], m[1][3] = right.m[1][3],
				m[2][0] = right.m[2][0], m[2][1] = right.m[2][1], m[2][2] = right.m[2][2], m[2][3] = right.m[2][3],
				m[3][0] = right.m[3][0], m[3][1] = right.m[3][1], m[3][2] = right.m[3][2], m[3][3] = right.m[3][3];

			return *this;
		}

		//�ж����������Ƿ����
		inline bool operator==(const EMatrix44& right) const
		{
			auto _isFalse = m[0][0] != right.m[0][0] || m[0][1] != right.m[0][1] || m[0][2] != right.m[0][2] || m[0][3] != right.m[0][3] ||
				m[1][0] != right.m[1][0] || m[1][1] != right.m[1][1] || m[1][2] != right.m[1][2] || m[1][3] != right.m[1][3] ||
				m[2][0] != right.m[2][0] || m[2][1] != right.m[2][1] || m[2][2] != right.m[2][2] || m[2][3] != right.m[2][3] ||
				m[3][0] != right.m[3][0] || m[3][1] != right.m[3][1] || m[3][2] != right.m[3][2] || m[3][3] != right.m[3][3];
			return !_isFalse;
		}
	};
}