#include "SoundFX.h"

SoundFX::SoundFX()
{
	nextShipExplosion = 0;
	nextAsteroidExplosion = 0;
	ShipExplosions[0]=0;
	AsteroidExplosions[0]=0;
	Thruster = 0;
	Shoot = 0;
	EnemyShoot = 0;
	BossExplosion = 0;
	BossHit = 0;
	BossShoot = 0;
	Crunch = 0;
}

void SoundFX::LoadSounds()
{
	nextShipExplosion = 0;
	nextAsteroidExplosion = 0;

	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
	Shoot = pSoundEngine->LoadWav(L"Assets/laser.wav");
	EnemyShoot = pSoundEngine->LoadWav(L"Assets/shoot.wav");
	BossShoot = pSoundEngine->LoadWav(L"Assets/shot3.wav");
	Thruster = pSoundEngine->LoadWav(L"Assets/thrustloop2.wav");
	Crunch = pSoundEngine->LoadWav(L"Assets/crunch.wav");
	BossExplosion = pSoundEngine->LoadWav(L"Assets/explosion2.wav");
	BossHit = pSoundEngine->LoadWav(L"Assets/shot2.wav");
	
	for(int i=0;i<NUMEXPLOSIONS; i++)
		ShipExplosions[i] = pSoundEngine->LoadWav(L"Assets/explosion1.wav");
	
	for (int i = 0; i < NUMEXPLOSIONS; i++)
		AsteroidExplosions[i] = pSoundEngine->LoadWav(L"Assets/explosion4.wav");
}

void SoundFX::PlayShoot()
{
	MySoundEngine::GetInstance()->Play(Shoot);
}

void SoundFX::PlayEnemyShoot()
{
	MySoundEngine::GetInstance()->Play(EnemyShoot);
}

void SoundFX::PlayBossShoot()
{
	MySoundEngine::GetInstance()->Play(BossShoot);
}

void SoundFX::PlayBossHit()
{
	MySoundEngine::GetInstance()->Play(BossHit);
}

void SoundFX::PlayBossExplosion()
{
	MySoundEngine::GetInstance()->Play(BossExplosion);
}

void SoundFX::PlayCrunch()
{
	MySoundEngine::GetInstance()->Play(Crunch);
}

void SoundFX::PlayShipExplosion()
{
	MySoundEngine::GetInstance()->Play(ShipExplosions[nextShipExplosion]);
	nextShipExplosion++;
	if (nextShipExplosion >= NUMEXPLOSIONS)
		nextShipExplosion = 0;
}

void SoundFX::PlayAsteroidExplosion()
{
	MySoundEngine::GetInstance()->Play(AsteroidExplosions[nextAsteroidExplosion]);
	nextAsteroidExplosion++;
	if (nextAsteroidExplosion >= NUMEXPLOSIONS)
		nextAsteroidExplosion = 0;
}

void SoundFX::StartThruster()
{
	MySoundEngine::GetInstance()->Play(Thruster, true);
}

void SoundFX::StopThruster()
{
	MySoundEngine::GetInstance()->Stop(Thruster);
}

void SoundFX::SetEngineVolume(int volume)
{
	volume = (volume - 100) * 35;
	MySoundEngine::GetInstance()->SetVolume(Thruster, volume);
}
