
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

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
  walrus.setTexture(walrus_texture);
  walrus.setPosition(window.getSize().x / 2 - walrus.getGlobalBounds().width / 2,100);

  //init text
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
  title_text.setString("Whack-a-walrus");
  title_text.setFont(font);
  title_text.setCharacterSize(100);
  title_text.setFillColor(sf::Color(255,255,255,128));
  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
    window.getSize().y / 2 - title_text.getGlobalBounds().height / 2);

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

  in_menu = true;

  return true;
}

void Game::update(float dt)
{
  if (reverse)
  {
    walrus.move(-1.0f * speed * dt, 0);
    walrus.setTextureRect(sf::IntRect(
      walrus.getLocalBounds().width,
      0,
      -walrus.getLocalBounds().width,
      walrus.getLocalBounds().height));

  }
  else
  {
    walrus.move(1.0f * speed * dt, 0);
    walrus.setTextureRect(sf::IntRect(
      0,
      0,
      walrus.getLocalBounds().width,
      walrus.getLocalBounds().height));
  }
  if ((walrus.getPosition().x > (window.getSize().x - walrus.getGlobalBounds().width)) ||
      (walrus.getPosition().x < 0))
  {
    reverse = !reverse;
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
  else
  {
    window.draw(background);
    window.draw(walrus);
    window.draw(title_text);
    window.draw(score_text);
  }


}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // check if in bounds of bird Sprite
  if (collisionCheck(click, walrus))
  {
    std::cout << "Collision detected\n";
    std::string new_score;
    score++;
    new_score = "Score: " + std::to_string(score);
    score_text.setString(new_score);
    
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

}
