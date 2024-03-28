class TicTacToe():
    def __init__(self, initial='X'):
        self.start = initial
        self.board = [' ' for _ in range(9)]
        self.current_winner = None
    
    # print a big board with numbers on the right for reference
    def print_board(self):
        for i in range(3):
            print(' | '.join(self.board[i*3:i*3+3]) + '   ' + ' | '.join(str(x) for x in range(i*3+1, i*3+4)))
            if i < 2:
                print('-'*10)
    
    def board_full(self):
        return ' ' not in self.board
    
    def check_winner(self):
        b = self.board
        # horizontal
        for i in range(3):
            if b[i*3] == b[i*3+1] == b[i*3+2] and b[i*3] != ' ':
                return b[i*3]
        # vertical
        for i in range(3):
            if b[i] == b[i+3] == b[i+6] and b[i] != ' ':
                return b[i]
        # diagonal
        if ( b[0] == b[4] == b[8] or b[6] == b[4] == b[2] ) and b[4] != ' ':
            return b[4]
    
    def get_move(self, player): # get move from player

        if player == 'X': # human
            while True: # loop until valid input
                try:
                    play_num = int(input("Enter your move (1-9): "))
                    if play_num in range(1, 10) and self.board[play_num-1] == ' ':
                        return play_num
                    else:
                        raise ValueError
                except ValueError:
                    print("Invalid move.")

        else: # bot
            return self.bot_minimax()
    
    def bot_random(self): # random bot
        import random
        while True:
            play_num = random.randint(1, 9)
            if self.board[play_num-1] == ' ':
                return play_num
    

    def minimax(self, board, depth, is_maximizing): # minimax algorithm
        scores = {'X': -1, 'O': 1, 'tie': 0} # scores for each player
        winner = self.check_winner() # check if game is over
        if winner:
            return scores[winner]
        if self.board_full():
            return scores['tie']

        if is_maximizing: # bot's turn
            best_score = float('-inf')
            for i in range(9):
                if board[i] == ' ':
                    board[i] = 'O'
                    if self.check_winner() == 'O':
                        board[i] = ' '
                        return scores['O']
                    score = self.minimax(board, depth + 1, False)
                    board[i] = ' '
                    best_score = max(score, best_score)
            return best_score
        
        else: # player's turn
            best_score = float('inf')
            for i in range(9):
                if board[i] == ' ':
                    board[i] = 'X'
                    if self.check_winner() == 'X':
                        board[i] = ' '
                        return scores['X']
                    score = self.minimax(board, depth + 1, True)
                    board[i] = ' '
                    best_score = min(score, best_score)
            return best_score
    
    def bot_minimax(self): # minimax bot
        best_score = float('-inf')
        best_move = None
        for i in range(9): # loop through all possible moves
            if self.board[i] == ' ': # check if move is valid
                self.board[i] = 'O' # make move
                if self.check_winner() == 'O':  # Check for immediate win
                    self.board[i] = ' '
                    return i + 1
                score = self.minimax(self.board, 0, False) # get score for move
                self.board[i] = ' ' # undo move
                if score > best_score: # update best move
                    best_score = score
                    best_move = i + 1
        return best_move

    def play_game(self): # main loop
        player = 'X' if self.start == 'X' else 'O'
        while not self.board_full():
            self.print_board()
            print("player",player)
            play_num = self.get_move(player)
            self.board[play_num-1] = player
            player = 'O' if player == 'X' else 'X'
            winner = self.check_winner()
            if winner:
                break
        self.print_board()
        if winner:
            print(winner, "wins!")
        else:
            print("It's a draw!")

    
def main():
    game = TicTacToe(initial='O') # initial player
    game.play_game()

if __name__ == '__main__':
    main()