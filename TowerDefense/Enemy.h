#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableGameComponent.h"
#include "HealthBar.h"
#include "Path.h"
#include <vector>
#include "Signalling\Signal.h"
#include "Anim.h"
#include "AnimPlayer.h"
#include "CharacterAnim.h"
#include "PlayerObject.h"

using namespace sf;
using namespace std;
using namespace Pathfinding;
using namespace States;
using namespace Animation;
namespace Game_Entities
{
    class Enemy : public DrawableGameComponent, public PlayerObject
    {
    public:
        Enemy(int x, int y,int uid, int owner_id);
		void Draw(sf::RenderTarget *rw);
		void Update(float elapsed_seconds);

        const Vector2f GetPos();

        //Give enemy new path to follow
        void UpdatePath(Path p_);
        void UpdatePath(vector<TileNode> node_path);

        const FloatRect GetBoundingBox();

        void ReduceHealth(float amount);
        const bool IsDead();
        const float GetHealth();
        const float GetMaxHealth();
		const int GetBounty();
		const int GetUID();
		const int GetOwnerId();
		void SetMaxHealth(float h);
		void SetPosition(Vector2f pos);
		void ChangeType(int lvl);
		void SetOwnerID(int id);
		Gallant::Signal1<Enemy*> on_path_completed;

		

    private:
        int health;
        int maxHealth;
		int bounty;
		int level;
		int UID;

		Vector2f velocity;
        double angle_to_point(double x, double y);
        void DrawHealth();
        HealthBar healthBar;

        //Pathing
        float stage_pos;
        int stage_index;
        Path path;
        float speed;

		void LoadContent(sf::String fileName);

        //Called in update
        void UpdatePathing(float seconds);
		void UpdateAnimation(sf::Vector2f direction);

		//Animations
		CharacterAnim *anim_left;
		CharacterAnim *anim_right;
		CharacterAnim *anim_up;
		CharacterAnim *anim_down;
		
		AnimPlayer sprite;

    };
}