#pragma once
#include"Graphics.h"
#include"Cell.h"
class Board
{
public:
	Board(int numBombs,Graphics& gfx);
	void MakeCellsAroundNumbers(const Location & loc);
	void IncreaseNumbersAround(const Location & loc);
	void DrawBoard();
	void GetLeftClick(Location & loc);
	void GetRightClick(Location & loc);
	void UncoverAround(const Location loc);
	bool IsGameOver();
public:
	static constexpr int CellSize = 40;
	static constexpr int Width = Graphics::ScreenWidth / CellSize;
	static constexpr int Height = Graphics::ScreenHeight / CellSize;

private:
	Graphics & gfx;
	Cell _cells[Width*Height];
	int _numBombs;
	bool _isOver;
};