void load_board(const char *filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(char board[9][9]);
bool make_move(const char* position, char number, char board[9][9]);
bool same_case(int r, int c, char number, char board[9][9]);
bool save_board(const char* file, char board[9][9]);
bool solve_board(char board[9][9]);
void get_position(int& r, int& c, char board[9][9]);
/*bool make_move(const char position[], char digit, char board[9][9]);
bool check_subcase(int row, int column, char digit, char board[9][9]);
bool save_board(const char filename[], char board[9][9]);
bool solve_board(char board[9][9]);
void find_next_empty_cell(char board[9][9], int& r, int& c);
*/
