#include "Game.h"
#include <iostream>

Game::Game()
       :pl1(new Pawn(Piece::WHITE, std::pair<int, int>(0, 1))),
        pl2(new Pawn(Piece::WHITE, std::pair<int, int>(1, 1))),
        pl3(new Pawn(Piece::WHITE, std::pair<int, int>(2, 1))),
        pl4(new Pawn(Piece::WHITE, std::pair<int, int>(3, 1))),
        pl5(new Pawn(Piece::WHITE, std::pair<int, int>(4, 1))),
        pl6(new Pawn(Piece::WHITE, std::pair<int, int>(5, 1))),
        pl7(new Pawn(Piece::WHITE, std::pair<int, int>(6, 1))),
        pl8(new Pawn(Piece::WHITE, std::pair<int, int>(7, 1))),
        pb1(new Pawn(Piece::BLACK, std::pair<int, int>(0, 6))),
        pb2(new Pawn(Piece::BLACK, std::pair<int, int>(1, 6))),
        pb3(new Pawn(Piece::BLACK, std::pair<int, int>(2, 6))),
        pb4(new Pawn(Piece::BLACK, std::pair<int, int>(3, 6))),
        pb5(new Pawn(Piece::BLACK, std::pair<int, int>(4, 6))),
        pb6(new Pawn(Piece::BLACK, std::pair<int, int>(5, 6))),
        pb7(new Pawn(Piece::BLACK, std::pair<int, int>(6, 6))),
        pb8(new Pawn(Piece::BLACK, std::pair<int, int>(7, 6))),
        rb1(new Rook(Piece::BLACK, std::pair<int, int>(0, 7))),
        rb2(new Rook(Piece::BLACK, std::pair<int, int>(7, 7))),
        rl1(new Rook(Piece::WHITE, std::pair<int, int>(0, 0))),
        rl2(new Rook(Piece::WHITE, std::pair<int, int>(7, 0))),
        nb1(new Knight(Piece::BLACK, std::pair<int, int>(1, 7))),
        nb2(new Knight(Piece::BLACK, std::pair<int, int>(6, 7))),
        nl1(new Knight(Piece::WHITE, std::pair<int, int>(1, 0))),
        nl2(new Knight(Piece::WHITE, std::pair<int, int>(6, 0))),
        bb1(new Bishop(Piece::BLACK, std::pair<int, int>(2, 7))),
        bb2(new Bishop(Piece::BLACK, std::pair<int, int>(5, 7))),
        bl1(new Bishop(Piece::WHITE, std::pair<int, int>(2, 0))),
        bl2(new Bishop(Piece::WHITE, std::pair<int, int>(5, 0))),
        kb1(new King(Piece::BLACK, std::pair<int, int>(3, 7))),
        kl1(new King(Piece::WHITE, std::pair<int, int>(3, 0))),
        qb1(new Queen(Piece::BLACK, std::pair<int, int>(4, 7))),
        ql1(new Queen(Piece::WHITE, std::pair<int, int>(4, 0))),
        m_turn(Piece::WHITE),
        m_checkEnPassant(true)
{
    m_field[0][7] = rb1;
    m_field[7][7] = rb2;
    m_field[0][0] = rl1;
    m_field[7][0] = rl2;

    m_field[1][7] = nb1;
    m_field[6][7] = nb2;
    m_field[1][0] = nl1;
    m_field[6][0] = nl2;

    m_field[2][7] = bb1;
    m_field[5][7] = bb2;
    m_field[2][0] = bl1;
    m_field[5][0] = bl2;

    m_field[3][7] = kb1;
    m_field[3][0] = kl1;

    m_field[4][7] = qb1;
    m_field[4][0] = ql1;

    m_field[0][1] = pl1;
    m_field[1][1] = pl2;
    m_field[2][1] = pl3;
    m_field[3][1] = pl4;
    m_field[4][1] = pl5;
    m_field[5][1] = pl6;
    m_field[6][1] = pl7;
    m_field[7][1] = pl8;

    m_field[0][6] = pb1;
    m_field[1][6] = pb2;
    m_field[2][6] = pb3;
    m_field[3][6] = pb4;
    m_field[4][6] = pb5;
    m_field[5][6] = pb6;
    m_field[6][6] = pb7;
    m_field[7][6] = pb8;

    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            m_field[j][i] = nullptr;
        }
    }

    calcAllMoves();
}
 

