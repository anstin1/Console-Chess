#include "MainLoop.h"
#include "Game.h"
#include <iostream>
#include <string>

void MainLoop::run() {
	Game game;
	std::string input;
	while (true) {
		game.printBoard();
		std::cout << (game.getTurn() == Piece::WHITE ? "White" : "Black") << " to move. Enter your move (e.g., e2e4): ";
		std::getline(std::cin, input);
		if (input == "exit" || input == "quit") break;
		if (input.length() != 4) {
			std::cout << "Invalid input. Please use format e2e4.\n";
			continue;
		}
		int xStart = input[0] - 'a';
		int yStart = input[1] - '1';
		int xEnd = input[2] - 'a';
		int yEnd = input[3] - '1';
		Piece* piece = game.getFieldPos(xStart, yStart);
		if (!piece || piece->getTeam() != game.getTurn()) {
			std::cout << "No valid piece at that position.\n";
			continue;
		}
		if (!game.isValidMove(xEnd, yEnd, piece)) {
			std::cout << "Invalid move.\n";
			continue;
		}
		// Find the move type
		auto moves = piece->getPossibleMoves();
		for (const auto& move : moves) {
			if (std::get<0>(move) == xEnd && std::get<1>(move) == yEnd) {
				game.move(piece, move);
				break;
			}
		}
		game.calcAllMoves();
	}
	std::cout << "Game ended." << std::endl;
}