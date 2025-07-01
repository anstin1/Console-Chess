#include "Piece.h"
#include "King.h"
#include <string>
#include <iostream>

std::vector<std::tuple<int, int, Piece::MoveType>> Piece::pushMove(std::vector<std::tuple<int, int, Piece::MoveType>> moveList,
																   std::tuple<int, int, Piece::MoveType> move,
																   King* king,
																   Piece* field[8][8],
																   bool checkCheck)
{
	if (!checkCheck)
	{
		moveList.push_back(move);
	}
	else
	{
		bool enemyPlace = true;
		king->setCheck(field, king->getPos().first, king->getPos().second);
		Piece* zwisch = &(*field[std::get<0>(move)][std::get<1>(move)]);
		enemyPlace = false;

		if (field[std::get<0>(move)][std::get<1>(move)] != nullptr)
		{
			enemyPlace = true;
			field[std::get<0>(move)][std::get<1>(move)] = nullptr;
		}

		std::swap(field[std::get<0>(move)][std::get<1>(move)], field[m_pos.first][m_pos.second]);
		if (m_type == KING)
		{
			king->setCheck(field, std::get<0>(move), std::get<1>(move));
		}
		else
		{
			king->setCheck(field, king->getPos().first, king->getPos().second);
		}
		std::swap(field[std::get<0>(move)][std::get<1>(move)], field[m_pos.first][m_pos.second]);

		if (enemyPlace)
		{
			field[std::get<0>(move)][std::get<1>(move)] = &(*zwisch);
		}
		if (!king->getCheck())
		{
			moveList.push_back(move);
		}
		king->setCheck(field, king->getPos().first, king->getPos().second);
	}
	return moveList;
}

King* Piece::getOwnKing(Piece* field[8][8])
{
	for  (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (field[i][j] != nullptr)
			{
				if (field[i][j]->getTeam() == m_team && field[i][j]->getType() == Piece::KING)
				{
					King* ret = static_cast<King*>(field[i][j]);
					return ret;
				}
			}
		}
	}
	return nullptr;
}

Piece::Piece(Team team, std::pair<int, int> pos, PieceType type)
	: m_team(team), m_pos(pos), m_type(type), m_hasMoved(false) {}

Piece::Piece(const Piece& piece)
	: m_team(piece.m_team), m_pos(piece.m_pos), m_type(piece.m_type), m_hasMoved(false) {}

Piece::~Piece() {}

void Piece::render() {
	// Print a single character for the piece
	char c = '.';
	switch (m_type) {
		case PAWN:   c = (m_team == WHITE) ? 'P' : 'p'; break;
		case ROOK:   c = (m_team == WHITE) ? 'R' : 'r'; break;
		case KNIGHT: c = (m_team == WHITE) ? 'N' : 'n'; break;
		case BISHOP: c = (m_team == WHITE) ? 'B' : 'b'; break;
		case KING:   c = (m_team == WHITE) ? 'K' : 'k'; break;
		case QUEEN:  c = (m_team == WHITE) ? 'Q' : 'q'; break;
		default:     c = '.'; break;
	}
	std::cout << c;
}

void Piece::sayMyName() {
	std::cout << "No Piece here" << std::endl;
}