Game::~Game()
{
}


Piece* Game::getFieldPos(int row, int col)
{
    if (row < 0 || row > 7 || col < 0 || col > 7) return nullptr;
    return m_field[row][col];
}


void Game::move(Piece* start, std::tuple<int, int, Piece::MoveType> move)
{
    if (m_checkEnPassant)
    {
        disableEnPassant();
    }
    else
    {
        m_checkEnPassant = true;
    }

    switch (std::get<2>(move))
    {
        case Piece::NORMAL:
            normal(start->getPos().first, start->getPos().second, std::get<0>(move), std::get<1>(move));
            break;
        case Piece::CASTLE:
            castles(start->getPos().first, start->getPos().second, std::get<0>(move), std::get<1>(move));
            break;
        case Piece::ENPASSANT:
            enPassant(start->getPos().first, start->getPos().second, std::get<0>(move), std::get<1>(move));
            break;
        case Piece::NEWPIECE:
            exchange(start->getPos().first, start->getPos().second, std::get<0>(move), std::get<1>(move));
            break;
        default:
            break;
    }

    gameState();
}


void Game::normal(int xStart, int yStart, int xEnd, int yEnd)
{
    m_field[xEnd][yEnd] = getFieldPos(xStart, yStart);
    m_field[xEnd][yEnd]->m_hasMoved = true;
    m_field[xStart][yStart] = nullptr;
    m_field[xEnd][yEnd]->setPosition(std::pair<int, int>(xEnd, yEnd));
    if (m_field[xEnd][yEnd] != nullptr)
    {
        m_field[xEnd][yEnd]->render();
    }

    if (m_field[xEnd][yEnd]->getType() == Piece::PAWN)
    {
        if (abs(yEnd - yStart) == 2)
        {
            if (xEnd - 1 >= 0)
            {
                if (m_field[xEnd - 1][yEnd] != nullptr)
                {
                    if (m_field[xEnd - 1][yEnd]->getType() == Piece::PAWN)
                    {
                        Pawn* pwn = static_cast<Pawn*>(m_field[xEnd - 1][yEnd]);
                        pwn->setEnPassant(std::pair<bool, int>(true, -1));
                        m_checkEnPassant = false;
                    }
                }
            }

            if (xEnd + 1 <= 7)
            {
                if (m_field[xEnd + 1][yEnd] != nullptr)
                {
                    if (m_field[xEnd + 1][yEnd]->getType() == Piece::PAWN)
                    {
                        Pawn* pwn = static_cast<Pawn*>(m_field[xEnd + 1][yEnd]);
                        pwn->setEnPassant(std::pair<bool, int>(true, 1));
                        m_checkEnPassant = false;
                    }
                }
            }
        }
    }
}


void Game::enPassant(int xStart, int yStart, int xEnd, int yEnd)
{
    Pawn* pawn_start = static_cast<Pawn*>(m_field[xStart][yStart]);
    m_field[xEnd][yEnd - pawn_start->m_dy] = nullptr;
    m_field[xEnd][yEnd] = getFieldPos(xStart, yStart);
    m_field[xEnd][yEnd]->m_hasMoved = true;
    m_field[xStart][yStart] = nullptr;
    m_field[xEnd][yEnd]->setPosition(std::pair<int, int>(xEnd, yEnd));
    m_field[xEnd][yEnd]->render();
}


void Game::exchange(int xStart, int yStart, int xEnd, int yEnd)
{
    Piece::Team team = m_field[xStart][yStart]->getTeam();
    std::string choice;
    std::cout << "Pawn promotion! Choose (Q)ueen, (R)ook, (B)ishop, or k(N)ight: ";
    std::cin >> choice;
    Piece* promoted = nullptr;
    if (choice == "Q" || choice == "q")
        promoted = new Queen(team, std::pair<int, int>(xEnd, yEnd));
    else if (choice == "R" || choice == "r")
        promoted = new Rook(team, std::pair<int, int>(xEnd, yEnd));
    else if (choice == "B" || choice == "b")
        promoted = new Bishop(team, std::pair<int, int>(xEnd, yEnd));
    else if (choice == "N" || choice == "n")
        promoted = new Knight(team, std::pair<int, int>(xEnd, yEnd));
    else {
        std::cout << "Invalid choice. Promoting to Queen by default.\n";
        promoted = new Queen(team, std::pair<int, int>(xEnd, yEnd));
    }
    m_field[xEnd][yEnd] = promoted;
    m_field[xStart][yStart] = nullptr;
    m_field[xEnd][yEnd]->render();
}


