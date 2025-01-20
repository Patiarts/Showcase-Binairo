// gameboard.cpp - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// Määrittelee GameBoard-luokan operaatiot.
// Laudan asetus ja oikeellisuuden tarkistus ovat kriittisiä.

#include "gameboard.hh"
#include <iostream>
#include <random>
#include <algorithm>

GameBoard::GameBoard()
{
    init();
}

GameBoard::GameBoard(SetCommand cmd)
    : size_(cmd.board_size)
    , number_of_symbols_(size_/2)
    , setCMD_(cmd)
{
    init();
    seems_valid_ = set_board();
}

bool GameBoard::set_board()
{
    // Kutsutaan set_moden perusteella sopivaa asetusmetodia. MANUAL haluaa
    // kuitenkin vain tyhjän laudan.
    clear_board();
    switch(setCMD_.set_mode){
    case RANDOM: return fill_randomly(setCMD_.seed); break;
    case INPUT: return fill_from_input(setCMD_.input); break;
    case MANUAL: return true; break;  // Lauta on jo tyhjä.
    default: return fill_randomly(setCMD_.seed); break;
    }
}

void GameBoard::clear_board()
{
    // Laudan joka solu tyhjäksi.
    for(unsigned int i = 0 ; i < size_ ; i++){
        for(unsigned int j = 0 ; j < size_ ; j++){

            board_.at(i).at(j) = EMPTY;
        }
    }
}

void GameBoard::lock_placement()
{
    // MANUAL-moodissa asetettu lauta lukitaan rakentamalla laudan nykyisen tilan
    // perusteella syöterivi, ja määräämällä se laudan alkuasetelmaksi.
    std::string str = "\"";

    for(unsigned int i = 0 ; i < size_ ; i++){
        for(unsigned int j = 0 ; j < size_ ; j++){

            switch(board_.at(i).at(j)){
            case EMPTY: str += " "; break;
            case ZERO: str += "0"; break;
            case ONE: str += "1"; break;
            }
        }
    }
    str += "\n";
    setCMD_ = SetCommand{INPUT, 0, str};

    // Jos käyttäjän asettaman laudan tekstiesitys vastaa virheellistä lautaa,
    // lauta ei ainakaan "seemaa validilta", vaikuta sopivalta.
    // Tämä käy false-palautusarvosta.
    seems_valid_ = ok_adjacent_symbols() and
                   ok_amount_of_symbols() and
                   ok_unique_rows_and_columns();
}

bool GameBoard::fill_randomly(unsigned int seed)
{
    // Checking the validity of the given seed
    for(unsigned int bad_seed : BAD_SEEDS)
    {
        if(seed == bad_seed)
        {
            std::cout << "Bad seed" << std::endl;
            return false;
        }
    }

    // Constructing a string with random symbols
    std::default_random_engine eng(seed);
    std::uniform_int_distribution<unsigned int> distr(0, DISTR_UPPER_BOUND);
    std::string input = "";

    for(unsigned int i = 0; i < size_ * size_; ++i)
    {
        switch(distr(eng))
        {
        case 0: input += '0'; break;
        case 1: input += '1'; break;
        default: input += ' '; break;
        }
    }

    // Calling fill_from_input with the constructed string (enclosed with quote
    // marks), whereupon the return value of fill_from_input will be true
    return fill_from_input('"' + input + '"');
}

bool GameBoard::fill_from_input(const std::string &input)
{
    // Checking the size (assuming that input is enclosed with quote marks)
    if(input.size() != size_ * size_ + 2)
    {
        std::cout << "Wrong size of input" << std::endl;
        return false;
    }

    // Removing quote marks
    std::string actual_input = input.substr(1, size_ * size_);

    // Checking the content and moving each element on the gameboard
    for(unsigned int i = 0; i < size_ * size_; ++i)
    {
        Element_type current_element = EMPTY;
        switch(actual_input.at(i))
        {
        case '0': current_element = ZERO; break;
        case '1': current_element = ONE; break;
        case ' ': current_element = EMPTY; break;
        default: std::cout << "Wrong character" << std::endl; return false;
        }

        board_.at(i / size_).at(i % size_ ) = current_element;
    }
    if(ok_adjacent_symbols() and ok_amount_of_symbols()
        and ok_unique_rows_and_columns())
    {
        return true;
    }
    else
    {
        std::cout << "Bad input" << std::endl;
        return false;
    }
}

