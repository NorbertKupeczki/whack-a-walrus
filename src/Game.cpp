
#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window): window(game_window)
{
  srand(time(nullptr));
}

Game::~Game()
{
  std::cout << "Game terminates";
}

bool Game::init()
{
  /* =============== init game and menu background texture =============== */
  if(!background_texture.loadFromFile("Data/Images/game_bg.png"))
  {
    std::cout << "background texture didn't load\n";
  }
  background.setTexture(background_texture);

  if(!menu_bg_texture.loadFromFile("Data/Images/menu_bg.png"))
  {
    std::cout << "background texture didn't load\n";
  }
  menu_bg.setTexture(menu_bg_texture);

  /* =============== init interactive element textures =============== */
  if(!waw_texture.loadFromFile("Data/Images/Whack_a_Walrus.png"))
  {
    std::cout << "background texture didn't load\n";
  }
  waw_main.setTexture(waw_texture);
  waw_main.setPosition(
    window.getSize().x / 2 - waw_main.getGlobalBounds().width / 2,
    window.getSize().y / 6 - waw_main.getGlobalBounds().height / 2);

  //init character texture
  if(!walrus_texture.loadFromFile("Data/Images/walrus.png"))
  {
    std::cout << "walrus texture didn't load\n";
  }
  walrus_1.setTexture(walrus_texture);
  walrus_1.setPosition(window.getSize().x / 2 - walrus_1.getGlobalBounds().width / 2,100);
  walrus_2.setTexture(walrus_texture);
  walrus_2.setPosition(window.getSize().x / 2 - walrus_2.getGlobalBounds().width / 2,500);

  if(!penguin_texture.loadFromFile("Data/Images/penguin.png"))
  {
    std::cout << "penguin texture didn't load\n";
  }
  penguin.setTexture(penguin_texture);
  penguin.setPosition(window.getSize().x / 2 - penguin.getGlobalBounds().width / 2,500);

  if(!play_texture_on.loadFromFile("Data/Images/start_yellow.png"))
  {
    std::cout << "play-on texture didn't load\n";
  }
  if(!play_texture_off.loadFromFile("Data/Images/start_blue.png"))
  {
    std::cout << "play-off texture didn't load\n";
  }
  play_button.setTexture(play_texture_on);
  play_button.setPosition(
    window.getSize().x / 3 - play_button.getGlobalBounds().width / 2,
    260);

  if(!quit_texture_on.loadFromFile("Data/Images/quit_yellow.png"))
  {
    std::cout << "quit-on texture didn't load\n";
  }
  if(!quit_texture_off.loadFromFile("Data/Images/quit_blue.png"))
  {
    std::cout << "quit-off texture didn't load\n";
  }
  quit_button.setTexture(quit_texture_off);
  quit_button.setPosition(
    window.getSize().x / 1.5 - quit_button.getGlobalBounds().width / 2,
    260);

  //init music
  if (!music.openFromFile("Data/Sound/bg_music.ogg"))
  {
    std::cout << "Music file didn't load";
  }
  music.setVolume(volume);
  music.setLoop(true);
  music.play();

  //init sound
  if (!buffer_whack.loadFromFile("Data/Sound/whack.ogg"))
  {
    std::cout << "whack sound didn't load to buffer!\n";
  }
  whack.setBuffer(buffer_whack);
  whack.play();

  if (!buffer_boing.loadFromFile("Data/Sound/boing.ogg"))
  {
    std::cout << "boing sound didn't load to buffer!\n";
  }
  boing.setBuffer(buffer_boing);

  //init cursor
  if(!cursor_texture.loadFromFile("Data/Images/cursor2.png"))
  {
    std::cout << "cursor texture didn't load\n";
  }
  cursor.setTexture(cursor_texture);
  cursor.setOrigin(40.0f,40.0f);
  window.setMouseCursorVisible(false);

  //init text
  if (!font.loadFromFile("Data/Fonts/Forte.ttf"))
  {
    std::cout << "font did not load \n";
  }

  title_text.setString("Whack-a-walrus");
  title_text.setFont(font);
  title_text.setCharacterSize(35);
  title_text.setFillColor(sf::Color(255,255,255,200));
  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
    10);

  rules.setString("You have to catch as many walruses as you"
                  "\ncan within 60 seconds, but try not to capture"
                  "\nthe penguin. For each walrus captured, you score"
                  "\n1 point, but for each penguin you lose 5."
                  "\n\nKeys:"
                  "\n  [Q] = Quit game"
                  "\n  [M] = Music On/Off"
                  "\n  [+] = Increase volume"
                  "\n  [-] = Reduce volume");
  rules.setFont(font);
  rules.setCharacterSize(25);
  rules.setFillColor(sf::Color(0,0,255,225));
  rules.setPosition(
    window.getSize().x / 2 - rules.getGlobalBounds().width / 2,
    350);

  menu_text.setString("Please select an option using the LEFT\n"
                      "or RIGHT arrow keys, then press ENTER:");
  menu_text.setFont(font);
  menu_text.setCharacterSize(28);
  menu_text.setFillColor(sf::Color(0,0,255,225));
  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    window.getSize().y / 4 - menu_text.getGlobalBounds().height / 2 +10);

  score_text.setString("Score: 0");
  score_text.setFont(font);
  score_text.setCharacterSize(24);
  score_text.setFillColor(sf::Color(255,0,0,255));
  score_text.setPosition(940,10);

  clock_text.setString("Clock");
  clock_text.setFont(font);
  clock_text.setCharacterSize(24);
  clock_text.setFillColor(sf::Color(255,128,0,255));
  clock_text.setPosition(10,10);

  game_over_text.setString("GAME OVER");
  game_over_text.setFont(font);
  game_over_text.setCharacterSize(100);
  game_over_text.setFillColor(sf::Color(255,0,0,200));
  game_over_text.setPosition(
    window.getSize().x / 2 - game_over_text.getGlobalBounds().width / 2,
    window.getSize().y / 3 - game_over_text.getGlobalBounds().height / 2);

  in_menu = true;

  return true;
}

