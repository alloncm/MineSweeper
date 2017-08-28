#include "Board.h"
#include<random>
#include<ctime>
#include<assert.h>

Board::Board(int numBombs, Graphics & g) :
	gfx(g)
{
	_numBombs = numBombs;

	//initializing the array with blank empty cells 
	for (int i = 0; i < Width*Height; i++)
	{
		int y, x;
		y = i / Width;
		x = i - (Width*y);
		_cells[i] = Cell({x,y});
	}

	//init the random obj
	std::mt19937 gen(static_cast<std::mt19937::result_type>(std::time(nullptr)));
	std::uniform_int_distribution<int> xdist(0, Board::Width - 1);
	std::uniform_int_distribution<int> ydist(0, Board::Height - 1);

	Location newloc;

	//initilizing the bombs
	for (int i = 0; i < _numBombs; i++)
	{
		do
		{
			newloc.x = xdist(gen);
			newloc.y = ydist(gen);
		} while (_cells[newloc.y*Width + newloc.x].GetCover() != Cell::CellCover::Blank || 
			_cells[newloc.y*Width + newloc.x].GetContent() != Cell::CellCont::Empty);
		_cells[newloc.y*Width + newloc.x] = Cell(Cell::CellCover::Blank, Cell::CellCont::Bomb,newloc);
	}

	//initilizing the numbers
	for (int i = 0; i < Width*Height; i++)
	{
		if (_cells[i].GetContent() == Cell::CellCont::Bomb)
		{
			MakeCellsAroundNumbers(_cells[i].GetLocation());
			IncreaseNumbersAround(_cells[i].GetLocation());
		}
	}
}

void Board::MakeCellsAroundNumbers(const Location & loc)
{
	assert(_cells[loc.y*Width + loc.x].GetContent() == Cell::CellCont::Bomb);

	int startY = -1, startX = -1;
	int finishY = 1, finishX = 1;
	switch (loc.y)
	{
	case 0:
		startY = 0;
		break;
	case Height - 1:
		finishY = 0;
	}
	switch (loc.x)
	{
	case 0:
		startX = 0;
		break;
	case Width - 1:
		finishX = 0;
	}

	for (int i = startY; i <= finishY; i++)
	{
		for (int j = startX; j <= finishX; j++)
		{
			if (_cells[(loc.y + i) * Width + (loc.x + j)].GetContent() == Cell::CellCont::Empty)
			{
				_cells[(loc.y + i) *Width + (loc.x + j)].SetContent(Cell::CellCont::Number);
			}
		}
	}
}

void Board::IncreaseNumbersAround(const Location & loc)
{
	assert(_cells[loc.y*Width + loc.x].GetContent() == Cell::CellCont::Bomb);

	int startY = -1, startX = -1;
	int finishY = 1, finishX = 1;
	switch (loc.y)
	{
	case 0:
		startY = 0;
		break;
	case Height - 1:
		finishY = 0;
	}
	switch (loc.x)
	{
	case 0:
		startX = 0;
		break;
	case Width - 1:
		finishX = 0;
	}

	for (int i = startY; i <= finishY; i++)
	{
		for (int j = startX; j <= finishX; j++)
		{
			if (_cells[(loc.y + i) * Width + (loc.x + j)].GetContent() == Cell::CellCont::Number)
			{
				_cells[(loc.y + i) *Width + (loc.x + j)].IncreaseNum();
			}
		}
	}
}

void Board::DrawBoard()
{
	for (int i = 0; i < Width*Height; i++)
	{
		assert(_cells[i].GetLocation().x >= 0);
		assert(_cells[i].GetLocation().x < Board::Width);
		assert(_cells[i].GetLocation().y >= 0);
		assert(_cells[i].GetLocation().y < Board::Height);
		_cells[i].Draw(gfx,Board::CellSize);
	}
}

void Board::GetLeftClick(Location & loc)
{
	int x = loc.x / Board::CellSize;
	int y = loc.y / Board::CellSize;
	_cells[y*Width + x].Click();
}

void Board::GetRightClick(Location & loc)
{
	int x = loc.x / Board::CellSize;
	int y = loc.y / Board::CellSize;
	Cell::CellCover cover = _cells[y*Width + x].GetCover();
	switch (cover)
	{
	case Cell::CellCover::Blank:
		cover = Cell::CellCover::Mark;
		break;
	case Cell::CellCover::Mark:
		cover = Cell::CellCover::Quest;
		break;
	case Cell::CellCover::Quest:
		cover = Cell::CellCover::Blank;
		break;
	}
	_cells[y*Width + x].SetCover(cover);
}

void Board::UncoverAround(const Location loc)
{
	_cells[loc.y*Width + loc.x].Click();
	if (_cells[loc.y*Width + loc.x].GetContent()==Cell::CellCont::Empty)
	{
		int startY = -1, startX = -1;
		int finishY = 1, finishX = 1;
		switch (loc.y)
		{
		case 0:
			startY = 0;
			break;
		case Height - 1:
			finishY = 0;
		}
		switch (loc.x)
		{
		case 0:
			startX = 0;
			break;
		case Width - 1:
			finishX = 0;
		}

		for (int i = startY; i <= finishY; i++)
		{
			for (int j = startX; j <= finishX; j++)
			{
				if (_cells[(loc.y + i) * Width + (loc.x + j)].GetContent() == Cell::CellCont::Number)
				{
					UncoverAround({loc.x+j,loc.y+i});
				}
			}
		}
	}
}
