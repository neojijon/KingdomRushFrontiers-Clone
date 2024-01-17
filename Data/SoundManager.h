#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

class SoundManager
{
public:
	static void playClickEffect();
	static void playIncomingWave();
	static void playNextWaveReady();
	
	//��Ч
	static void playTowerMenu();
	static void playShipOpen();
	static void playWinStars();
	//������
	static void playTowerBuilding();
	static void playTowerUpdate();
	static void playTowerSell();
	//Ұ����
	static void playTotemReady();
	static void playTotemShot();
	static void playTotemSpirits();
	static void playTotemWeakness();
	//����
	static void playArrowShoot1();
	static void playArrowShoot2();
	static void playArrowRelease();
	static void playArcherReady();
	static void playArcher2Ready();
	static void playArcher3Ready();
	//����
	static void playCrossbowReady();
	static void playCrossbowMultishot();
	static void playCrossbowEagle();
	//������
	static void playEarthquakeReady();
	static void playEarthquakeHit();
	static void playEarthquakeDrillin();
	static void playEarthquakeDrillOut();
	static void playEarthquakeLava();
	//������
	static void playMechReady();
	static void playMechWalk();
	static void playMechShit();
	static void playMechLoading();
	//����
	static void playArtilleryReady();
	static void playArtillery2Ready();
	static void playArtillery3Ready();
	static void playBomb();
	//��Ӫ��
	static void playRallyPointPlaced();
	static void playBarrackReady();
	static void playBarrack2Ready();
	static void playBarrack3Ready();
	static void playBarrackOpendoor();
	static void playBarrackMove();
	static void playAssassinMove();
	//�������
	static void playArchmageReady();
	static void playArchmageShot();
	static void playArchmageTwister();
	static void playArchmagePrecharge();
	//����ħ����
	static void playMageTowerReady();
	static void playMageTower2Ready();
	static void playMageTower3Ready();
	static void playMageTowerShot();
	//NEC
	static void playNecTowerReady();
	static void playDKReady();
	static void playNecShot();
	static void playDKTaunt();
	//��ʯ
	static void playFireballHit();
	static void playFireballUnleash();
	//�ؿ�����
	static void playQuestCompleted();
	static void playQuestFailed();
	//����
	static void playReinforcement();
	static void playCash();
	static void playFreeze();
	static void playHearts();
	//����BOSS
	static void playChestdrum();
	static void playChimps_1();
	static void playChimps_2();
	static void playChimps_3();
	static void playMonoDeath();
public:
	static void playWelcomeBackMusic();
	static void playJungleBattle();
	static void playDesertBattle();
	static void playGameTheme1();
public:
	//BOSS 100
	static void playEfreetiLaugh();
	static void playEfreetiClap();
	static void playEfreetiDeath();
private:
	static bool cheakEffectState();
};

#endif