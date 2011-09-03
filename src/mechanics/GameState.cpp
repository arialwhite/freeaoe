/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "GameState.h"

#include "mechanics/GameManager.h"
#include "render/RenderGame.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "commands/CommandSpawn.h"

void GameState::init()
{
    IState::init();
    
    game_renderer_ = new RenderGame(render_target_);
    game_manager_ = new GameManager();
    
    game_manager_->setGameRenderer(game_renderer_);
    
    //Test:
    game_manager_->queueCommand(new CommandSpawn(0, 281, 200, 200));
    game_manager_->queueCommand(new CommandSpawn(0, 234, 100, 200));
}


void GameState::draw()
{
  game_renderer_->draw();
}

void GameState::update()
{
  game_manager_->update();
}

void GameState::handleEvent(sf::Event event)
{

}

GameState::GameState(sf::RenderTarget *render_target) 
            : render_target_(render_target)
{

}

GameState::GameState(const GameState& other)
{

}

GameState::~GameState()
{
  delete game_manager_;
  delete game_renderer_;
}
