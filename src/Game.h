
#ifndef WHACKAMOLESFML_GAME_H
#define WHACKAMOLESFML_GAME_H

#include <SFML/Graphics.hpp>

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

  sf::RenderWindow& window;
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Sprite walrus_1;
  sf::Sprite walrus_2;
  sf::Texture walrus_texture;
  sf::Font font;
  sf::Text title_text;
  bool walrus_1_captured = false;
  float walrus_1_respawn_timer = 0.5;
  bool walrus_2_captured = false;
  float walrus_2_respawn_timer = 0.5;

  bool in_menu;
  bool game_over = false;
  sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;
  sf::Text game_over_text;
  bool play_selected = true;

  //Walrus 1 speed and directions
  bool x1_reverse = false;
  bool y1_reverse = false;
  float x1_speed = 200;
  float y1_speed = 100;

  //Walrus 2 speed and directions
  bool x2_reverse = true;
  bool y2_reverse = true;
  float x2_speed = 250;
  float y2_speed = 200;

  sf::Text score_text;
  int score = 0;

  sf::Text clock_text;
  float game_timer = 60;

};

#endif // WHACKAMOLESFML_GAME_H
