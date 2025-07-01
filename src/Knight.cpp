#include "Knight.h"
#include <iostream>

Knight::Knight(Team team, std::pair<int, int> pos)
	: Piece(team, pos, KNIGHT) {}

void Knight::sayMyName()
{
	std::cout << (m_team == BLACK ? "BLACK " : "WHITE ") << "KNIGHT" << std::endl;
}

void Knight::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<std::tuple<int, int, Piece::MoveType>> moves;
	
	for (int dx = -2; dx <= 2 ; dx += 4)
	{
		for (int dy = -1; dy <= 1; dy += 2)
		{
			if (m_pos.first + dx >= 0 && m_pos.first + dx <= 7 && m_pos.second + dy >= 0 && m_pos.second + dy <= 7)
			{
				if (field[m_pos.first + dx][m_pos.second + dy] == nullptr)
				{
					moves = pushMove(moves,
									 std::tuple<int, int, Piece::MoveType>(m_pos.first + dx, m_pos.second + dy, Piece::NORMAL),
									 getOwnKing(field),
									 field,
									 checkCheck);
				}
				else if (field[m_pos.first + dx][m_pos.second + dy] != nullptr)
				{
					if (field[m_pos.first + dx][m_pos.second + dy]->getTeam() != m_team)
					{
						moves = pushMove(moves,
										 std::tuple<int, int, Piece::MoveType>(m_pos.first + dx, m_pos.second + dy, Piece::NORMAL),
										 getOwnKing(field),
										 field,
										 checkCheck);
					}
				}
			}
		}
	}

	for (int dy = -2; dy <= 2; dy += 4)
	{
		for (int dx = -1; dx <= 1; dx += 2)
		{
			if (m_pos.first + dx >= 0 && m_pos.first + dx <= 7 && m_pos.second + dy >= 0 && m_pos.second + dy <= 7)
			{
				if (field[m_pos.first + dx][m_pos.second + dy] == nullptr)
				{
					moves = pushMove(moves,
						std::tuple<int, int, Piece::MoveType>(m_pos.first + dx, m_pos.second + dy, Piece::NORMAL),
						getOwnKing(field),
						field,
						checkCheck);
				}
				else if (field[m_pos.first + dx][m_pos.second + dy] != nullptr)
				{
					if (field[m_pos.first + dx][m_pos.second + dy]->getTeam() != m_team)
					{
						moves = pushMove(moves,
							std::tuple<int, int, Piece::MoveType>(m_pos.first + dx, m_pos.second + dy, Piece::NORMAL),
							getOwnKing(field),
							field,
							checkCheck);
					}
				}
			}
		}
	}

	m_possibleMoves = moves;
}