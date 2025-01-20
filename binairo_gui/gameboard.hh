// gameboard.hh - COMP.CS.110 - 12.6 (P) Binairon Paluu
// Tekijä: Patrik Reitkivi
// Op.num: 151106280
//
// Esittelee ohjelman pelimoottorin, GameBoard-luokan.
// Ohjelma ajaa Binairoa tämän luokan olion avulla.
// Luokka alustetaan pääasiallisesti SetCommand-rakenteen
// avulla, mikä määrittelee pelilaudan alkuasetelman.

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>
#include <string>

// Pelilaudan alkioiden tyyppi.
// Type of the elements in the gameboard.
enum Element_type {ZERO, ONE, EMPTY};

// Pelilaudan asetustilan tyyppi. Pelilauta alustetaan eri tavalla
// riippuen siitä, mikä Set_mode on valittuna.
enum Set_mode {NONE, RANDOM, INPUT, MANUAL};

// Rakenne määräämään pelilaudan alkuasetelman.
// Kun lauta halutaan alustaa tai asettaa takaisin alkuasetelmaan,
// käytetään SetCommand-tietoalkiota.
struct SetCommand
{
    Set_mode set_mode = INPUT;
    unsigned int seed = 0;                                          // Oletusarvoinen asetuskomento
    std::string input = "\" 010   1  1  010   1  1  0  0  101  \"";     // määrää lautaan B-kirjaimen
    unsigned int board_size = 6;
};

// Vakio todennäköisyysjakauman ylärajaa varten.
// Nollilla ja ykkösillä on sama todennäköisyys, vaikkapa x, ja tyhjien
// todennäköisyyden voidaan arvioida olevan 6x, jolloin jakaumassa
// on yhteensä kahdeksan pistettä (lukua), joten sopiva väli on esim. [0..7].
//
// Constant for the upper bound of probability distribution.
// Zeros and ones have the same probability, say x, and the estimated
// probability of empties is 6x, whereupon their sum is 8x, and thus,
// the interval must have eigth points, as [0..7].
const int DISTR_UPPER_BOUND = 7;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa.
// Width of the left-most column, needed in printing the gameboard.
const unsigned int LEFT_COLUMN_WIDTH = 5;

class GameBoard
{
public:
    // Rakentaja.
    // Constructor. Calls init() to fill the board with EMPTYs.
    GameBoard();

    /**
     * @brief GameBoard
     * Tässä ohjelmassa pääasiallinen rakentaja.
     * @param cmd
     * Määrää pelilaudan koon ja alkuasetelman.
     */
    GameBoard(SetCommand cmd);

    /**
     * @brief set_board
     * Asettaa laudan set_command_-jäsenmuuttujan perusteella.
     * @return onko lauta sääntöjen mukainen?
     */
    bool set_board();

    /**
     * @brief clear_board
     * Asettaa laudan joka solun tyhjäksi.
     */
    void clear_board();

    /**
     * @brief lock_placement
     * Lukitsee käyttäjän itse asettaman laudan alkuasetelmaksi.
     */
    void lock_placement();

    // Fills the gameboard randomly with three symbols (ZERO, ONE, EMPTY)
    // such that every fourth element is non-empty.
    // Checks the given seed and returns true if it is not one of BAD_SEEDs,
    // otherwise returns false.
    bool fill_randomly(unsigned int seed);

    // Fills the gameboard from the given input.
    // Checks if the input size is correct and if it has only legal symbols.
    // If this holds true, i.e. if filling is possible, returns true,
    // otherwise returns false.
    bool fill_from_input(const std::string& input);

    // Checks if the gameboard has at most two adjacent ZEROs and at most two
    // adjacent ONEs in each row and column.
    // If this is the case, returns true, otherwise returns false.
    // Calls the methods has_permissible_in_rows and has_permissible_in_columns
    // with both ZERO and ONE as a parameter.
    bool ok_adjacent_symbols() const;

    // Checks if each row and column of the gameboard has at most
    // NUMBER_OF_SYMBOLS symbols.
    // If this is the case, returns true, otherwise returns false.
    bool ok_amount_of_symbols() const;