bool GameBoard::ok_adjacent_symbols() const
{
    return ok_adjacent_syms_in_rows(ZERO) and
           ok_adjacent_syms_in_rows(ONE) and
           ok_adjacent_syms_in_columns(ZERO) and
           ok_adjacent_syms_in_columns(ONE);
}

bool GameBoard::ok_amount_of_symbols() const
{
    unsigned int zeros_in_row = 0;
    unsigned int ones_in_row = 0;
    unsigned int zeros_in_column = 0;
    unsigned int ones_in_column = 0;

    for(unsigned int i = 0; i < size_; ++i)
    {
        for(unsigned int j = 0; j < size_; ++j)
        {
            if(board_.at(i).at(j) == ZERO)
            {
                ++zeros_in_row;
            }
            else if(board_.at(i).at(j) == ONE)
            {
                ++ones_in_row;
            }
            if(board_.at(j).at(i) == ZERO)
            {
                ++zeros_in_column;
            }
            else if(board_.at(j).at(i) == ONE)
            {
                ++ones_in_column;
            }
        }
        if(zeros_in_row > number_of_symbols_ or
            ones_in_row > number_of_symbols_ or
            zeros_in_column > number_of_symbols_ or
            ones_in_column > number_of_symbols_)
        {
            return false;
        }
        zeros_in_row = ones_in_row = zeros_in_column = ones_in_column = 0;
    }
    return true;
}

bool GameBoard::ok_unique_rows_and_columns() const
{
    return ok_different_rows() and ok_different_cols();
}

bool GameBoard::add_symbol(unsigned int x, unsigned int y, char symbol_char)
{
    if(board_.at(y).at(x) != EMPTY)
    {
        //std::cout << "Not empty: ";
        return false;
    }

    Element_type elem = EMPTY;
    switch(symbol_char)
    {
    case '0': elem = ZERO; break;
    case '1': elem = ONE; break;
    default: return false; // This should never happen, checked in main.cpp
    }

    // Adding the symbol and checking if everything is still fine
    board_.at(y).at(x) = elem;
    if(ok_adjacent_symbols() and
        ok_amount_of_symbols())
    {
        return true;
    }
    // If all was not fine after adding, making the index empty again
    else
    {
        board_.at(y).at(x) = EMPTY;
        return false;
    }
}

