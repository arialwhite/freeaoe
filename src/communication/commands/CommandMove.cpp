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


#include "CommandMove.h"
#include <server/GameServer.h>

CommandMove::CommandMove(sf::Uint32 unit_id, sf::Uint32 dest_x, 
                         sf::Uint32 dest_y): unit_id_(unit_id), dest_x_(dest_x),
                         dest_y_(dest_y)
{

}


CommandMove::CommandMove(const CommandMove& other)
{

}

CommandMove::~CommandMove()
{

}

void CommandMove::execute(GameServer *gs)
{

}