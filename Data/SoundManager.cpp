#include "Data/SoundManager.h"
#include "cocos2d.h"

#define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
//using namespace cocos2d::experimental;
#endif

USING_NS_CC;

bool SoundManager::cheakEffectState()
{
	if(UserDefault::getInstance()->getIntegerForKey("backeffect",1)==1)
		return true;
	else
		return false;
}

void SoundManager::playEfreetiLaugh()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/boss_efreeti_evillaugh.wav");
}

void SoundManager::playWinStars()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_WinStars.wav");
}

void SoundManager::playEfreetiDeath()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/boss_efreeti_death.wav");
}

void SoundManager::playEfreetiClap()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/boss_efreeti_clapping.wav");
}

void SoundManager::playClickEffect()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_GUIButtonCommon.wav");
}

void SoundManager::playWelcomeBackMusic()
{
	int backmusic = AudioEngine::play2d("sound/savage_music_theme.wav");
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==0)
		AudioEngine::pause(backmusic);
}

void SoundManager::playDesertBattle()
{
	int backmusic = AudioEngine::play2d("sound/savage_music_desert_battle.wav");
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==0)
		AudioEngine::pause(backmusic);
}

void SoundManager::playJungleBattle()
{
	int backmusic = AudioEngine::play2d("sound/savage_music_jungle_battle.wav");
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==0)
		AudioEngine::pause(backmusic);
}

void SoundManager::playGameTheme1()
{
	int thema1 = AudioEngine::play2d("sound/Map_Theme_1.wav");
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==0)
		AudioEngine::pause(thema1);
}

void SoundManager::playNextWaveReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_NextWaveReady.wav");
}


void SoundManager::playIncomingWave()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_WaveIncoming.wav");
}

void SoundManager::playArrowShoot1()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_ArrowHit2.wav");
}

void SoundManager::playArrowShoot2()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_ArrowHit3.wav");
}

void SoundManager::playTowerUpdate()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_TowerUpgrade.wav");
}

void SoundManager::playTowerSell()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_TowerSell.wav");
}

void SoundManager::playShipOpen()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/ship_path_break.wav");
}

void SoundManager::playTowerBuilding()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_TowerBuilding.wav");
}

void SoundManager::playArcherReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Archer_Ready.wav");
}

void SoundManager::playTowerMenu()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_GUIOpenTowerMenu.wav");
}

void SoundManager::playArcher2Ready()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Archer_Taunt1.wav");
}

void SoundManager::playArcher3Ready()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Archer_Taunt2.wav");
}

void SoundManager::playCrossbowReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/crossbow_taunt_ready.wav");
}

void SoundManager::playCrossbowMultishot()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/crossbow_multishot.wav");
}

void SoundManager::playCrossbowEagle()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/crossbow_eagle.wav");
}

void SoundManager::playTotemReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/axlethrower_taunt_totem1.wav");
}

void SoundManager::playTotemShot()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/axlethrower_totem_vanish.wav");
}

void SoundManager::playTotemSpirits()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/axlethrower_totem_spirits.wav");
}

void SoundManager::playTotemWeakness()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/axlethrower_totem_weakness.wav");
}

void SoundManager::playEarthquakeReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/earthquake_taunt_ready.wav");
}

void SoundManager::playEarthquakeHit()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/dwaarp_attack.wav");
}

void SoundManager::playEarthquakeDrillin()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/dwaarp_drillIn.wav");
}

void SoundManager::playEarthquakeDrillOut()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/dwaarp_drillOut.wav");
}

void SoundManager::playEarthquakeLava()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/dwaarp_lavaSmash.wav");
}

void SoundManager::playMechReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/mecha_taunt_ready.wav");
}


void SoundManager::playMechWalk()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/mecha_walk.wav");
}


void SoundManager::playMechShit()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/mecha_dropoil.wav");
}

void SoundManager::playMechLoading()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/mecha_spawn.wav");
}

void SoundManager::playArtilleryReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Artillery_Ready.wav");
}


void SoundManager::playArtillery2Ready()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Artillery_Taunt1.wav");
}


void SoundManager::playArtillery3Ready()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Artillery_Taunt2.wav");
}

void SoundManager::playBarrackReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Barrack_Ready.wav");
}

void SoundManager::playBarrack2Ready()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Barrack_Taunt1.wav");
}

void SoundManager::playBarrack3Ready()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Barrack_Taunt2.wav");
}

void SoundManager::playBarrackOpendoor()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_TowerOpenDoor.wav");
}

void SoundManager::playBarrackMove()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Barrack_Move.wav");
}

void SoundManager::playArchmageReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/archmage_taunt_ready.wav");
}

void SoundManager::playArchmageShot()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/archmage_attack.wav");
}

void SoundManager::playArchmageTwister()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/archmage_twister.wav");
}

void SoundManager::playArchmagePrecharge()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/archmage_precharge.wav");
}

void SoundManager::playMageTowerReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Mage_Ready.wav");
}

void SoundManager::playMageTower2Ready()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Mage_Taunt1.wav");
}

void SoundManager::playMageTower3Ready()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Mage_Taunt2.wav");
}

void SoundManager::playMageTowerShot()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_MageShot.wav");
}

void SoundManager::playNecTowerReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/necromancer_taunt_ready.wav");
}

void SoundManager::playDKReady()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/necromancer_taunt_dknight.wav");
}

void SoundManager::playNecShot()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/necromancer_attack.wav");
}

void SoundManager::playDKTaunt()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/necromancer_deathknight_taunt_2.wav");
}

void SoundManager::playArrowRelease()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_ArrowRelease2.wav");
}

void SoundManager::playBomb()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_Bomb1.wav");
}

void SoundManager::playFireballHit()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_FireballHit.wav");
}

void SoundManager::playFireballUnleash()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_FireballUnleash.wav");
}

void SoundManager::playQuestCompleted()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_QuestCompleted.wav");
}

void SoundManager::playQuestFailed()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_QuestFailed.wav");
}

void SoundManager::playAssassinMove()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/assassin_taunt_ready.wav");
}

void SoundManager::playReinforcement()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Reinforcements_Event2.wav");
}

void SoundManager::playCash()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/inapp_cash.wav");
}

void SoundManager::playFreeze()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/inapp_freeze.wav");
}

void SoundManager::playHearts()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/inapp_hearts.wav");
}

void SoundManager::playRallyPointPlaced()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/Sound_RallyPointPlaced.wav");
}

void SoundManager::playChestdrum()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/boss_mono_chestdrum.wav");
}

void SoundManager::playChimps_1()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/boss_mono_chimps_1.wav");
}

void SoundManager::playChimps_2()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/boss_mono_chimps_2.wav");
}

void SoundManager::playChimps_3()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/boss_mono_chimps_3.wav");
}

void SoundManager::playMonoDeath()
{
	if(cheakEffectState())
		AudioEngine::play2d("sound/boss_mono_death.wav");
}
