
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
  std::cout << "Game terminates";
}

bool Game::init()
{
  //init background texture
  if(!background_texture.loadFromFile("Data/Images/background.png"))
  {
    std::cout << "background texture didn't load\n";
  }
  background.setTexture(background_texture);

  //init character texture
  if(!walrus_texture.loadFromFile("Data/Images/walrus.png"))
  {
    std::cout << "walrus texture didn't load\n";
  }
  walrus_1.setTexture(walrus_texture);
  walrus_1.setPosition(window.getSize().x / 2 - walrus_1.getGlobalBounds().width / 2,100);
  walrus_2.setTexture(walrus_texture);
  walrus_2.setPosition(window.getSize().x / 2 - walrus_2.getGlobalBounds().width / 2,500);


  //init text
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
  title_text.setString("Whack-a-walrus");
  title_text.setFont(font);
  title_text.setCharacterSize(30);
  title_text.setFillColor(sf::Color(255,255,255,200));
  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
    10);

  menu_text.setString("Welcome to Whack-a-Walrus\nPlease select an option:");
  menu_text.setFont(font);
  menu_text.setCharacterSize(25);
  menu_text.setFillColor(sf::Color(255,255,255,128));
  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    window.getSize().y / 5 - menu_text.getGlobalBounds().height / 2);

  play_option.setString(">Play<");
  play_option.setFont(font);
  play_option.setCharacterSize(20);
  play_option.setFillColor(sf::Color(255,255,255,128));
  play_option.setPosition(
    window.getSize().x / 3 - play_option.getGlobalBounds().width / 2,
    window.getSize().y / 3 - play_option.getGlobalBounds().height / 2);

  quit_option.setString("Quit");
  quit_option.setFont(font);
  quit_option.setCharacterSize(20);
  quit_option.setFillColor(sf::Color(255,255,255,128));
  quit_option.setPosition(
    (window.getSize().x / 3 - quit_option.getGlobalBounds().width / 2)*2,
    window.getSize().y / 3 - quit_option.getGlobalBounds().height / 2);

  score_text.setString("Score: 0");
  score_text.setFont(font);
  score_text.setCharacterSize(20);
  score_text.setFillColor(sf::Color(255,0,0,255));
  score_text.setPosition(940,10);

  clock_text.setString("Clock");
  clock_text.setFont(font);
  clock_text.setCharacterSize(20);
  clock_text.setFillColor(sf::Color(255,128,0,255));
  clock_text.setPosition(10,10);

  game_over_text.setString("GAME OVER");
  game_over_text.setFont(font);
  game_over_text.setCharacterSize(100);
  game_over_text.setFillColor(sf::Color(255,255,255,128));
  game_over_text.setPosition(
    window.getSize().x / 2 - game_over_text.getGlobalBounds().width / 2,
    window.getSize().y / 3 - game_over_text.getGlobalBounds().height / 2);

  in_menu = true;

  return true;
}

void Game::update(float dt)
{
  //Walrus 1 movement and directions
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

  if ((walrus_1.getPosition().x > (window.getSize().x - walrus_1.getGlobalBounds().width)) ||
      (walrus_1.getPosition().x < 0))
  {
    x1_reverse = !x1_reverse;
  }

  if ((walrus_1.getPosition().y > (window.getSize().y - walrus_1.getGlobalBounds().height)) ||
      (walrus_1.getPosition().y < 0))
  {
    y1_reverse = !y1_reverse;
  }

  //Walrus 2 movement and directions
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

  if ((walrus_2.getPosition().x > (window.getSize().x - walrus_2.getGlobalBounds().width)) ||
      (walrus_2.getPosition().x < 0))
  {
    x2_reverse = !x2_reverse;
  }

  if ((walrus_2.getPosition().y > (window.getSize().y - walrus_2.getGlobalBounds().height)) ||
      (walrus_2.getPosition().y < 0))
  {
    y2_reverse = !y2_reverse;
  }

  // Countdown
  if (!in_menu && game_timer > 0)
  {
    game_timer -= dt;
    int time_in_seconds = game_timer;
    clock_text.setString("Time remaining: " + std::to_string(time_in_seconds));
  }
  else
  {
    clock_text.setString("GAME OVER");
  }

  //When time is up
  if (game_timer < 0)
  {
    game_over = true;
    game_timer -= dt;
    score_text.setPosition(
      window.getSize().x / 2 - score_text.getGlobalBounds().width / 2,
      window.getSize().y / 2 - score_text.getGlobalBounds().height / 2);
    score_text.setCharacterSize(50);
    if (game_timer < -4)
    {
      window.close();
    }

  }

  //If walrus state is captured, spawn it after the respawn time
  if (walrus_1_captured)
  {
    if (walrus_1_respawn_timer > 0)
    {
      walrus_1_respawn_timer -= dt;
    }
    else
    {
      spawn();
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
      spawn();
    }
  }
}

