#pragma once
#include "mysoundengine.h"

class SoundFX
{
private:
	static const int NUMEXPLOSIONS = 5;
	int nextShipExplosion;
	int nextAsteroidExplosion;
	SoundIndex ShipExplosions[NUMEXPLOSIONS];
	SoundIndex AsteroidExplosions[NUMEXPLOSIONS];
	SoundIndex Thruster;
	SoundIndex Shoot;
	SoundIndex EnemyShoot;
	SoundIndex BossShoot;
	SoundIndex Crunch;
	SoundIndex BossExplosion;
	SoundIndex BossHit;

public:
	SoundFX();
	void LoadSounds();
	void PlayShoot();
	void PlayEnemyShoot();
	void PlayBossShoot();
	void PlayCrunch();
	void PlayBossExplosion();
	void PlayBossHit();
	void PlayShipExplosion();
	void PlayAsteroidExplosion();
	void StartThruster();
	void StopThruster();
	void SetEngineVolume(int volume);
};