void Game::update(float dt)
{
  cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
  music.setVolume(volume);

  //Walrus 1 movement and directions, only runs if it is not captured
  if (!walrus_1_captured)
  {
    if (x1_reverse && y1_reverse)
    {
      walrus_1.move(-1.0f * x1_speed * dt, -1.0f * y1_speed * dt);
      walrus_1.setTextureRect(sf::IntRect(
        walrus_1.getLocalBounds().width,
        0,
        -walrus_1.getLocalBounds().width,
        walrus_1.getLocalBounds().height));
    }
    else if (x1_reverse && !y1_reverse)
    {
      walrus_1.move(-1.0f * x1_speed * dt, 1.0f * y1_speed * dt);
      walrus_1.setTextureRect(sf::IntRect(
        walrus_1.getLocalBounds().width,
        0,
        -walrus_1.getLocalBounds().width,
        walrus_1.getLocalBounds().height));
    }
    else if (!x1_reverse && y1_reverse)
    {
      walrus_1.move(1.0f * x1_speed * dt, -1.0f * y1_speed * dt);
      walrus_1.setTextureRect(sf::IntRect(
        0,
        0,
        walrus_1.getLocalBounds().width,
        walrus_1.getLocalBounds().height));
    }
    else
    {
      walrus_1.move(1.0f * x1_speed * dt, 1.0f * y1_speed * dt);
      walrus_1.setTextureRect(sf::IntRect(
        0,
        0,
        walrus_1.getLocalBounds().width,
        walrus_1.getLocalBounds().height));
    }

    if (
      (walrus_1.getPosition().x >
       (window.getSize().x - walrus_1.getGlobalBounds().width)) ||
      (walrus_1.getPosition().x < 0))
    {
      if (walrus_1.getPosition().x < 0)
      {
        walrus_1.move(2, 0);
      }
      else
      {
        walrus_1.move(-2, 0);
      }
      boing.play();
      x1_reverse = !x1_reverse;
      x1_speed   = 200.0f + ((rand() % 21) * 5.0f);
      y1_speed   = 50.0f + ((rand() % 41) * 5.0f);
    }

    if (
      (walrus_1.getPosition().y >
       (window.getSize().y - walrus_1.getGlobalBounds().height)) ||
      (walrus_1.getPosition().y < 0))
    {
      if (walrus_1.getPosition().y < 0)
      {
        walrus_1.move(0, 2);
      }
      else
      {
        walrus_1.move(0, -2);
      }
      boing.play();
      y1_reverse = !y1_reverse;
      x1_speed   = 200.0f + ((rand() % 21) * 5.0f);
      y1_speed   = 50.0f + ((rand() % 41) * 5.0f);
    }
  }

  //Walrus 2 movement and directions, only runs if it is not captured
  if (!walrus_2_captured)
  {
    if (x2_reverse && y2_reverse)
    {
      walrus_2.move(-1.0f * x2_speed * dt, -1.0f * y2_speed * dt);
      walrus_2.setTextureRect(sf::IntRect(
        walrus_2.getLocalBounds().width,
        0,
        -walrus_2.getLocalBounds().width,
        walrus_2.getLocalBounds().height));
    }
    else if (x2_reverse && !y2_reverse)
    {
      walrus_2.move(-1.0f * x2_speed * dt, 1.0f * y2_speed * dt);
      walrus_2.setTextureRect(sf::IntRect(
        walrus_2.getLocalBounds().width,
        0,
        -walrus_2.getLocalBounds().width,
        walrus_2.getLocalBounds().height));
    }
    else if (!x2_reverse && y2_reverse)
    {
      walrus_2.move(1.0f * x2_speed * dt, -1.0f * y2_speed * dt);
      walrus_2.setTextureRect(sf::IntRect(
        0,
        0,
        walrus_2.getLocalBounds().width,
        walrus_2.getLocalBounds().height));
    }
    else
    {
      walrus_2.move(1.0f * x2_speed * dt, 1.0f * y2_speed * dt);
      walrus_2.setTextureRect(sf::IntRect(
        0,
        0,
        walrus_2.getLocalBounds().width,
        walrus_2.getLocalBounds().height));
    }

    if (
      (walrus_2.getPosition().x >
       (window.getSize().x - walrus_2.getGlobalBounds().width)) ||
      (walrus_2.getPosition().x < 0))
    {
      if (walrus_2.getPosition().x < 0)
      {
        walrus_2.move(2, 0);
      }
      else
      {
        walrus_2.move(-2, 0);
      }
      boing.play();
      x2_reverse = !x2_reverse;
      x2_speed   = 200.0f + ((rand() % 21) * 5.0f);
      y2_speed   = 50.0f + ((rand() % 41) * 5.0f);
    }

    if (
      (walrus_2.getPosition().y >
       (window.getSize().y - walrus_2.getGlobalBounds().height)) ||
      (walrus_2.getPosition().y < 0))
    {
      if (walrus_2.getPosition().y < 0)
      {
        walrus_2.move(0, 2);
      }
      else
      {
        walrus_2.move(0, -2);
      }
      boing.play();
      y2_reverse = !y2_reverse;
      x2_speed   = 200.0f + ((rand() % 21) * 5.0f);
      y2_speed   = 50.0f + ((rand() % 41) * 5.0f);
    }
  }

  //Penguin movement and directions, only runs if it is not captured
  if (!penguin_captured)
  {
    if (xp_reverse && yp_reverse)
    {
      penguin.move(-1.0f * xp_speed * dt, -1.0f * yp_speed * dt);
      penguin.setTextureRect(sf::IntRect(
        penguin.getLocalBounds().width,
        0,
        -penguin.getLocalBounds().width,
        penguin.getLocalBounds().height));
    }
    else if (xp_reverse && !yp_reverse)
    {
      penguin.move(-1.0f * xp_speed * dt, 1.0f * yp_speed * dt);
      penguin.setTextureRect(sf::IntRect(
        penguin.getLocalBounds().width,
        0,
        -penguin.getLocalBounds().width,
        penguin.getLocalBounds().height));
    }
    else if (!xp_reverse && yp_reverse)
    {
      penguin.move(1.0f * xp_speed * dt, -1.0f * yp_speed * dt);
      penguin.setTextureRect(sf::IntRect(
        0, 0, penguin.getLocalBounds().width, penguin.getLocalBounds().height));
    }
    else
    {
      penguin.move(1.0f * xp_speed * dt, 1.0f * yp_speed * dt);
      penguin.setTextureRect(sf::IntRect(
        0, 0, penguin.getLocalBounds().width, penguin.getLocalBounds().height));
    }

    if (
      (penguin.getPosition().x >
       (window.getSize().x - penguin.getGlobalBounds().width)) ||
      (penguin.getPosition().x < 0) && !penguin_captured)
    {
      if (penguin.getPosition().x < 0)
      {
        penguin.move(2, 0);
      }
      else
      {
        penguin.move(-2, 0);
      }
      boing.play();
      xp_reverse = !xp_reverse;
      xp_speed   = 200.0f + ((rand() % 21) * 5.0f);
      yp_speed   = 50.0f + ((rand() % 41) * 5.0f);
    }

    if (
      (penguin.getPosition().y >
       (window.getSize().y - penguin.getGlobalBounds().height)) ||
      (penguin.getPosition().y < 0) && !penguin_captured)
    {
      if (penguin.getPosition().y < 0)
      {
        penguin.move(0, 2);
      }
      else
      {
        penguin.move(0, -2);
      }
      boing.play();
      yp_reverse = !yp_reverse;
      xp_speed   = 200.0f + ((rand() % 21) * 5.0f);
      yp_speed   = 50.0f + ((rand() % 41) * 5.0f);
    }
  }

  // If walruses collide, bounce them off each other by exchanging
  // speed and direction values
  if (walrusCollision(walrus_1,walrus_2))
  {
    std::cout << "CLASH OF WALRUSES\n";
    boing.play();

    bool direction_buffer;
    direction_buffer = x1_reverse;
    x1_reverse = x2_reverse;
    x2_reverse = direction_buffer;
    direction_buffer = y1_reverse;
    y1_reverse = y2_reverse;
    y2_reverse = direction_buffer;

    float speed_buffer;
    speed_buffer = x1_speed;
    x1_speed = x2_speed;
    x2_speed = speed_buffer;
    speed_buffer = y1_speed;
    y1_speed = y2_speed;
    y2_speed = speed_buffer;
  }

  //If any character's state is captured, spawn it after the respawn time
  if (walrus_1_captured)
  {
    if (walrus_1_respawn_timer > 0)
    {
      walrus_1_respawn_timer -= dt;
    }
    else
    {
      spawn("walrus1");
    }
  }
  else if (walrus_2_captured)
  {
    if (walrus_2_respawn_timer > 0)
    {
      walrus_2_respawn_timer -= dt;
    }
    else
    {
      spawn("walrus2");
    }
  }
  else if (penguin_captured)
  {
    if (penguin_timer > 0)
    {
      penguin_timer -= dt;
    }
    else
    {
      spawn("penguin");
    }
  }

  // Countdown
  if (!in_menu && game_timer >= 0)
  {
    game_timer -= dt;
    int time_in_seconds = game_timer;
    clock_text.setString("Time remaining: " + std::to_string(time_in_seconds));
  }
  else if (!in_menu && game_timer < 0)
  {
    clock_text.setString("GAME OVER");
    game_over = true;
    game_timer -= dt;
    score_text.setPosition(
      window.getSize().x / 2 - score_text.getGlobalBounds().width / 2,
      window.getSize().y / 2 - score_text.getGlobalBounds().height / 2);
    score_text.setCharacterSize(50);

    xp_speed = yp_speed = x1_speed = x2_speed = y1_speed = y2_speed = 0;
    walrus_1.setPosition(300 - walrus_1.getLocalBounds().width / 2, 330);
    x1_reverse = false;
    walrus_2.setPosition(780 - walrus_2.getLocalBounds().width / 2, 330);
    x2_reverse = true;
    penguin.setPosition(window.getSize().x/2 - penguin.getLocalBounds().width / 2,
                        450);
    if (volume > 0)
    {
      volume -= 5.0f * dt;
      if(volume < 0)
      {
        volume = 0.0f;
      }
      music.setVolume(volume);
    }

    if (game_timer < -5)
    {
      window.close();
    }
  }
}