void Game::castles(int xStart, int yStart, int xEnd, int yEnd)
{
    if (xEnd == 0)
    {
        m_field[2][yEnd] = m_field[4][yEnd];
        m_field[3][yEnd] = m_field[0][yEnd];
        m_field[2][yEnd]->m_hasMoved = true;
        m_field[3][yEnd]->m_hasMoved = true;
        m_field[2][yEnd]->setPosition(std::pair<int, int>(2, yEnd));
        m_field[3][yEnd]->setPosition(std::pair<int, int>(3, yEnd));
        m_field[4][yEnd] = nullptr;
        m_field[0][yEnd] = nullptr;
        m_field[2][yEnd]->render();
        m_field[3][yEnd]->render();
    }
    else
    {
        m_field[6][yEnd] = m_field[4][yEnd];
        m_field[5][yEnd] = m_field[7][yEnd];
        m_field[6][yEnd]->m_hasMoved = true;
        m_field[5][yEnd]->m_hasMoved = true;
        m_field[6][yEnd]->setPosition(std::pair<int, int>(6, yEnd));
        m_field[5][yEnd]->setPosition(std::pair<int, int>(5, yEnd));
        m_field[4][yEnd] = nullptr;
        m_field[7][yEnd] = nullptr;
        m_field[6][yEnd]->render();
        m_field[5][yEnd]->render();
    }
}

void Game::gameState()
{
    bool lost = true;
    King* pivot = kb1;

    if (m_turn == Piece::BLACK)
    {
        pivot = kl1;
    }

    pivot->setCheck(m_field, kl1->getPos().first, kl1->getPos().second);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (m_field[i][j] != nullptr)
            {
                if (m_field[i][j]->getTeam() != m_turn)
                {
                    m_field[i][j]->calcPossibleMoves(m_field, true);
                    if (!m_field[i][j]->getPossibleMoves().empty())
                    {
                        lost = false;
                    }
                }
            }
        }
    }

    if (pivot->getCheck() && lost)
    {
        if (m_turn == Piece::BLACK)
        {
            std::cout << "Black wins!";
        }
        else
        {
            std::cout << "White wins!";
        }
    }
    else if (lost)
    {
        if (m_turn == Piece::BLACK)
        {
            std::cout << "Remis!";
        }
        else
        {
            std::cout << "Remis!";
        }
    }
    if (m_turn == Piece::BLACK)
    {
        m_turn = Piece::WHITE;
    }
    else
    {
        m_turn = Piece::BLACK;
    }

}


void Game::disableEnPassant()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (m_field[i][j] != nullptr)
            {
                if (m_field[i][j]->getType() == Piece::PAWN)
                {
                    Pawn* pwn = static_cast<Pawn*>(m_field[i][j]);
                    pwn->setEnPassant(std::pair<bool, int>(false, 0));
                }
            }
        }
    }
}

void Game::calcAllMoves()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (m_field[i][j] != nullptr)
            {
                m_field[i][j]->calcPossibleMoves(m_field, true);
            }
        }
    }
}

bool Game::isValidMove(int x, int y, Piece* piece)
{
    auto list = piece->getPossibleMoves();
    for (const auto& value : list) {
        if (std::get<0>(value) == x && std::get<1>(value) == y) {
            return true;
        }
    }
    return false;
}

void Game::printBoard() {
    std::cout << "  a b c d e f g h\n";
    for (int y = 7; y >= 0; --y) {
        std::cout << y + 1 << " ";
        for (int x = 0; x < 8; ++x) {
            if (m_field[x][y]) m_field[x][y]->render();
            else std::cout << ".";
            std::cout << " ";
        }
        std::cout << y + 1 << std::endl;
    }
    std::cout << "  a b c d e f g h\n";
}
