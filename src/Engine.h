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

#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>

#include "core/Logger.h"
#include "mechanics/StateManager.h"

namespace sf {
class RenderWindow;
}

class Engine
{

public:
    static const sf::Clock GameClock;

    Engine();
    virtual ~Engine();

    bool setup(const std::shared_ptr<genie::ScnFile> &scenario = nullptr);
    void start();

private:
    void showStartScreen();

    std::unique_ptr<sf::RenderWindow> renderWindow_;
    std::shared_ptr<SfmlRenderTarget> renderTarget_;

    StateManager state_manager_;

    sf::Text fps_label_;
};

