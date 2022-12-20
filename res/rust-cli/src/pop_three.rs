
//
// pop_three game library
//
// Anthony Mesa
//

use rand::Rng;
use std::{collections::BTreeSet};
use std::time::{SystemTime, UNIX_EPOCH};

//=============================================================================

// #[derive(Eq, PartialEq, Debug, Ord, PartialOrd, Copy, Clone)]
// enum CellState {
//     ONE,
//     TWO,
//     THREE,
//     FOUR,
//     FIVE
// }

// //=============================================================================

// // Cell object for Board grid
// #[derive(Eq, PartialEq, Debug, Ord, PartialOrd, Copy, Clone)]
// struct BoardCell {
//     value: CellState,
//     position: ( u8, u8 )
// }

// impl BoardCell {
//     fn new(x: u8, y: u8) -> BoardCell {
//         let mut rng = rand::thread_rng();
//         let random_value: u8 = rng.gen_range(0..5);
//         let random_state: CellState = match random_value {
//             0_u8 => CellState::ONE,
//             1_u8 => CellState::TWO,
//             2_u8 => CellState::THREE,
//             3_u8 => CellState::FOUR,
//             4_u8 => CellState::FIVE,
//             5_u8..=u8::MAX => todo!()
//         };

//         BoardCell { value: random_state, position: (x, y) }
//     }

//     pub fn get_color(&self) -> (u8, u8, u8) {
//         match self.value {
//             CellState::ONE => (255, 0, 0),
//             CellState::TWO => (0, 255, 0),
//             CellState::THREE => (0, 0, 255),
//             CellState::FOUR => (0, 255, 255),
//             CellState::FIVE => (255, 0, 255)
//         }
//     }

//     fn get_number(&self) -> u8 {
//         match self.value {
//             CellState::ONE => u8::from(1),
//             CellState::TWO => u8::from(2),
//             CellState::THREE => u8::from(3),
//             CellState::FOUR => u8::from(4),
//             CellState::FIVE => u8::from(5)
//         }
//     }
// }

//=============================================================================

// #[derive(Eq, PartialEq, Debug, Ord, PartialOrd, Clone)]
// struct Board {
//     width: u8,
//     height: u8,
//     grid: Vec<BoardCell>,
//     cell_islands: BTreeSet<BTreeSet<BoardCell>>
// }

// impl Board {
//     fn new(width: u8, height: u8) -> Board {

//         // Initialize board with empty island set
//         let mut new_board: Board = Board {
//             width,
//             height,
//             grid: Board::generate_grid(width, height),
//             cell_islands: BTreeSet::new()
//         };

//         // Update island set to reflect new grid
//         new_board.update_islands();