    /**
     * @brief ok_unique_rows_and_columns
     * Tarkistaa, noudattaako lauta Binairon kolmatta sääntöä.
     * @return Jokainen rivi ja sarake on ainutlaatuinen.
     */
    bool ok_unique_rows_and_columns() const;

    // Adds the given symbol in the given coordinates of the gameboard.
    // However, this is done only if both has_permissible_adjacent_symbols
    // and has_permissible_amount_of_symbols return true.
    // Returns true, if adding was done, otherwise returns false.
    bool add_symbol(unsigned int x, unsigned int y, char symbol_char);

    // Returns true, if the game is over, i.e. if there are no EMPTYs in the
    // gameboard.
    bool is_game_over() const;

    // Tulostaa pelilaudan.
    // Prints the gameboard.
    void print() const;

    /**
     * @brief get_size
     * @return laudan koko, size_-jäsenmuuttujan arvo
     */
    unsigned int get_size() const;

    /**
     * @brief seems_valid
     * tarkistaa, että alkuasetelma ei valmiiksi riko jotain Binairon sääntöä.
     * @return Vaikuttaako lauta olevan ratkaistavissa?
     */
    bool seems_valid() const;

    /**
     * @brief get_cellptr
     * Noutaa osoittimen laudan ruutuun (x,y). BinairoCell-
     * widgetillä on vastaava jäsenmuuttuja.
     * @param x - koordinaatti
     * @param y - koordinaatti
     * @return Element_type*, laudan ruudusta (x,y).
     */
    Element_type* get_cellptr(unsigned int x, unsigned int y);

private:
    // Inits the gameboard, i.e. fills it with EMPTYs.
    void init();

    // Tulostaa annetun pituisen rivin annettua merkkiä.
    // Prints a line with the given length and the given character.
    void print_line(unsigned int length, char fill_character) const;

    // Keskeneräinen luolamiesratkaisu ratkeavan laudan generoimiseksi. Jätetty tähän
    // kummittelemaan, koska sillä on tunnearvoa.
    // bool generate_solution(bool randomly = false);
    // bool recursive_solve(std::vector<std::pair<unsigned int, unsigned int>> indexes);

    // Goes through all rows in the gameboard and checks if there are
    // at most two adjacent occurrences of the given elem in each row.
    // If this is the case, returns true, otherwise returns false.
    bool ok_adjacent_syms_in_rows(Element_type elem) const;

    // Goes through all columns in the gameboard and checks if there are
    // at most two adjacent occurrences of the given elem in each column.
    // If this is the case, returns true, otherwise returns false.
    bool ok_adjacent_syms_in_columns(Element_type elem) const;

    /**
     * @brief ok_different_rows
     * Vertaa jokaista riviä jokaiseen toiseen riviin.
     * @return ovatko rivit ainutlaatuisia?
     */
    bool ok_different_rows() const;
    bool ok_different_cols() const;

    /**
     * @brief get_column
     * muodostaa vektorin laudan j-sarakkeesta, ts.
     * laudan joka rivin j:nnestä elementistä.
     * @param j
     * halutun sarakkeen numero
     * @return vector<element_type>, samanlainen kuin laudan rivi on.
     */
    std::vector<Element_type> get_column(unsigned int j) const;

    // Gameboard
    std::vector<std::vector<Element_type>> board_;

    // Numerot pelilaudan koon määrittelemiseen.
    // Ints for the size of the gameboard.
    unsigned int size_ = 4;
    unsigned int number_of_symbols_ = 2;

    SetCommand setCMD_ = {RANDOM, 0, "", 4};
    // Totuusarvo kertoo, onko asetettu lauta sääntöjen mukainen. Pelilaudan voi
    // siis alustaa virheellisenä, mutta se ei "seemaa validilta".
    bool seems_valid_ = true;

    // Ratkaisemattoman pelilaudan tuottavat siemenluvut väliltä [1..50].
    // A list of seed values from [1..50] that produce non-solvable gameboard.
    const std::vector<unsigned int> BAD_SEEDS = { 2, 8, 12, 13, 16, 20, 21, 23,
                                                 26, 29, 31, 32, 34, 41, 42,
                                                 43, 44, 46 };
};

#endif // GAMEBOARD_HH
