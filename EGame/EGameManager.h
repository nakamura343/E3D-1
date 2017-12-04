#pragma once
#include "ECommon.h"
#include <list>
#include <vector>

namespace E3D
{
	enum class SOUND_TYPE
	{
		SOUND_BACKGROUND,
		SOUND_FIRE,
		SOUND_EXPLODE,
	};

	class EMesh;
	class EBullet;
	class ETank;
	class EPlayerController;
	class ESceneManager;
	class EGameManager
	{
		typedef std::list<EBullet*>::iterator BulletIter;
		typedef std::list<ETank*>::iterator TankIter;

	public:
		EGameManager(ESceneManager* scene);
		~EGameManager();

		//��ʼ��Ϸ
		void startGame(EInt maxEnemyNumber = 10);
		EBool isGameBegin() const { return mMaxEnemyNumber > 0; }
		//�Ƿ������Ϸ
		EBool finishGame() const;

		//���ٵ�����Ŀ
		EInt getDestroyEnemyNumber() const { return mCurrentEnemyNumber; }
		//ʣ�������Ŀ
		EInt getLastEnemyNumber() const { return mMaxEnemyNumber - mCurrentEnemyNumber; }

		//�����ӵ�
		EBullet* createBullet(ETank* owner);
		void destroyBullet(EBullet* bullet);
		//����AI̹��
		ETank* createAITank(const EVector3D& pos);
		//��ȡ��ǰ��ɫ̹�˵Ŀ�����
		EPlayerController* getPlayerController() { return mMainPlayer; }

		//��������
		void playSound(SOUND_TYPE sound, EBool loop = false);

		//��ó���������
		ESceneManager* getSceneManager() { return mScene; }

		//���س�����ͼ
		EBool loadMap(const EString& mapName);
		void changeMap(const EString& mapName);
		EString getCurrentMapName() const { return mCurMap; }
		//��ȡ��ͼ�Ŀ��
		EFloat getMapWidth() const { return mXL; }
		EFloat getMapHeight() const { return mZL; }

		//ͨ��canGo, checkObject ��ģ��򵥵���ײЧ��
		//xzƽ��������x,z�����Ƿ��ͨ��
		EBool canGo(EFloat x, EFloat z);
		void getLogicXZ(EFloat x, EFloat z, EInt& outX, EInt &outZ);
		//����x,z���꣬�����ڴ���������壨��̬���壬�������ӵ�����̹�ˣ�
		EMesh* checkObject(EFloat x, EFloat y);
		//����x,y,z���꣬�鿴�Ƿ����Tank��û�м��з���nullptr
		ETank* checkTank(EFloat x, EFloat y, EFloat z);

		//����
		void update();

	protected:
		ESceneManager*						mScene;
		std::list<EBullet*>					mBullets;
		std::list<ETank*>					mTanks;

		EPlayerController*					mMainPlayer;

		EString								mCurMap;

		EFloat								mBlockSize;
		EInt								mX, mZ;
		EFloat								mHXL, mHZL;				//map ����
		EFloat								mXL, mZL;				//map ��/2, ��/2
		std::vector<std::vector<EInt>>		mCollisionValue;		//�洢��ǰ���ص�ͼ���ϰ���
		std::vector<std::vector<EMesh*>>	mCollisionMeshs;

		EMesh*								mTerrainMesh;

		EInt								mMaxEnemyNumber;		//��������Ŀ
		EInt								mCurrentEnemyNumber;	//��ǰ���ٵ�����
		EInt								mVisibleEnemyNumber;	//һ�������ʾ�ĵ�����Ŀ
	};
}