//         return new_board;
//     }

    // fn generate_grid(width: u8, height: u8) -> Vec<BoardCell> {
    //     let mut new_grid: Vec<BoardCell> = Vec::new();
    //     (0..height).into_iter().for_each(|y: u8| {
    //         (0..width).for_each(|x: u8| {
    //             new_grid.push(BoardCell::new(x, y));
    //         });
    //     });
    //     return new_grid;
    // }

    // fn get_cell(&self, x: u8, y: u8) -> &BoardCell {
    //     &self.grid[usize::from(u8::from(y)) * usize::from(self.width) + usize::from(u8::from(x))]
    // }

    // fn set_cell(&mut self, x: u8, y: u8, mut cell: BoardCell) {
    //     cell.position.0 = x;
    //     cell.position.1 = y;
    //     self.grid[usize::from(u8::from(y)) * usize::from(self.width) + usize::from(u8::from(x))] = cell;
    // }

    // fn update_islands(&mut self) {
    //     self.cell_islands = BTreeSet::new();

    //     for y in 0..self.height {
    //         for x in 0..self.width {
    //             let mut current_island: BTreeSet<BoardCell> = BTreeSet::new();
    //             self.generate_island(&mut current_island, x, y);

    //             if current_island.len() > 2 {
    //                 self.cell_islands.insert(current_island);
    //             }
    //         }
    //     }

    //     if self.cell_islands.len() == 0 {
    //         self.make_island();
    //         self.update_islands();
    //     }
    // }

    // pub fn get_island(&self, x: u8, y: u8) -> Option<&BTreeSet<BoardCell>> {
    //     for each_island in &self.cell_islands {
    //         for each_cell in each_island {
    //             if each_cell.position.0 == x && each_cell.position.1 == y {
    //                 return Some(each_island);
    //             }
    //         }
    //     }

    //     return None;
    // }

    // fn generate_island(&self, temp_island: &mut BTreeSet<BoardCell>, x: u8, y: u8) {
    //     // initialize the island with the selected cell
    //     temp_island.insert(*self.get_cell(x, y));

    //     self.expand_island(x, y, temp_island);
    // }

    // fn expand_island(&self, x: u8, y: u8, temp_island: &mut BTreeSet<BoardCell>) {

    //     // This should technically always be in range.
    //     let root_value = self.get_cell(x, y).value;

    //     self.search_right(x, y, root_value, temp_island);
    //     self.search_top(x, y, root_value, temp_island);
    //     self.search_left(x, y, root_value, temp_island);
    //     self.search_bottom(x, y, root_value, temp_island);
    // }

    // fn search_from_root(&self, x: u8, y: u8, root_value: CellState, temp_island: &mut BTreeSet<BoardCell>) {
    //     let test_value = self.get_cell(x, y).value;
        
    //     if root_value == test_value {
    //         if temp_island.insert(*self.get_cell(x, y)) {
    //             self.expand_island(x, y, temp_island);
    //         }
    //     }
    // }

    // fn search_right(&self, x: u8, y: u8, root_value: CellState, temp_island: &mut BTreeSet<BoardCell>) {
    //     if x + 1 < self.width {
    //         self.search_from_root(x + 1, y, root_value, temp_island)
    //     }
    // }

    // fn search_top(&self, x: u8, y: u8, root_value: CellState, temp_island: &mut BTreeSet<BoardCell>) {
    //     if y + 1 < self.height {
    //         self.search_from_root(x, y + 1, root_value, temp_island)
    //     }
    // }

    // fn search_left(&self, x: u8, y: u8, root_value: CellState, temp_island: &mut BTreeSet<BoardCell>) {
    //     if i16::from(x) - 1 >= 0 {
    //         self.search_from_root(x - 1, y, root_value, temp_island)
    //     }
    // }

    // fn search_bottom(&self, x: u8, y: u8, root_value: CellState, temp_island: &mut BTreeSet<BoardCell>) {
    //     if i16::from(y) - 1 >= 0 {
    //         self.search_from_root(x, y - 1, root_value, temp_island)
    //     }
    // }

    // fn get_left_island_bound(&self, island: &BTreeSet<BoardCell>) -> u8 {
    //     let mut min = self.width;

    //     for each_cell in island {
    //         let current_x = each_cell.position.0;
    //         if current_x < min {
    //             min = current_x;
    //         }
    //     }

    //     return min;
    // }

    // fn get_right_island_bound(&self, island: &BTreeSet<BoardCell>) -> u8 {
    //     let mut max = 0;

    //     for each_cell in island {
    //         let current_x = each_cell.position.0;
    //         if current_x > max {
    //             max = current_x;
    //         }
    //     }

    //     return max;
    // }

    // fn get_bottom_column_bound(&self, x: u8, island: &BTreeSet<BoardCell>) -> u8 {
    //     let mut min = self.height;

    //     for each_cell in island {
    //         if each_cell.position.0 == x{
    //             let current_y = each_cell.position.1;
    //             if current_y < min {
    //                 min = current_y;
    //             }
    //         }
    //     }

    //     return min;
    // }

    // fn get_top_column_bound(&self, x: u8, island: &BTreeSet<BoardCell>) -> u8 {
    //     let mut max = 0;

    //     for each_cell in island {
    //         if each_cell.position.0 == x{
    //             let current_y = each_cell.position.1;
    //             if current_y > max {
    //                 max = current_y;
    //             }
    //         }
    //     }

    //     return max;
    // }

    // // Generates a new island 
    // fn make_island(&mut self) {
    //     for y in (0..self.height).rev() {
    //         for x in 0..self.width {
    //             let current_cell = self.get_cell(x, y);
                
    //             if self.look_near(current_cell) {
    //                 self.set_cell(x + 1, y, BoardCell { value: current_cell.value, position: (x + 1, y) });
    //             }
    //             else if self.look_far(current_cell) {
    //                 self.set_cell(x + 2, y, BoardCell { value: current_cell.value, position: (x + 2, y) });
    //             }
    //         }
    //     }
    // }

    // // This function only looks horizontally. We could look vertically
    // // also but this is typically unnecessary.
    // fn look(&self, x: u8, y: u8, current_value: CellState) -> bool {
    //     if x < self.width {
    //         let forward_value = self.get_cell(x, y).value;

    //         if forward_value == current_value {
    //             return true;
    //         }
    //     }

    //     return false;
    // }

    // fn look_near(&self, current_cell: &BoardCell) -> bool{
    //     return self.look(
    //         current_cell.position.0 + 1, 
    //         current_cell.position.1, 
    //         current_cell.value
    //     );
    // }

    // fn look_far(&self, current_cell: &BoardCell) -> bool {
    //     return self.look(
    //         current_cell.position.0 + 2, 
    //         current_cell.position.1, 
    //         current_cell.value
    //     );
    // }

    // island_selected() originally took in scren coords and mapped them to 
    // the available grid dimensions. Given this is a library that doesn't
    // deal with the graphics side of things, it will only take the indices.
    fn island_selected(&self, x: u8, y: u8) -> bool {
        for each_island in &self.cell_islands {
            for each_cell in each_island {
                if each_cell.position.0 == x && each_cell.position.1 == y {
                    return true;
                }
            }
        }

        return false;
    }

    fn get_first_island(&self) -> Option<&BTreeSet<BoardCell>> {
        match self.cell_islands.iter().next() {
            Some(cell) => Some(cell),
            None => None
        }
    }
}

