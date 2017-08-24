#include "Cell.h"
#include<assert.h>

Cell::Cell(CellCover cov, CellCont cont,const Location& loc)
{
	this->_cover = cov;
	this->_content = cont;
	this->_clicked = false;
	this->_number = 0;
	this->_loc = loc;
}

Cell::Cell(const Location& loc)
{
	this->_cover = CellCover::Blank;
	this->_content = CellCont::Empty;
	this->_clicked = false;
	this->_number = 0;
	this->_loc = loc;
}

Cell::Cell(int a, const Location& loc)
{
	Cell::Cell(CellCover::Blank, CellCont::Number,loc);
	_number = a;
	
}

Cell::Cell()
{
	Cell::Cell({ 0,0 });
}

void Cell::Click()
{
	_clicked = true;
}

Cell::CellCont Cell::GetContent() const
{
	return _content;
}

Cell::CellCover Cell::GetCover() const 
{
	return _cover;
}

void Cell::Draw(Graphics & gfx,int size)
{
	Color c;
	
	if (!_clicked)
	{
		switch (_cover)
		{
		case CellCover::Blank:
			c = Colors::Magenta;
			break;
		case CellCover::Mark:
			c = Colors::Red;
			break;
		case CellCover::Quest:
			c = Colors::Gray;
			break;
		}
		
		gfx.DrawSmalRect(_loc.x*size, _loc.y*size, size, size, c);
	}
	else
	{
		switch (_content)
		{
		case CellCont::Bomb:
			c = Colors::Blue;
			break;
		case CellCont::Empty:
			c = Colors::White;
			break;
		case CellCont::Number:
			c = Colors::White;
			break;
		}
		gfx.DrawSmalRect(_loc.x*size, _loc.y*size, size, size, c);
	}
}

void Cell::SetCover(CellCover c)
{
	_cover = c;
}

void Cell::SetContent(CellCont c)
{
	_content = c;
}

void Cell::IncreaseNum()
{
	_number++;
}

const Location & Cell::GetLocation()
{
	return _loc;
}