void Game::render()
{
  if (in_menu)
  {
    window.draw(menu_bg);
    window.draw(waw_main);
    window.draw(menu_text);
    window.draw(play_button);
    window.draw(quit_button);
    window.draw(rules);
  }
  else if (game_over)
  {
    window.draw(background);
    window.draw(game_over_text);
    window.draw(score_text);
    window.draw(walrus_1);
    window.draw(walrus_2);
    window.draw(penguin);
  }
  else
  {
    window.draw(background);
    window.draw(walrus_1);
    window.draw(walrus_2);
    window.draw(penguin);
    window.draw(title_text);
    window.draw(score_text);
    window.draw(clock_text);
    window.draw(cursor);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  cursor.setRotation(-10.0f);

  if (collisionCheck(click, penguin))
  {
    std::cout << "Collision detected: Penguin 2\n";
    std::string new_score;
    score -= 5;
    new_score = "Score: " + std::to_string(score);
    score_text.setString(new_score);
    //Removing penguin from the scene
    penguin.setPosition(-penguin.getLocalBounds().width-10,0);
    xp_speed = yp_speed = 0;
    penguin_timer = 0.5;
    penguin_captured = true;
  }
  else if (collisionCheck(click, walrus_1))
  {
    std::cout << "Collision detected: Walrus 1\n";
    std::string new_score;
    score++;
    new_score = "Score: " + std::to_string(score);
    score_text.setString(new_score);
    //Removing the walrus from the scene
    walrus_1.setPosition(-walrus_1.getLocalBounds().width-500,0);
    x1_speed = y1_speed = 0;
    walrus_1_respawn_timer = 0.5;
    walrus_1_captured = true;
  }
  else if (collisionCheck(click, walrus_2))
  {
    std::cout << "Collision detected: Walrus 2\n";
    std::string new_score;
    score++;
    new_score = "Score: " + std::to_string(score);
    score_text.setString(new_score);
    //Removing walrus 2 from the scene
    walrus_2.setPosition(-walrus_2.getLocalBounds().width-500,500);
    x2_speed = y2_speed = 0;
    walrus_2_respawn_timer = 0.5;
    walrus_2_captured = true;
  }
}

void Game::mouseReleased(sf::Event event)
{
  cursor.setRotation(10.0f);
}

void Game::keyPressed(sf::Event event)
{
  if (in_menu)
  {
    if (
      (event.key.code == sf::Keyboard::Left) ||
      (event.key.code == sf::Keyboard::Right))
    {
      play_selected = !play_selected;
      if (play_selected)
      {
        play_button.setTexture(play_texture_on);
        quit_button.setTexture(quit_texture_off);
      }
      else
      {
        play_button.setTexture(play_texture_off);
        quit_button.setTexture(quit_texture_on);
      }
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
      if (play_selected)
      {
        in_menu = false;
        game_over = false;
        game_timer = 60;
      }
      else
      {
        window.close();
      }
    }

  }
  if (event.key.code == sf::Keyboard::Q)
  {
    game_timer = -0.01;
  }
  if (event.key.code == sf::Keyboard::M)
  {
    if (play_music)
    {
      music.pause();
    }
    else
    {
      music.play();
    }
    play_music = !play_music;
  }
  if (event.key.code == sf::Keyboard::Add)
  {
    if (volume < 50.0)
    {
      volume += 5.0;
    }
  }
  if (event.key.code == sf::Keyboard::Subtract)
  {
    if (volume > 0)
    {
      volume -= 5.0;
    }
  }
}

bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
  float x_dist = click.x-40.0f -
               (sprite.getPosition().x + sprite.getLocalBounds().width/2);
  float y_dist = click.y-40.0f -
               (sprite.getPosition().y + sprite.getLocalBounds().height/2);

  float dist = sqrt(pow(x_dist,2) + pow(y_dist,2));

  if (dist < 65.0f)
  {
    whack.play();
    return true;
  }
  else
  {
    return false;
  }
}

