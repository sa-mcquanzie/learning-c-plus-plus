#pragma once
#include "colour.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <string>
#include <vector>


enum struct EntityType {
  Base,
  Player,
  Alien,
  Bullet,
  Star,
  StatusBar
};

enum AlienVariant {
  Crab,
  Squid,
  Octopus,
  Cuttlefish,
  Mystery
};

enum AlienPhase {
  Strafing,
  Advancing
};

extern const char * EntityTypes[5];
extern const char * AlienTypes[3];

class Entity {
  public:
    static constexpr std::string types[6] = {
      "Base",
      "Player",
      "Alien",
      "Bullet",
      "Star",
      "StatusBar"
    };

    EntityType entity_type;
    SDL_Renderer *renderer;
    std::vector<int> sprite;
    bool visible;
    bool destroyed;
    float x;
    float y;
    float w;
    float h;

    Entity(
      SDL_Renderer * renderer,
      float x, float y,
      float w, float h,
      std::vector<int> sprite
    );

    Entity(
      SDL_Renderer * renderer,
      float x, float y,
      std::vector<int> sprite
    );

    Entity(
      SDL_Renderer * renderer,
      float x, float y
    );

    Entity(
      SDL_Renderer * renderer
    );

    Entity(
      SDL_Renderer * renderer,
      std::vector<int> sprite
    );

    virtual ~Entity();

    virtual void show() = 0;
    virtual void move() = 0;
    virtual std::string own_type();

    void animate();
};

class Player : public Entity {
  public:
    using Entity::Entity;
    float direction;
    float speed;
    SDL_FRect hitbox;
    Rgba colour;

    Player(
      SDL_Renderer * renderer,
      float x, float y,
      float w, float h
    );

    Player(
      SDL_Renderer * renderer,
      float x, float y
    );

    Player(
      SDL_Renderer * renderer,
      std::vector<int> sprite
    );

    Player(
      SDL_Renderer * renderer
    );

    ~Player();

    void show() override;
    void move() override;
    void update_hitbox();
};

class Bullet : public Entity {
  public:
    using Entity::Entity;
    SDL_FRect hitbox;
    Rgba colour;
    float direction;

    Bullet(
      SDL_Renderer * renderer,
      float x, float y,
      float direction
    );

    Bullet(
      SDL_Renderer * renderer
    );

    ~Bullet();

    void show() override;
    void move() override;
    void update_hitbox();
};

class Star: public Entity {
  public:
    using Entity::Entity;
    float direction;
    float speed;
    Rgba colour;
    std::vector<int> sprite;
    int alpha;

    Star(
      SDL_Renderer * renderer
    );

    ~Star();

    void show() override;
    void move() override;
};

class Alien: public Entity {
  public:
    using Entity::Entity;
    AlienVariant variant;
    float direction;
    float speed;
    SDL_FRect hitbox;
    Rgba colour;
    std::array<std::vector<int>, 2> sprite;
    int sprite_current_frame;
    int sprite_total_frames;
    Uint64 last_animated;
    Uint64 animation_rate;
    float x_min;
    float x_max;
    float y_max;
    bool can_fire;
    bool should_fire;
    AlienPhase phase;


    static constexpr std::string types[5] = {
      "Crab",
      "Squid",
      "Octopus",
      "Cuttlefish",
      "Mystery"
    };


    Alien(
      EntityType entity_type,
      SDL_Renderer * renderer,
      float x, float y,
      bool visible
    );

    Alien(
      SDL_Renderer * renderer,
      AlienVariant variant,
      float x, float y
    );

    Alien(
      SDL_Renderer * renderer,
      float x, float y,
      std::vector<int> sprite
    );

    ~Alien();

    void show() override;
    void move() override;
    void update_hitbox();
};

class StatusBar: public Entity {
  public:
    using Entity::Entity;
    int score;
    int ships;
    SDL_FRect* rect;

  StatusBar(SDL_Renderer * renderer);

  ~StatusBar();

  void show() override;
  void move() override;
  void update_score();
  void update_ships();
};