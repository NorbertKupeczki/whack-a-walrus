
#ifndef WHACKAMOLESFML_GAME_H
#define WHACKAMOLESFML_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  bool collisionCheck(sf::Vector2i click, sf::Sprite sprite);
  void spawn();

  sf::SoundBuffer buffer;
  sf::Sound whack;
  sf::Music music;
  bool play_music = true;
  float volume = 25.0f;

  sf::RenderWindow& window;
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Texture walrus_texture;
  sf::Font font;
  sf::Text title_text;

  bool in_menu;
  bool game_over = false;
  sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;
  sf::Text game_over_text;
  bool play_selected = true;

  //Walrus 1
  sf::Sprite walrus_1;
  bool x1_reverse = false;
  bool y1_reverse = false;
  float x1_speed = 200;
  float y1_speed = 100;
  bool walrus_1_captured = false;
  float walrus_1_respawn_timer = 0.5;

  //Walrus 2
  sf::Sprite walrus_2;
  bool x2_reverse = true;
  bool y2_reverse = true;
  float x2_speed = 250;
  float y2_speed = 200;
  bool walrus_2_captured = false;
  float walrus_2_respawn_timer = 0.5;

  //Penguin
  sf::Sprite penguin;
  sf::Texture penguin_texture;
  bool xp_reverse = false;
  bool yp_reverse = false;
  float xp_speed = 200;
  float yp_speed = 100;
  bool penguin_captured = false;
  float penguin_timer = 0.5;

  sf::Text score_text;
  int score = 0;

  sf::Text clock_text;
  float game_timer = 0;

  sf::Text rules;
};

#endif // WHACKAMOLESFML_GAME_H