bool GameBoard::is_game_over() const
{
    // Olisiko tämä pitänyt nimetä uudelleen?
    for(unsigned int i = 0; i < board_.size(); ++i)
    {
        for(unsigned int j = 0; j < board_.at(i).size(); ++j)
        {
            if(board_.at(i).at(j) == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

void GameBoard::print() const
{
    // Tulostetaan yläreuna
    // Printing upper border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * size_ + 1, '=');

    // Tulostetaan otsikkorivi
    // Printing title row
    std::cout << "|   | ";
    for(unsigned int i = 0; i < size_; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Tulostetaan viiva otsikkorivin alle
    // Printing line after the title row
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * size_ + 1, '-');

    // Tulostetaan pelilaudan varsinainen sisältö
    // Printing the actual content of the gameboard
    for(unsigned int i = 0; i < size_; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < size_; ++j)
        {
            switch(board_.at(i).at(j))
            {
            case ZERO: std::cout << "0 "; break;
            case ONE: std::cout << "1 "; break;
            case EMPTY: std::cout << "  "; break;
            }
        }
        std::cout << "|" << std::endl;
    }

    // Tulostetaan alareuna
    // Printing lower border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * size_ + 1, '=');
}

unsigned int GameBoard::get_size() const
{
    return size_;
}

bool GameBoard::seems_valid() const
{
    return seems_valid_;
}

Element_type* GameBoard::get_cellptr(unsigned int x, unsigned int y)
{
    return &board_.at(x).at(y);
}

void GameBoard::init()
{
    std::vector<Element_type> row(size_, EMPTY);
    for(unsigned int i = 0; i < size_; ++i)
    {
        board_.push_back(row);
    }
}

void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}

/*
Ratkaisualgoritmin kummitus. Jo pelkästään 10x10-laudan generoimiseksi
rekursiivista funktiota kutsuttiin yli 4 miljoonaa kertaa, ennen kuin
luovutin sen suhteen. Toimii kuitenkin 6x6-laudoille alle kymmenessä sekunnissa.
Saa kokeilla ":D"!

bool GameBoard::generate_solution(bool randomly)
{

    std::vector<std::pair<unsigned int, unsigned int>> empty_indexes = {};

    for(unsigned int i = 0 ; i < size_ ; i++){
        for(unsigned int j = 0 ; j < size_ ; j++){

            if(board_.at(i).at(j) == EMPTY){
                std::pair<unsigned int, unsigned int> ind ={i,j};
                empty_indexes.push_back(ind);
            }
        }
    }

    if(randomly){
        // nothing yet
    }


    return recursive_solve(empty_indexes);
}

bool GameBoard::recursive_solve(std::vector<std::pair<unsigned int, unsigned int>> indexes)
{
    if(indexes.empty()){
        return ok_unique_rows_and_columns();
    }

    std::pair<unsigned int, unsigned int> ind = indexes.back();
    indexes.pop_back();

    board_.at(ind.first).at(ind.second) = ZERO;
    bool valid = ok_adjacent_symbols() and ok_amount_of_symbols();

    if(not (valid and recursive_solve(indexes))){
        board_.at(ind.first).at(ind.second) = ONE;

        valid = ok_adjacent_symbols() and ok_amount_of_symbols();

        if(not (valid and recursive_solve(indexes))){
            board_.at(ind.first).at(ind.second) = EMPTY;
            indexes.push_back(ind);
            return false;
        }
    }
    return true;
}
*/

bool GameBoard::ok_adjacent_syms_in_rows(Element_type elem) const
{
    for(unsigned int i = 0; i < board_.size(); ++i)
    {
        for(unsigned int j = 0; j < board_.at(i).size() - 2; ++j)
        {
            if(board_.at(i).at(j) == elem and
                board_.at(i).at(j + 1) == elem and
                board_.at(i).at(j + 2) == elem)
            {
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::ok_adjacent_syms_in_columns(Element_type elem) const
{
    for(unsigned int i = 0; i < board_.size() - 2; ++i)
    {
        for(unsigned int j = 0; j < board_.at(i).size(); ++j)
        {
            if(board_.at(i).at(j) == elem and
                board_.at(i + 1).at(j) == elem and
                board_.at(i + 2).at(j) == elem)
            {
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::ok_different_rows() const
{
    for(unsigned int i = 0 ; i < size_-1 ; i++){

        std::vector<Element_type> comp_row = board_.at(i);

        if(std::count(comp_row.begin(), comp_row.end(), EMPTY)){
            continue;
        }

        for(unsigned int x = i+1 ; x < size_ ; x++){

            if(comp_row == board_.at(x)){
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::ok_different_cols() const
{
    for(unsigned int j = 0 ; j < size_-1 ; j++){

        std::vector<Element_type> comp_col = get_column(j);

        if(std::count(comp_col.begin(), comp_col.end(), EMPTY)){
            continue;
        }

        for(unsigned int x = j+1 ; x < size_ ; x++){

            if(comp_col == get_column(x)){
                return false;
            }
        }
    }
    return true;
}

std::vector<Element_type> GameBoard::get_column(unsigned int j) const
{
    std::vector<Element_type> column = {};

    for(unsigned int i = 0 ; i < size_ ; i++){
        column.push_back(board_.at(i).at(j));
    }

    return column;
}