bool Game::walrusCollision(const sf::Sprite& w1, const sf::Sprite& w2)
{
  float x_dist = (w1.getPosition().x + w1.getLocalBounds().width/2) -
               (w2.getPosition().x + w2.getLocalBounds().width/2);
  float y_dist = (w1.getPosition().y + w1.getLocalBounds().height/2) -
               (w2.getPosition().y + w2.getLocalBounds().height/2);

  float dist = sqrt(pow(x_dist,2) + pow(y_dist,2));

  if (dist < 128.0f)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Game::spawnCheck(const sf::Sprite& obj, float x, float y)
{
  float x_dist = (obj.getPosition().x + obj.getLocalBounds().width/2) - (x+64.0f);
  float y_dist = (obj.getPosition().y + obj.getLocalBounds().height/2) - (y+69.0f);

  float dist = sqrt(pow(x_dist,2) + pow(y_dist,2));

  if (dist < 180.0f)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Game::spawn(const std::string& animal)
{
  bool illegal_spawn;
  float new_x_pos;
  float new_y_pos;
  //Gives the walrus a random speed and spawn location
  if (animal == "walrus1" && !game_over)
  {
    do
    {
      new_x_pos = ((rand() % 941) + 10.0f);
      new_y_pos = ((rand() % 571) + 10.0f);
      illegal_spawn = spawnCheck(walrus_2,new_x_pos,new_y_pos);
    } while (illegal_spawn);

    walrus_1.setPosition(new_x_pos,new_y_pos);

    x1_speed = 200.0f + ((rand() % 21) * 5.0f);
    y1_speed = 50.0f + ((rand() % 41) * 5.0f);

    //Gives the walrus a random direction
    int direction = rand() % 4;
    switch (direction)
    {
      case 0:
      {
        x1_reverse = false;
        y1_reverse = false;
        break;
      }
      case 1:
      {
        x1_reverse = false;
        y1_reverse = true;
        break;
      }
      case 2:
      {
        x1_reverse = true;
        y1_reverse = false;
        break;
      }
      case 3:
      {
        x1_reverse = true;
        y1_reverse = true;
        break;
      }
    }
    walrus_1_captured = false;
    std::cout << "New walrus_1 is spawned! x_speed: "<< x1_speed <<
                 ", y_speed: "<< y1_speed <<
                 ", x_pos: "<< new_x_pos <<
                 ", y_pos: "<< new_y_pos <<"\n";
  }
  else if (animal == "walrus2" && !game_over)
  {
    do
    {
      new_x_pos = ((rand() % 941) + 10.0f);
      new_y_pos = ((rand() % 571) + 10.0f);
      illegal_spawn = spawnCheck(walrus_1,new_x_pos,new_y_pos);
    } while (illegal_spawn);

    walrus_2.setPosition(new_x_pos,new_y_pos);

    x2_speed = 200.f + ((rand() % 21) * 5.0f);
    y2_speed = 50.0f + ((rand() % 41) * 5.0f);

    //Gives the walrus a random direction
    int direction = rand() % 4;
    switch (direction)
    {
      case 0:
      {
        x2_reverse = false;
        y2_reverse = false;
        break;
      }
      case 1:
      {
        x2_reverse = false;
        y2_reverse = true;
        break;
      }
      case 2:
      {
        x2_reverse = true;
        y2_reverse = false;
        break;
      }
      case 3:
      {
        x2_reverse = true;
        y2_reverse = true;
        break;
      }
    }
    walrus_2_captured = false;
    std::cout << "New walrus_2 is spawned! x_speed: "<< x2_speed <<
              ", y_speed: "<< y2_speed <<
              ", x_pos: "<< new_x_pos <<
              ", y_pos: "<< new_y_pos <<"\n";
  }
  else if (animal == "penguin" && !game_over)
  {
    new_x_pos = ((rand() % 941) + 10.0f);
    new_y_pos = ((rand() % 571) + 10.0f);
    penguin.setPosition(new_x_pos,new_y_pos);

    xp_speed = 200.0f + ((rand() % 21) * 5.0f);
    yp_speed = 50.0f + ((rand() % 41) * 5.0f);

    //Gives the walrus a random direction
    int direction = rand() % 4;
    switch (direction)
    {
      case 0:
      {
        xp_reverse = false;
        yp_reverse = false;
        break;
      }
      case 1:
      {
        xp_reverse = false;
        yp_reverse = true;
        break;
      }
      case 2:
      {
        xp_reverse = true;
        yp_reverse = false;
        break;
      }
      case 3:
      {
        xp_reverse = true;
        yp_reverse = true;
        break;
      }
    }
    penguin_captured = false;
    std::cout << "New penguin is spawned! x_speed: "<< xp_speed <<
              ", y_speed: "<< yp_speed <<
              ", x_pos: "<< new_x_pos <<
              ", y_pos: "<< new_y_pos <<"\n";
  }
}
