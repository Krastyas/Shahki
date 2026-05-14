#pragma once
#include "board.h"
#include <cstdio>

// Сохранить игру в бинарный файл
inline bool saveGame(const char* filename, const desk& board, int aiDifficulty, bool isWhiteHuman) {
	FILE* file = fopen(filename, "wb");
	if (file == nullptr)
		return false;

	// Сохраняем доску
	fwrite(board.place, sizeof(piece), 64, file);

	// Сохраняем переменные состояния доски
	fwrite(&board.mustCapt, sizeof(int), 1, file);
	fwrite(&board.currentColor, sizeof(int), 1, file);
	fwrite(&board.black, sizeof(int), 1, file);
	fwrite(&board.white, sizeof(int), 1, file);
	fwrite(&board.mustKiller, sizeof(position), 1, file);

	// Сохраняем уровень сложности и цвет игрока
	fwrite(&aiDifficulty, sizeof(int), 1, file);
	fwrite(&isWhiteHuman, sizeof(bool), 1, file);

	fclose(file);
	return true;
}

// Загрузить игру из бинарного файла
inline bool loadGame(const char* filename, desk& board, int& aiDifficulty, bool& isWhiteHuman) {
	FILE* file = fopen(filename, "rb");
	if (file == nullptr)
		return false;

	// Загружаем доску
	if (fread(board.place, sizeof(piece), 64, file) != 64) {
		fclose(file);
		return false;
	}

	// Загружаем переменные состояния доски
	if (fread(&board.mustCapt, sizeof(int), 1, file) != 1) {
		fclose(file);
		return false;
	}
	if (fread(&board.currentColor, sizeof(int), 1, file) != 1) {
		fclose(file);
		return false;
	}
	if (fread(&board.black, sizeof(int), 1, file) != 1) {
		fclose(file);
		return false;
	}
	if (fread(&board.white, sizeof(int), 1, file) != 1) {
		fclose(file);
		return false;
	}
	if (fread(&board.mustKiller, sizeof(position), 1, file) != 1) {
		fclose(file);
		return false;
	}

	// Загружаем уровень сложности и цвет игрока
	if (fread(&aiDifficulty, sizeof(int), 1, file) != 1) {
		fclose(file);
		return false;
	}
	if (fread(&isWhiteHuman, sizeof(bool), 1, file) != 1) {
		fclose(file);
		return false;
	}

	fclose(file);
	return true;
}
