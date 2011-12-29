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


#include "GameRenderer.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "CompGraphic.h"

GameRenderer::GameRenderer(sf::RenderWindow &render_window)
{
  render_window_ = &render_window;
}

GameRenderer::~GameRenderer()
{

}

void GameRenderer::draw(EntityForm& form)
{
  form.getComponent<comp::Graphic>(comp::GRAPHIC)->drawOn(*this);
}

void GameRenderer::draw(res::GraphicPtr graph, ScreenPos pos, int frame, int angle)
{
  sf::Texture texture;
  
  texture.LoadFromImage(graph->getImage(frame));
  
  sf::Sprite sprite;
  sprite.SetTexture(texture);
  
  sprite.SetPosition(pos);
  
  render_window_->Draw(sprite);
}


void GameRenderer::display(void )
{
  render_window_->Display();
}