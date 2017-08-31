/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(20,gfx),
	check(false),
	count(0)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!brd.IsGameOver())
	{
		if (wnd.mouse.LeftIsPressed())
		{
			int x = wnd.mouse.GetPosX();
			int y = wnd.mouse.GetPosY();
			Location l = { x,y };
			brd.GetLeftClick(l);
		}

		//cheking the right mouse click
		//while ensuring the program detects only one press at a time
		if (check == false)
		{
			if (wnd.mouse.RightIsPressed())
			{
				int x = wnd.mouse.GetPosX();
				int y = wnd.mouse.GetPosY();
				Location l = { x,y };
				brd.GetRightClick(l);
				check = true;
			}

		}
		if (check)
		{
			count++;
		}
		if (count == 15)
		{
			count = 0;
			check = false;
		}
	}
}

void Game::ComposeFrame()
{
	brd.DrawBoard();
	
}
