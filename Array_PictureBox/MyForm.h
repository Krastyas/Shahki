#pragma once
#include "board.h"
#include "moves.h"
#include "ai.h"
#include "GameSave.h"
#include <iostream>

namespace ArrayPictureBox {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Сводка для MyForm
    /// </summary>
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            gameBoard = nullptr;
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
            if (gameBoard != nullptr)
            {
                delete gameBoard;
            }
            if (blackCasualBmp != nullptr) delete blackCasualBmp;
            if (whiteCasualBmp != nullptr) delete whiteCasualBmp;
            if (blackQueenBmp != nullptr) delete blackQueenBmp;
            if (whiteQueenBmp != nullptr) delete whiteQueenBmp;
        }
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ easyButton;
    private: System::Windows::Forms::Button^ normalButton;
    private: System::Windows::Forms::Button^ hardButton;
    private: System::Windows::Forms::Label^ statusLabel;
    private: System::Windows::Forms::Button^ saveButton;
    private: System::Windows::Forms::Button^ loadInitialButton;
    private: System::Windows::Forms::Button^ menuButton;
    // loadButton removed from UI - moved to menu



    private: System::Windows::Forms::Label^ hintLabel;
    private: System::Windows::Forms::Button^ blackColorButton;
    private: System::Windows::Forms::Button^ whiteColorButton;
    private: System::Windows::Forms::Label^ colorLabel;
    protected:

    private:
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        System::ComponentModel::Container ^components;
        // Массив PictureBox'ов
        array<PictureBox^>^ pb;
        int x0 = 50, y0 = 50, size = 50;
        bool selected = false;
        int selectedX = -1, selectedY = -1;

        // Движок игры
        desk* gameBoard;
        int aiDifficulty = 0;
        bool isWhiteHuman = true;
        Bitmap^ blackCasualBmp;
        Bitmap^ whiteCasualBmp;
        Bitmap^ blackQueenBmp;
        Bitmap^ whiteQueenBmp;

        // Для отображения допустимых ходов
        array<System::Drawing::Color>^ originalColors;
        array<int>^ validMoveIndices;
        int validMoveCount = 0;