void Game::render()
{
  if (in_menu)
  {
    window.draw(menu_text);
    window.draw(play_option);
    window.draw(quit_option);
  }
  else if (game_over)
  {
    window.draw(game_over_text);
    window.draw(score_text);
  }
  else
  {
    window.draw(background);
    window.draw(walrus_1);
    window.draw(walrus_2);
    window.draw(title_text);
    window.draw(score_text);
    window.draw(clock_text);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // check if in bounds of walrus 1 Sprite
  if (collisionCheck(click, walrus_1))
  {
    std::cout << "Collision detected\n";
    std::string new_score;
    score++;
    new_score = "Score: " + std::to_string(score);
    score_text.setString(new_score);
    //Removing the walrus from the scene
    walrus_1.setPosition(-walrus_1.getLocalBounds().width,0);
    x1_speed = 0;
    walrus_1_respawn_timer = 0.5;
    walrus_1_captured = true;
  }
  // check if in bounds of walrus 1 Sprite
  else if (collisionCheck(click, walrus_2))
  {
    std::cout << "Collision detected: Walrus 2\n";
    std::string new_score;
    score++;
    new_score = "Score: " + std::to_string(score);
    score_text.setString(new_score);
    //Removing walrus 2 from the scene
    walrus_2.setPosition(-walrus_2.getLocalBounds().width,0);
    x2_speed = 0;
    walrus_2_respawn_timer = 0.5;
    walrus_2_captured = true;
  }
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
        play_option.setString(">Play<");
        quit_option.setString("Quit");
      }
      else
      {
        play_option.setString("Play");
        quit_option.setString(">Quit<");
      }
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
      if (play_selected)
      {
        in_menu = false;
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
}

bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
  if (
    (click.x > sprite.getPosition().x) &&
    (click.x < (sprite.getPosition().x + sprite.getGlobalBounds().width)) &&
    (click.y > sprite.getPosition().y) &&
    (click.y < (sprite.getPosition().y + sprite.getGlobalBounds().height))
    )
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Game::spawn()
{
  //Gives the walrus a random speed and spawn location
  if (walrus_1_captured)
  {
    int new_x_ops = ((rand() % 941) + 10);
    int new_y_pos = ((rand() % 571) + 10);
    walrus_1.setPosition(new_x_ops,new_y_pos);

    x1_speed = 200 + ((rand() % 21) * 5);
    y1_speed = 50 + ((rand() % 41) * 5);

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
                 ", x_pos: "<< new_x_ops <<
                 ", y_pos: "<< new_y_pos <<"\n";
  }
  else if (walrus_2_captured)
  {
    int new_x_ops = ((rand() % 941) + 10);
    int new_y_pos = ((rand() % 571) + 10);
    walrus_2.setPosition(new_x_ops,new_y_pos);

    x2_speed = 200 + ((rand() % 21) * 5);
    y2_speed = 50 + ((rand() % 41) * 5);

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
              ", x_pos: "<< new_x_ops <<
              ", y_pos: "<< new_y_pos <<"\n";
  }
}
