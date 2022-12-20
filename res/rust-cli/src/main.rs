
use std::io;

mod pop_three;

const WIDTH: u8 = 8;
const HEIGHT: u8 = 7;

fn convert_color_to_ascii(color: (u8, u8, u8)) -> String {
    match color {
        (255, 0, 0) => return String::from("\x1b[91m\u{2588}\x1b[0m"),
        (0, 255, 0) => return String::from("\x1b[92m\u{2588}\x1b[0m"),
        (0, 0, 255) => return String::from("\x1b[94m\u{2588}\x1b[0m"),
        (0, 255, 255) => return String::from("\x1b[95m\u{2588}\x1b[0m"),
        (255, 0, 255) => return String::from("\x1b[93m\u{2588}\x1b[0m"),
        (1_u8..=254_u8, _, _) => return String::from("\x1b[0m\u{2588}\x1b[0m"),
        (0_u8, 1_u8..=254_u8, _) | (u8::MAX, 1_u8..=u8::MAX, _) => return String::from("\x1b[0m\u{2588}\x1b[0m"),
        (0_u8, 0_u8, 0_u8..=254_u8) | (0_u8, u8::MAX, 1_u8..=254_u8) | (u8::MAX, 0_u8, 1_u8..=254_u8) => return String::from("\x1b[0m\u{2588}\x1b[0m")
    }
}

fn print_game_state(game_state: Vec<(u8, u8, u8)>) {
    print!(" ");
    for each_x in 0..WIDTH {
        print!("{}", each_x);
        if each_x == (WIDTH - 1) {
            print!("\n");
        }
    }
    for each_y in 0..HEIGHT {
        print!("{}", each_y);
        for each_x in 0..WIDTH {
            print!("{}", convert_color_to_ascii(game_state[(usize::from(each_y) * usize::from(WIDTH)) + usize::from(each_x)]));

            if each_x == (WIDTH - 1) {
                print!("\n");
            }
        }
    }
}

fn main() {

    let mut main_game = pop_three::Game::new().with_dimensions(WIDTH, HEIGHT);
    let mut game_state = main_game.get_game_board();

    print_game_state(game_state);

    loop {

        let mut user_x = String::new();
        let mut user_y = String::new();

        println!("Choose Coord x: ");
        io::stdin().read_line(&mut user_x).expect("error: unable to read user input");
        println!("\nChoose Coord y: ");
        io::stdin().read_line(&mut user_y).expect("error: unable to read user input");
        
        main_game.select(user_x.trim().parse::<u8>().unwrap(), user_y.trim().parse::<u8>().unwrap());

        game_state = main_game.get_game_board();

        print_game_state(game_state);
    }

}