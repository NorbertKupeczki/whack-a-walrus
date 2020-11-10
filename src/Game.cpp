
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(nullptr));
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

  if(!penguin_texture.loadFromFile("Data/Images/penguin.png"))
  {
    std::cout << "penguin texture didn't load\n";
  }
  penguin.setTexture(penguin_texture);
  penguin.setPosition(window.getSize().x / 2 - penguin.getGlobalBounds().width / 2,500);

  //init music
  if (!music.openFromFile("Data/Sound/bg_music.ogg"))
  {
    std::cout << "Music file didn't load";
  }
  music.setVolume(volume);
  music.setLoop(true);
  music.play();

  //init sound
  if (!buffer.loadFromFile("Data/Sound/whack.ogg"))
  {
    std::cout << "Sound didn't load to buffer!\n";
  }
  whack.setBuffer(buffer);

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

  rules.setString("You have to catch as many walruses as you"
                  "\ncan within 60 seconds, but try not to capture"
                  "\nthe penguin. For each walrus captured, you score"
                  "\n1 point, but for each penguin you lose 5."
                  "\n\nKey bindings:"
                  "\n[Q] - Quite game"
                  "\n[M] - Turn music On/Off");
  rules.setFont(font);
  rules.setCharacterSize(20);
  rules.setFillColor(sf::Color(255,255,255,200));
  rules.setPosition(
    window.getSize().x / 2 - rules.getGlobalBounds().width / 2,
    300);

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
  game_over_text.setFillColor(sf::Color(255,0,0,200));
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
    if (walrus_1.getPosition().x < 0 && !walrus_1_captured)
    {
      walrus_1.move(2,0);
    }
    else
    {
      walrus_1.move(-2,0);
    }
    x1_reverse = !x1_reverse;
    x1_speed = 200 + ((rand() % 21) * 5);
    y1_speed = 50 + ((rand() % 41) * 5);
  }

  if ((walrus_1.getPosition().y > (window.getSize().y - walrus_1.getGlobalBounds().height)) ||
      (walrus_1.getPosition().y < 0))
  {
    if (walrus_1.getPosition().y < 0 && !walrus_1_captured)
    {
      walrus_1.move(0,2);
    }
    else
    {
      walrus_1.move(0,-2);
    }
    y1_reverse = !y1_reverse;
    x1_speed = 200 + ((rand() % 21) * 5);
    y1_speed = 50 + ((rand() % 41) * 5);
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
    if (walrus_2.getPosition().x < 0 && !walrus_2_captured)
    {
      walrus_2.move(2,0);
    }
    else
    {
      walrus_2.move(-2,0);
    }
    x2_reverse = !x2_reverse;
    x2_speed = 200 + ((rand() % 21) * 5);
    y2_speed = 50 + ((rand() % 41) * 5);
  }

  if ((walrus_2.getPosition().y > (window.getSize().y - walrus_2.getGlobalBounds().height)) ||
      (walrus_2.getPosition().y < 0))
  {
    if (walrus_2.getPosition().y < 0 && !walrus_2_captured)
    {
      walrus_2.move(0,2);
    }
    else
    {
      walrus_2.move(0,-2);
    }
    y2_reverse = !y2_reverse;
    x2_speed = 200 + ((rand() % 21) * 5);
    y2_speed = 50 + ((rand() % 41) * 5);
  }

  //Penguin movement and directions
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
      0,
      0,
      penguin.getLocalBounds().width,
      penguin.getLocalBounds().height));
  }
  else
  {
    penguin.move(1.0f * xp_speed * dt, 1.0f * yp_speed * dt);
    penguin.setTextureRect(sf::IntRect(
      0,
      0,
      penguin.getLocalBounds().width,
      penguin.getLocalBounds().height));
  }

  if ((penguin.getPosition().x > (window.getSize().x - penguin.getGlobalBounds().width)) ||
      (penguin.getPosition().x < 0))
  {
    if(penguin.getPosition().x < 0 && !penguin_captured)
    {
      penguin.move(2,0);
    }
    else
    {
      penguin.move(-2,0);
    }
    xp_reverse = !xp_reverse;
    xp_speed = 200 + ((rand() % 21) * 5);
    yp_speed = 50 + ((rand() % 41) * 5);
  }

  if ((penguin.getPosition().y > (window.getSize().y - penguin.getGlobalBounds().height)) ||
      (penguin.getPosition().y < 0))
  {
    if(penguin.getPosition().y < 0 && !penguin_captured)
    {
      penguin.move(0,2);
    }
    else
    {
      penguin.move(0,-2);
    }
    yp_reverse = !yp_reverse;
    xp_speed = 200 + ((rand() % 21) * 5);
    yp_speed = 50 + ((rand() % 41) * 5);
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

    xp_speed, yp_speed, x1_speed, x2_speed, y1_speed, y2_speed = 0;
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

  //If any character's state is captured, spawn it after the respawn time
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
  else if (penguin_captured)
  {
    if (penguin_timer > 0)
    {
      penguin_timer -= dt;
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
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // check if in bounds of walrus 1 Sprite
  if (collisionCheck(click, walrus_1))
  {
    std::cout << "Collision detected: Walrus 1\n";
    std::string new_score;
    score++;
    new_score = "Score: " + std::to_string(score);
    score_text.setString(new_score);
    //Removing the walrus from the scene
    walrus_1.setPosition(-walrus_1.getLocalBounds().width-10,0);
    x1_speed,y1_speed = 0;
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
    walrus_2.setPosition(-walrus_2.getLocalBounds().width-10,0);
    x2_speed,y2_speed = 0;
    walrus_2_respawn_timer = 0.5;
    walrus_2_captured = true;
  }
  else if (collisionCheck(click, penguin))
  {
    std::cout << "Collision detected: Penguin 2\n";
    std::string new_score;
    score -= 5;
    new_score = "Score: " + std::to_string(score);
    score_text.setString(new_score);
    //Removing penguin from the scene
    penguin.setPosition(-penguin.getLocalBounds().width-10,0);
    xp_speed,yp_speed = 0;
    penguin_timer = 0.5;
    penguin_captured = true;
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
    whack.play();
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
  if (walrus_1_captured && !game_over)
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
  else if (walrus_2_captured && !game_over)
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
  else if (penguin_captured && !game_over)
  {
    int new_x_ops = ((rand() % 941) + 10);
    int new_y_pos = ((rand() % 571) + 10);
    penguin.setPosition(new_x_ops,new_y_pos);

    xp_speed = 200 + ((rand() % 21) * 5);
    yp_speed = 50 + ((rand() % 41) * 5);

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
              ", x_pos: "<< new_x_ops <<
              ", y_pos: "<< new_y_pos <<"\n";
  }
}
