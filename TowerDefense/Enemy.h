#pragma once
#include <SFML/Graphics.hpp>
#include "DrawableGameComponent.h"
#include "HealthBar.h"
#include "Path.h"
#include <vector>

using namespace sf;
using namespace std;
using namespace Pathfinding;
using namespace States;
namespace Game_Entities
{
    class Enemy : public DrawableGameComponent
    {
    public:
        Enemy(int, int);
        void Draw(sf::RenderWindow *rw);
        void Update(sf::RenderWindow *rw, float elapsed_seconds);

        const Vector2f GetPos();

        //Give enemy new path to follow
        void UpdatePath(Path p_);
        void UpdatePath(vector<TileNode> node_path);

        const FloatRect GetBoundingBox();

        void ReduceHealth(float amount);
        const bool IsDead();
        const float GetHealth();
        const float GetMaxHealth();
		void SetPosition(Vector2f pos);

    private:
        Texture tex;
        Sprite sprite;
        int id;
        int health;
        int maxHealth;
        Vector2f velocity;
        double angle_to_point(double x, double y);
        void DrawHealth();
        HealthBar healthBar;

        //Pathing
        float stage_pos;
        int stage_index;
        Path path;
        float speed;

        //Called in update
        void UpdatePathing(float seconds);

    };
}