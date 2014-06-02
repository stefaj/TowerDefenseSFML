#pragma once
#include "TowerStruct.h"
#include "ProjectileStruct.h"
#include "EnemyStruct.h"
#include "SFML/Network.hpp"
#include "PlayerSyncStruct.h"
#include "RemoveEnemyStruct.h"
#include "UpdateEnemyStruct.h"
#include "Signalling\Signal.h"
#include <iostream>
#include <stdio.h>


namespace Networking
{
	enum PACKETTYPES{ NewTower = 0, NewProjectile = 1, NewEnemy = 2, PlayerSync = 3, RemoveEnemy = 4, UpdateEnemy=5 };
	class Connection
	{
	public:
		Connection();
		Connection(sf::TcpSocket *s);
		void Send(TowerStruct h);
		void Send(ProjectileStruct p);
		void Send(EnemyStruct p);
		void Send(PlayerSyncStruct s);
		void Send(RemoveEnemyStruct es);
		void Send(UpdateEnemyStruct en);
		void Update(float elapsed_time);

		//Signals
		Gallant::Signal1<TowerStruct> OnNewTowerReceived;
		Gallant::Signal1<EnemyStruct> OnNewEnemyReceived;
		Gallant::Signal1<UpdateEnemyStruct> OnUpdateEnemyReceived;
		Gallant::Signal1<ProjectileStruct> OnNewProjectileRecieved;
		Gallant::Signal1<PlayerSyncStruct> OnNewPSyncRecieved;
		Gallant::Signal1<RemoveEnemyStruct> OnRemoveEnemyReceived;
	private:
		sf::TcpSocket *sock;
	};
}