#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        void InitializeComponent(void)
        {
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->easyButton = (gcnew System::Windows::Forms::Button());
            this->normalButton = (gcnew System::Windows::Forms::Button());
            this->hardButton = (gcnew System::Windows::Forms::Button());
            this->statusLabel = (gcnew System::Windows::Forms::Label());
            this->saveButton = (gcnew System::Windows::Forms::Button());
            this->loadInitialButton = (gcnew System::Windows::Forms::Button());
            this->menuButton = (gcnew System::Windows::Forms::Button());
            this->hintLabel = (gcnew System::Windows::Forms::Label());
            this->blackColorButton = (gcnew System::Windows::Forms::Button());
            this->whiteColorButton = (gcnew System::Windows::Forms::Button());
            this->colorLabel = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // button1
            // 
            this->button1->BackColor = System::Drawing::Color::LightBlue;
            this->button1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 22.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
            this->button1->ForeColor = System::Drawing::Color::RoyalBlue;
            this->button1->Location = System::Drawing::Point(297, 192);
            this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(275, 94);
            this->button1->TabIndex = 0;
            this->button1->Text = L"Новая игра";
            this->button1->UseVisualStyleBackColor = false;
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // easyButton
            // 
            this->easyButton->BackColor = System::Drawing::Color::LightGreen;
            this->easyButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->easyButton->Location = System::Drawing::Point(200, 308);
            this->easyButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->easyButton->Name = L"easyButton";
            this->easyButton->Size = System::Drawing::Size(133, 62);
            this->easyButton->TabIndex = 1;
            this->easyButton->Text = L"Легко";
            this->easyButton->UseVisualStyleBackColor = false;
            this->easyButton->Visible = false;
            this->easyButton->Click += gcnew System::EventHandler(this, &MyForm::easyButton_Click);
            // 
            // normalButton
            // 
            this->normalButton->BackColor = System::Drawing::Color::Yellow;
            this->normalButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->normalButton->Location = System::Drawing::Point(373, 308);
            this->normalButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->normalButton->Name = L"normalButton";
            this->normalButton->Size = System::Drawing::Size(133, 62);
            this->normalButton->TabIndex = 2;
            this->normalButton->Text = L"Среднее";
            this->normalButton->UseVisualStyleBackColor = false;
            this->normalButton->Visible = false;
            this->normalButton->Click += gcnew System::EventHandler(this, &MyForm::normalButton_Click);
            // 
            // hardButton
            // 
            this->hardButton->BackColor = System::Drawing::Color::LightCoral;
            this->hardButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->hardButton->Location = System::Drawing::Point(547, 308);
            this->hardButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->hardButton->Name = L"hardButton";
            this->hardButton->Size = System::Drawing::Size(133, 62);
            this->hardButton->TabIndex = 3;
            this->hardButton->Text = L"Сложно";
            this->hardButton->UseVisualStyleBackColor = false;
            this->hardButton->Visible = false;
            this->hardButton->Click += gcnew System::EventHandler(this, &MyForm::hardButton_Click);
            // 
            // statusLabel
            // 
            this->statusLabel->AutoSize = true;
            this->statusLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->statusLabel->Location = System::Drawing::Point(67, 615);
            this->statusLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->statusLabel->Name = L"statusLabel";
            this->statusLabel->Size = System::Drawing::Size(328, 20);
            this->statusLabel->TabIndex = 4;
            this->statusLabel->Text = L"Нажмите \'Новая игра\' для начала";
            // 
            // saveButton
            // 
            this->saveButton->BackColor = System::Drawing::Color::LightCyan;
            this->saveButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->saveButton->Location = System::Drawing::Point(67, 578);
            this->saveButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->saveButton->Name = L"saveButton";
            this->saveButton->Size = System::Drawing::Size(160, 31);
            this->saveButton->TabIndex = 5;
            this->saveButton->Text = L"Сохранить игру";
            this->saveButton->UseVisualStyleBackColor = false;
            this->saveButton->Visible = false;
            this->saveButton->Click += gcnew System::EventHandler(this, &MyForm::saveButton_Click);
            // 
            // loadInitialButton
            // 
            this->loadInitialButton->BackColor = System::Drawing::Color::LightCyan;
            this->loadInitialButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->loadInitialButton->Location = System::Drawing::Point(297, 295);
            this->loadInitialButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->loadInitialButton->Name = L"loadInitialButton";
            this->loadInitialButton->Size = System::Drawing::Size(275, 37);
            this->loadInitialButton->TabIndex = 6;
            this->loadInitialButton->Text = L"Загрузить игру";
            this->loadInitialButton->UseVisualStyleBackColor = false;
            this->loadInitialButton->Click += gcnew System::EventHandler(this, &MyForm::menuLoad_Click);
            // 
            // menuButton
            // 
            this->menuButton->BackColor = System::Drawing::Color::LightYellow;
            this->menuButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->menuButton->Location = System::Drawing::Point(237, 578);
            this->menuButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->menuButton->Name = L"menuButton";
            this->menuButton->Size = System::Drawing::Size(160, 31);
            this->menuButton->TabIndex = 11;
            this->menuButton->Text = L"Выход в меню";
            this->menuButton->UseVisualStyleBackColor = false;
            this->menuButton->Visible = false;
            this->menuButton->Click += gcnew System::EventHandler(this, &MyForm::menuButton_Click);
            // 
            // hintLabel
            // 
            this->hintLabel->AutoSize = true;
            this->hintLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->hintLabel->ForeColor = System::Drawing::Color::DarkGreen;
            this->hintLabel->Location = System::Drawing::Point(67, 634);
            this->hintLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->hintLabel->Name = L"hintLabel";
            this->hintLabel->Size = System::Drawing::Size(470, 18);
            this->hintLabel->TabIndex = 7;
            this->hintLabel->Text = L"Кликните на свою шашку, выделенные ячейки - допустимые ходы";
            // 
            // blackColorButton
            // 
            this->blackColorButton->BackColor = System::Drawing::Color::Black;
            this->blackColorButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->blackColorButton->ForeColor = System::Drawing::Color::White;
            this->blackColorButton->Location = System::Drawing::Point(200, 382);
            this->blackColorButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->blackColorButton->Name = L"blackColorButton";
            this->blackColorButton->Size = System::Drawing::Size(160, 62);
            this->blackColorButton->TabIndex = 8;
            this->blackColorButton->Text = L"Черные";
            this->blackColorButton->UseVisualStyleBackColor = false;
            this->blackColorButton->Visible = false;
            this->blackColorButton->Click += gcnew System::EventHandler(this, &MyForm::blackColorButton_Click);
            // 
            // whiteColorButton
            // 
            this->whiteColorButton->BackColor = System::Drawing::Color::White;
            this->whiteColorButton->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->whiteColorButton->ForeColor = System::Drawing::Color::Black;
            this->whiteColorButton->Location = System::Drawing::Point(523, 382);
            this->whiteColorButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->whiteColorButton->Name = L"whiteColorButton";
            this->whiteColorButton->Size = System::Drawing::Size(160, 62);
            this->whiteColorButton->TabIndex = 9;
            this->whiteColorButton->Text = L"Белые";
            this->whiteColorButton->UseVisualStyleBackColor = false;
            this->whiteColorButton->Visible = false;
            this->whiteColorButton->Click += gcnew System::EventHandler(this, &MyForm::whiteColorButton_Click);
            // 
            // colorLabel
            // 
            this->colorLabel->AutoSize = true;
            this->colorLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->colorLabel->Location = System::Drawing::Point(107, 351);
            this->colorLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->colorLabel->Name = L"colorLabel";
            this->colorLabel->Size = System::Drawing::Size(206, 20);
            this->colorLabel->TabIndex = 10;
            this->colorLabel->Text = L"Выберите свой цвет:";
            this->colorLabel->Visible = false;
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(883, 665);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->easyButton);
            this->Controls->Add(this->normalButton);
            this->Controls->Add(this->hardButton);
            this->Controls->Add(this->statusLabel);
            this->Controls->Add(this->saveButton);
            this->Controls->Add(this->loadInitialButton);
            this->Controls->Add(this->menuButton);
            this->Controls->Add(this->hintLabel);
            this->Controls->Add(this->blackColorButton);
            this->Controls->Add(this->whiteColorButton);
            this->Controls->Add(this->colorLabel);
            this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
            this->Name = L"MyForm";
            this->Text = L"Шашки";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
    System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        this->button1->Visible = false;
        this->easyButton->Visible = true;
        this->normalButton->Visible = true;
        this->hardButton->Visible = true;
        this->loadInitialButton->Visible = false;
        this->statusLabel->Text = L"Выберите уровень сложности";
    }

    System::Void easyButton_Click(System::Object^ sender, System::EventArgs^ e) {
        aiDifficulty = 1;
        showColorSelection();
    }

    System::Void normalButton_Click(System::Object^ sender, System::EventArgs^ e) {
        aiDifficulty = 2;
        showColorSelection();
    }

    System::Void hardButton_Click(System::Object^ sender, System::EventArgs^ e) {
        aiDifficulty = 3;
        showColorSelection();
    }

    void showColorSelection() {
        this->easyButton->Visible = false;
        this->normalButton->Visible = false;
        this->hardButton->Visible = false;
        this->colorLabel->Visible = true;
        this->blackColorButton->Visible = true;
        this->whiteColorButton->Visible = true;
        this->statusLabel->Text = L"";
    }

    System::Void blackColorButton_Click(System::Object^ sender, System::EventArgs^ e) {
        isWhiteHuman = false;
        startNewGame();
    }

    System::Void whiteColorButton_Click(System::Object^ sender, System::EventArgs^ e) {
        isWhiteHuman = true;
        startNewGame();
    }

    void startNewGame() {
        this->easyButton->Visible = false;
        this->normalButton->Visible = false;
        this->hardButton->Visible = false;
        this->colorLabel->Visible = false;
        this->blackColorButton->Visible = false;
        this->whiteColorButton->Visible = false;
        this->loadInitialButton->Visible = false;
        this->statusLabel->Text = L"";
        this->saveButton->Visible = true;
        this->menuButton->Visible = true;

        // Инициализируем доску
        if (gameBoard != nullptr)
            delete gameBoard;
        gameBoard = new desk();
        newGame(*gameBoard);
        // Черные всегда ходят первыми
        gameBoard->currentColor = black;

        pb = gcnew array<PictureBox^>(64);

        // Загружаем изображения шашек БЕЗ try/catch
        blackCasualBmp = gcnew Bitmap("..//черная шашка.png");
        whiteCasualBmp = gcnew Bitmap("..//белая шашка.png");
        blackQueenBmp = gcnew Bitmap("..//черная дамка.png");
        whiteQueenBmp = gcnew Bitmap("..//белая дамка.png");

        // Создаем доску 8x8
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                pb[i * 8 + j] = gcnew PictureBox();
                pb[i * 8 + j]->Left = x0 + j * size;
                pb[i * 8 + j]->Top = y0 + i * size;
                pb[i * 8 + j]->Width = size;
                pb[i * 8 + j]->Height = size;
                pb[i * 8 + j]->SizeMode = PictureBoxSizeMode::StretchImage;
                pb[i * 8 + j]->TabStop = false;

                if ((i + j) % 2 == 0)
                    pb[i * 8 + j]->BackColor = System::Drawing::Color::LightGray;
                else
                    pb[i * 8 + j]->BackColor = System::Drawing::Color::DarkGray;

                pb[i * 8 + j]->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
                pb[i * 8 + j]->Tag = i * 8 + j;
                this->Controls->Add(pb[i * 8 + j]);
            }
        }


        // Отображаем шашки на доске
        updateBoard();
        selected = false;
        selectedX = -1;
        selectedY = -1;
        updateStatus();

        // Черные ходят первыми. Если человек выбрал белые, то ИИ ходит первым (за черных)
        if (isWhiteHuman && gameBoard->currentColor == black) {
            this->Enabled = false;
            Application::DoEvents();
            System::Threading::Thread::Sleep(500);

            moveInfo aiMove;
            getBestMove(*gameBoard, aiMove, black, aiDifficulty);
            makeMove(*gameBoard, aiMove);
            updateBoard();
            updateStatus();

            // Продолжаем рубку если есть обязательная рубка
            while (!endGame(*gameBoard) && gameBoard->currentColor == black && gameBoard->mustCapt) {
                System::Threading::Thread::Sleep(300);

                moveInfo aiContinueMove;
                getBestMove(*gameBoard, aiContinueMove, black, aiDifficulty);
                makeMove(*gameBoard, aiContinueMove);
                updateBoard();
                updateStatus();
            }

            this->Enabled = true;
        }

        // ГАРАНТИРУЕМ, что форма включена всегда
        this->Enabled = true;
    }

    void updateBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int idx = i * 8 + j;
                piece p = gameBoard->place[i][j];

                if (p.color == colorEmpty || p.type == typeEmpty) {
                    pb[idx]->Image = nullptr;
                }
                else {
                    Bitmap^ img = nullptr;

                    if (p.color == black) {
                        if (p.type == casual)
                            img = blackCasualBmp;
                        else if (p.type == queen)
                            img = blackQueenBmp;
                    }
                    else if (p.color == white) {
                        if (p.type == casual)
                            img = whiteCasualBmp;
                        else if (p.type == queen)
                            img = whiteQueenBmp;
                    }

                    if (img != nullptr)
                        pb[idx]->Image = gcnew Bitmap(img);
                    else
                        pb[idx]->Image = nullptr;
                }
            }
        }
    }

    void updateStatus() {
        System::String^ status = "";
        status = System::String::Format(L"Черные: {0}  |  Белые: {1}  | Уровень: {2}", gameBoard->black, gameBoard->white, aiDifficulty);

        if (endGame(*gameBoard)) {
            if (gameBoard->black == 0) {
                status = L"БЕЛЫЕ ПОБЕДИЛИ! Нажмите 'Выход в меню'";
            }
            else if (gameBoard->white == 0) {
                status = L"ЧЕРНЫЕ ПОБЕДИЛИ! Нажмите 'Выход в меню'";
            }
            this->statusLabel->Text = status;
            this->menuButton->Visible = true;
        }
        else {
            if (gameBoard->currentColor == black)
                status += L" | Ход: ЧЕРНЫЕ";
            else
                status += L" | Ход: БЕЛЫЕ";
            this->statusLabel->Text = status;
        }
    }

    void showValidMoves(int fromX, int fromY) {
        // Сохраняем оригинальные цвета допустимых ходов
        validMoveIndices = gcnew array<int>(64);
        originalColors = gcnew array<System::Drawing::Color>(64);
        validMoveCount = 0;

        // Проверяем все возможные ходы с этой позиции
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                moveInfo testMove;
                testMove.from = {fromX, fromY};
                testMove.to = {i, j};

                if (isValidMove(*gameBoard, testMove)) {
                    int idx = i * 8 + j;
                    validMoveIndices[validMoveCount] = idx;
                    originalColors[validMoveCount] = pb[idx]->BackColor;

                    // Выделяем зеленым допустимые ходы
                    pb[idx]->BackColor = System::Drawing::Color::LimeGreen;
                    validMoveCount++;
                }
            }
        }
    }

    void clearValidMoves() {
        // Восстанавливаем оригинальные цвета для всех ячеек
        if (validMoveIndices != nullptr && originalColors != nullptr) {
            for (int i = 0; i < validMoveCount; i++) {
                int idx = validMoveIndices[i];
                if (idx >= 0 && idx < 64) {
                    // Если это не исходная выбранная клетка, восстанавливаем цвет
                    if (!(selected && idx == selectedX * 8 + selectedY)) {
                        pb[idx]->BackColor = originalColors[i];
                    }
                }
            }
        }
        validMoveIndices = nullptr;
        originalColors = nullptr;
        validMoveCount = 0;
    }

    System::Void pictureBox_Click(System::Object^ sender, System::EventArgs^ e) {
        if (endGame(*gameBoard))
            return;
        System::Windows::Forms::PictureBox^ pictureBox = (PictureBox^)sender;
        int cellIdx = (int)pictureBox->Tag;
        int row = cellIdx / 8;
        int col = cellIdx % 8;

        // Проверяем, что это ход человеческого игрока
        bool isHumanTurn = (isWhiteHuman && gameBoard->currentColor == white) || 
                            (!isWhiteHuman && gameBoard->currentColor == black);

        if (!isHumanTurn)
            return;

        if (!selected) {
            // Попытка выбрать шашку
            piece selectedPiece = gameBoard->place[row][col];
            color humanColor = isWhiteHuman ? white : black;

            if (selectedPiece.color == humanColor && selectedPiece.type != typeEmpty) {
                if (gameBoard->mustKiller.x == -1 || (gameBoard->mustKiller.x == row && gameBoard->mustKiller.y == col)) {
                    selected = true;
                    selectedX = row;
                    selectedY = col;
                    pictureBox->BackColor = System::Drawing::Color::Cyan;

                    // Показываем допустимые ходы
                    showValidMoves(row, col);
                }
            }
        }
        else {
            // Попытка сделать ход
            if (selectedX == row && selectedY == col) {
                // Отмена выбора
                clearValidMoves();
                int idx = selectedX * 8 + selectedY;
                if ((selectedX + selectedY) % 2 == 0)
                    pb[idx]->BackColor = System::Drawing::Color::LightGray;
                else
                    pb[idx]->BackColor = System::Drawing::Color::DarkGray;
                selected = false;
                selectedX = -1;
                selectedY = -1;
            }
            else {
                // Попытка хода
                moveInfo move;
                move.from = {selectedX, selectedY};
                move.to = {row, col};

                int rv = isValidMove(*gameBoard, move);
                move.result = rv;
                if (rv != 0) {
                    makeMove(*gameBoard, move);
                    clearValidMoves();

                    // Восстанавливаем цвет старой клетки
                    int idx = selectedX * 8 + selectedY;
                    if ((selectedX + selectedY) % 2 == 0)
                        pb[idx]->BackColor = System::Drawing::Color::LightGray;
                    else
                        pb[idx]->BackColor = System::Drawing::Color::DarkGray;

                    selected = false;
                    selectedX = -1;
                    selectedY = -1;
                    updateBoard();
                    updateStatus();

                    // Ход ИИ (противоположный цвет)
                    color aiColor = isWhiteHuman ? black : white;
                    if (!endGame(*gameBoard) && gameBoard->currentColor == aiColor) {
                        // Ход ИИ с циклом для обязательных рубок
                        this->Enabled = false;
                        Application::DoEvents();
                        System::Threading::Thread::Sleep(500);

                        moveInfo aiMove;
                        getBestMove(*gameBoard, aiMove, aiColor, aiDifficulty);
                        makeMove(*gameBoard, aiMove);
                        updateBoard();
                        updateStatus();

                        // Продолжаем рубку если есть обязательная рубка
                        while (!endGame(*gameBoard) && gameBoard->currentColor == aiColor && gameBoard->mustCapt) {
                            System::Threading::Thread::Sleep(300);

                            moveInfo aiContinueMove;
                            getBestMove(*gameBoard, aiContinueMove, aiColor, aiDifficulty);
                            makeMove(*gameBoard, aiContinueMove);
                            updateBoard();
                            updateStatus();
                        }

                        this->Enabled = true;
                    }
                }
                else {
                    // Ход невалиден - пытаемся выбрать другую шашку
                    clearValidMoves();
                    // Восстанавливаем цвет предыдущей выбранной клетки (используем правильный индекс)
                    int prevIdx = selectedX * 8 + selectedY;
                    if (prevIdx >= 0 && prevIdx < 64) {
                        if ((selectedX + selectedY) % 2 == 0)
                            pb[prevIdx]->BackColor = System::Drawing::Color::LightGray;
                        else
                            pb[prevIdx]->BackColor = System::Drawing::Color::DarkGray;
                    }

                    // Выбираем новую шашку если там есть своя
                    color humanColor = isWhiteHuman ? white : black;
                    if (gameBoard->place[row][col].color == humanColor && gameBoard->place[row][col].type != typeEmpty) {
                        if (gameBoard->mustKiller.x == -1 || (gameBoard->mustKiller.x == row && gameBoard->mustKiller.y == col)) {
                            selected = true;
                            selectedX = row;
                            selectedY = col;
                            pictureBox->BackColor = System::Drawing::Color::Cyan;
                            showValidMoves(row, col);
                        }
                    }
                    else {
                        selected = false;
                        selectedX = -1;
                        selectedY = -1;
                    }
                }
            }
        }
    }

    System::Void saveButton_Click(System::Object^ sender, System::EventArgs^ e) {
        if (gameBoard != nullptr) {
            const char* filename = "game_save.bin";
            if (saveGame(filename, *gameBoard, aiDifficulty, isWhiteHuman)) {
                MessageBox::Show(L"Игра сохранена в файл 'game_save.bin'", L"Сохранение", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else {
                MessageBox::Show(L"Ошибка при сохранении игры", L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    System::Void menuLoad_Click(System::Object^ sender, System::EventArgs^ e) {
        loadGameFromFile();
    }

    System::Void menuButton_Click(System::Object^ sender, System::EventArgs^ e) {
        returnToMainMenu();
    }

    void returnToMainMenu() {
        // Скрываем кнопки игры
        this->saveButton->Visible = false;
        this->menuButton->Visible = false;

        // Очищаем доску
        if (pb != nullptr) {
            for (int i = 0; i < 64; i++) {
                if (pb[i] != nullptr) {
                    this->Controls->Remove(pb[i]);
                    delete pb[i];
                }
            }
            delete pb;
            pb = nullptr;
        }

        // Удаляем доску из памяти
        if (gameBoard != nullptr) {
            delete gameBoard;
            gameBoard = nullptr;
        }

        // Сбрасываем переменные
        selected = false;
        selectedX = -1;
        selectedY = -1;
        aiDifficulty = 0;
        isWhiteHuman = true;

        // Показываем стартовый экран
        this->button1->Visible = true;
        this->loadInitialButton->Visible = true;
        this->statusLabel->Text = L"Нажмите 'Новая игра' для начала";
    }

    void loadGameFromFile() {
        const char* filename = "game_save.bin";
        desk* tempBoard = new desk();
        int loadedAiDifficulty = 1;  // По умолчанию
        bool loadedIsWhiteHuman = true;  // По умолчанию

        bool loadSuccess = loadGame(filename, *tempBoard, loadedAiDifficulty, loadedIsWhiteHuman);

        // Если загрузка не удалась, инициализируем начальную доску
        if (!loadSuccess) {
            newGame(*tempBoard);
            tempBoard->currentColor = black;
            // Значения по умолчанию уже установлены выше
        }

        // Удаляем старую доску и используем загруженную (или новую)
        if (gameBoard != nullptr)
            delete gameBoard;
        gameBoard = tempBoard;

        // Устанавливаем загруженные значения
        aiDifficulty = loadedAiDifficulty;
        isWhiteHuman = loadedIsWhiteHuman;

        // Сразу показываем доску, минуя диалоги
        setupLoadedGameBoard();
    }

    void continueLoadedGame() {
        // Показываем диалог выбора цвета
        this->easyButton->Visible = false;
        this->normalButton->Visible = false;
        this->hardButton->Visible = false;
        this->colorLabel->Visible = true;
        this->blackColorButton->Visible = true;
        this->whiteColorButton->Visible = true;
        this->statusLabel->Text = L"Выберите свой цвет";
    }

    void setupLoadedGameBoard() {
        // Скрываем стартовые элементы
        this->button1->Visible = false;
        this->easyButton->Visible = false;
        this->normalButton->Visible = false;
        this->hardButton->Visible = false;
        this->colorLabel->Visible = false;
        this->blackColorButton->Visible = false;
        this->whiteColorButton->Visible = false;
        this->loadInitialButton->Visible = false;
        this->saveButton->Visible = true;
        this->menuButton->Visible = true;

        // Очищаем старую визуальную доску
        if (pb != nullptr) {
            for (int i = 0; i < 64; i++) {
                if (pb[i] != nullptr) {
                    this->Controls->Remove(pb[i]);
                    delete pb[i];
                }
            }
        }

        // Загружаем изображения
        if (blackCasualBmp == nullptr) blackCasualBmp = gcnew Bitmap("..//черная шашка.png");
        if (whiteCasualBmp == nullptr) whiteCasualBmp = gcnew Bitmap("..//белая шашка.png");
        if (blackQueenBmp == nullptr) blackQueenBmp = gcnew Bitmap("..//черная дамка.png");
        if (whiteQueenBmp == nullptr) whiteQueenBmp = gcnew Bitmap("..//белая дамка.png");

        // Пересоздаем визуальную доску
        pb = gcnew array<PictureBox^>(64);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                pb[i * 8 + j] = gcnew PictureBox();
                pb[i * 8 + j]->Left = x0 + j * size;
                pb[i * 8 + j]->Top = y0 + i * size;
                pb[i * 8 + j]->Width = size;
                pb[i * 8 + j]->Height = size;
                pb[i * 8 + j]->SizeMode = PictureBoxSizeMode::StretchImage;
                pb[i * 8 + j]->TabStop = false;

                if ((i + j) % 2 == 0)
                    pb[i * 8 + j]->BackColor = System::Drawing::Color::LightGray;
                else
                    pb[i * 8 + j]->BackColor = System::Drawing::Color::DarkGray;

                pb[i * 8 + j]->Click += gcnew System::EventHandler(this, &MyForm::pictureBox_Click);
                pb[i * 8 + j]->Tag = i * 8 + j;
                this->Controls->Add(pb[i * 8 + j]);
            }
        }

        updateBoard();
        selected = false;
        selectedX = -1;
        selectedY = -1;
        updateStatus();

        // Если ход ИИ, делаем его ход
        color aiColor = isWhiteHuman ? black : white;
        if (!endGame(*gameBoard) && gameBoard->currentColor == aiColor) {
            this->Enabled = false;
            Application::DoEvents();
            System::Threading::Thread::Sleep(500);

            moveInfo aiMove;
            getBestMove(*gameBoard, aiMove, aiColor, aiDifficulty);
            makeMove(*gameBoard, aiMove);
            updateBoard();
            updateStatus();

            // Продолжаем рубку если есть обязательная рубка
            while (!endGame(*gameBoard) && gameBoard->currentColor == aiColor && gameBoard->mustCapt) {
                System::Threading::Thread::Sleep(300);

                moveInfo aiContinueMove;
                getBestMove(*gameBoard, aiContinueMove, aiColor, aiDifficulty);
                makeMove(*gameBoard, aiContinueMove);
                updateBoard();
                updateStatus();
            }

            this->Enabled = true;
        }
        else {
            // Форма должна быть включена если это ход человека
            this->Enabled = true;
        }
    }

    };
}
