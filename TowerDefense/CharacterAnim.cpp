#include "CharacterAnim.h"
using namespace Animation;

CharacterAnim::CharacterAnim()
{
	isLooping = true;
}

void CharacterAnim::SetParameters(int w, int h)
{
	frameWidth = w;
	frameHeight = h;
}

void CharacterAnim::LoadTexture(sf::String fileName, int row_index)
{
	tex.loadFromFile(fileName, sf::IntRect(0, row_index*frameHeight, columns*frameWidth, rows*frameHeight));
}

CharacterAnim::~CharacterAnim()
{
}

const int CharacterAnim::GetRows()
{
	return rows;
}


const int CharacterAnim::GetColumns()
{
	return columns;
}

const int CharacterAnim::FrameWidth()
{
	return frameWidth;
}

const int CharacterAnim::FrameHeight()
{
	return frameHeight;
}