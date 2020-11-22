
#ifndef WHACKAWALRUSSFML_GAME_H
#define WHACKAWALRUSSFML_GAME_H

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
  void mouseReleased(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  bool collisionCheck(sf::Vector2i click, sf::Sprite sprite);
  static bool walrusCollision(const sf::Sprite& w1, const sf::Sprite& w2);
  static bool spawnCheck(const sf::Sprite& obj, float x, float y);
  void spawn(const std::string& animal);

  // Sounds and Music
  sf::SoundBuffer buffer_whack;
  sf::SoundBuffer buffer_boing;
  sf::Sound whack;
  sf::Sound boing;
  sf::Music music;
  bool play_music = true;
  float volume = 25.0f;

  // Sprites and textures
  sf::RenderWindow& window;
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Sprite menu_bg;
  sf::Texture menu_bg_texture;
  sf::Texture walrus_texture;
  sf::Font font;
  sf::Text title_text;
  sf::Sprite waw_main;
  sf::Texture waw_texture;
  sf::Sprite cursor;
  sf::Texture cursor_texture;
  sf::Sprite play_button;
  sf::Texture play_texture_on;
  sf::Texture play_texture_off;
  sf::Sprite quit_button;
  sf::Texture quit_texture_on;
  sf::Texture quit_texture_off;

  // In Menu/Game Over
  bool in_menu;
  bool game_over = false;
  sf::Text menu_text;
  sf::Text game_over_text;
  sf::Text rules;
  bool play_selected = true;

  // Walrus 1
  sf::Sprite walrus_1;
  bool x1_reverse = false;
  bool y1_reverse = false;
  float x1_speed = 200;
  float y1_speed = 100;
  bool walrus_1_captured = false;
  float walrus_1_respawn_timer = 0.5;

  // Walrus 2
  sf::Sprite walrus_2;
  bool x2_reverse = true;
  bool y2_reverse = true;
  float x2_speed = 250;
  float y2_speed = 200;
  bool walrus_2_captured = false;
  float walrus_2_respawn_timer = 0.5;

  // Penguin
  sf::Sprite penguin;
  sf::Texture penguin_texture;
  bool xp_reverse = false;
  bool yp_reverse = false;
  float xp_speed = 200;
  float yp_speed = 100;
  bool penguin_captured = false;
  float penguin_timer = 0.5;

  // Game UI
  sf::Text score_text;
  int score = 0;
  sf::Text clock_text;
  float game_timer = 0;
};

#endif // WHACKAWALRUSSFML_GAME_H