//=============================================================================

// #[derive(Eq, PartialEq, Debug, Copy, Clone)]
// struct Player {
//     score: u64
// }

// impl Player {
//     fn new() -> Player {
//         Player { score: 0 }
//     }
// }

//=============================================================================

pub struct Game {
    board: Board,
    player: Player,
    win_amount: u128,
    progress_time: u128,
    last_success_time: u16,
    helped: bool,
    time_update: u128,
    game_over: bool,
    player_win_value: u16
}

impl Game {
    pub fn new() -> Game {
        let new_board: Board = Board::new(8,7);

        Game {
            board: new_board,
            player: Player::new(),
            win_amount: 0,
            progress_time: 0,
            last_success_time: 0,
            helped: false,
            time_update: SystemTime::now()
                .duration_since(UNIX_EPOCH)
                .unwrap()
                .as_millis(),
            game_over: false,
            player_win_value: 1000
        }
    }

    fn increment_progress(&mut self, amount: u128) {
        if self.progress_time + amount > self.win_amount {
            self.progress_time = self.win_amount;
        } else {
            self.progress_time += amount;
        }
    }

    fn decrement_progress(&mut self, amount: u128) {
        if self.progress_time.checked_sub(amount) == None {
            self.progress_time = self.win_amount;
        } else {
            self.progress_time -= amount;
        }
    }

    pub fn with_dimensions(&self, x: u8, y: u8) -> Game {
        Game { 
            board: Board::new(x,y), 
            player: self.player, 
            win_amount: self.win_amount, 
            progress_time: self.progress_time, 
            last_success_time: self.last_success_time, 
            helped: self.helped, 
            time_update: SystemTime::now()
                .duration_since(UNIX_EPOCH)
                .unwrap()
                .as_millis(), 
            game_over: self.game_over, 
            player_win_value: self.player_win_value
        }
    }

    pub fn get_game_board(&self) -> Vec<(u8, u8, u8)> {
        let mut board_value_array = Vec::new();

        for each_cell in &self.board.grid {
            board_value_array.push(each_cell.get_color());
        }

        return board_value_array;
    }

    // Handle the selection of an element on the game's grid given the coordinates provided.
    pub fn select(&mut self, x: u8, y: u8) {
        
        // clone the board so that we can get immutable reads from it.
        let temp_board: Board = self.board.clone();

        // Given the selected coordinates, find the island that was selected, if any.
        let selection = temp_board.get_island(x, y);

        // If an island was selected, then we want to handle that. If an island wasn't selected,
        // move on like nothing happened.
        match selection {

            // An island was selected.
            Some(island) => {

                // Get the horizontal bounds of the island itself.
                let x_min = temp_board.get_left_island_bound(island);
                let x_max = temp_board.get_right_island_bound(island);

                // Iterate over the columns within the island.
                for current_x in x_min..=x_max {

                    // For each cell between the column's y maximum and 0, we want to redraw those cells.
                    // We get the ymin and ymax so that we can evaluate whether a cell needs to be copied
                    // or if a new random cell needs to be created.
                    let y_min = temp_board.get_bottom_column_bound(current_x, island);
                    let y_max = temp_board.get_top_column_bound(current_x, island);

                    let y_difference = (y_max - y_min) + 1;

                    // Iterating from the ymax to 0, either move the cell or create a new one.
                    for current_y in (0..=y_max).rev() {

                        if current_y.checked_sub(y_difference) == None {

                            // Create a new cell
                            self.board.set_cell(current_x, current_y, BoardCell::new(current_x, current_y));
                        } else {

                            // Move a cell
                            self.board.set_cell(current_x, current_y, *self.board.get_cell(current_x, current_y - y_difference))
                        }
                    }
                }

                self.board.update_islands();
            },

            // An island was not selected.
            None => {}
        }
    }
}
