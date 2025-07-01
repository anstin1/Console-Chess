#include "Bishop.h"
#include <iostream>

Bishop::Bishop(Team team, std::pair<int, int> pos)
	: Piece(team, pos, BISHOP) {}

void Bishop::sayMyName()
{
	std::cout << (m_team == BLACK ? "BLACK " : "WHITE ") << "BISHOP" << std::endl;
}

void Bishop::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<std::tuple<int, int, Piece::MoveType>> moves;
	int dx_copy;
	int dy_copy;
	for (int dx = -1; dx <= 1; dx += 2)
	{
		for (int dy = -1; dy <= 1; dy += 2)
		{
			dx_copy = dx;
			dy_copy = dy;
			while (field[m_pos.first + dx_copy][m_pos.second + dy_copy] == nullptr
				&& (m_pos.first + dx_copy >= 0 && m_pos.first + dx_copy <= 7 && m_pos.second + dy_copy >= 0 && m_pos.second + dy_copy <= 7))
			{
				moves = pushMove(moves,
					     std::tuple<int, int, Piece::MoveType>(m_pos.first + dx_copy, m_pos.second + dy_copy, Piece::NORMAL),
						 getOwnKing(field),
						 field,
						 checkCheck);
				if (dx_copy < 0)
				{
					dx_copy -= 1;
				}
				else
				{
					dx_copy += 1;
				}
				if (dy_copy < 0)
				{
					dy_copy -= 1;
				}
				else
				{
					dy_copy += 1;
				}
			}
			if (field[m_pos.first + dx_copy][m_pos.second + dy_copy] != nullptr
				&& (m_pos.first + dx_copy >= 0 && m_pos.first + dx_copy <= 7 && m_pos.second + dy_copy >= 0 && m_pos.second + dy_copy <= 7))
			{
				if (field[m_pos.first + dx_copy][m_pos.second + dy_copy]->getTeam() != m_team)
				{
					moves = pushMove(moves,
						std::tuple<int, int, Piece::MoveType>(m_pos.first + dx_copy, m_pos.second + dy_copy, Piece::NORMAL),
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}

	m_possibleMoves = moves;
}



