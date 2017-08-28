#pragma once
#include"Graphics.h"
#include"Location.h"
class Cell
{
public:
	enum class CellCont
	{
		Empty,
		Number,
		Bomb
	};
	enum class CellCover
	{
		Blank = 0,
		Mark = 1,
		Quest = 2

	};
public:
	Cell(CellCover cov,CellCont cont,const Location& loc);
	Cell(const Location& loc);								
	Cell(int a, const Location& loc);						//for the case CellCont is a number
	Cell();
	void Click();
	CellCont GetContent() const;
	CellCover GetCover() const;
	void Draw(Graphics& gfx,int size);
	void SetCover(CellCover c);
	void SetContent(CellCont c);
	void IncreaseNum();
	const Location& GetLocation();
	
private:
	Location _loc;
	bool _clicked;
	CellCont _content;
	CellCover _cover;
	int _number;				//only for the case CellConst is a number else its 0
};