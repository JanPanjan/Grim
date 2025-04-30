use std::io::{self, Write};

#[derive(Debug)]
struct GameState {
    player: Player,
    comp: Player,
}

#[derive(Debug, Default)]
struct Player {
    name: String,
    nickname: String,
    hp: u8,
    mana: u8,
}

impl Player {
    fn new(name: String) -> Self {
        Player {
            name,
            nickname: String::from("buttlicker"),
            hp: 20,
            mana: 0,
        }
    }
}

fn main() -> io::Result<()> {
    print_welcome_message();

    loop {
        let choice = get_usr_input(String::from(""))?;

        if choice == "q" {
            break;
        } else if choice == "l" {
            println!("AHH: can't load game from file yet! >");
        } else if choice == "n" {
            println!("Starting a new game...\n");

            let name = get_usr_input(String::from("What is thy name, wielder of archaic powers?"))?;
            let p1 = Player::new(name.to_string());

            println!("Welcome, {}! The game is about to start.", &p1.nickname);
            println!("Would you like to learn the ways of magic the gathering?");

            let choice = get_usr_input(String::from("yes/no"))?;
            if choice == "yes" {
                println!(
                    "Fright not, {}. Said game is not so hard to grasp, ",
                    &p1.nickname
                );
                println!("you'll get the hang of it quickly.\n");
            }

            println!("Let us begin the match!");
            println!("Gather around everyone! A humble novice challenger will throw");
            println!("cards around with our most feared player here!");
            println!("Sire oonga boonga!");
        } else {
            println!("wrong choice.");
            continue;
        }
    }

    Ok(())
}

fn print_welcome_message() -> () {
    println!("");
    println!("");
    println!("-------------------- Welcome to GRIM! -----------------------");
    println!("");
    println!("This is a terminal emulation of the famous card game, magic");
    println!("                      the gathering.");
    println!("");
    println!("                    New game  - n");
    println!("                    Load game - l");
    println!("                    Quit game - q");
}

/// Gets user input. Reads a line from stdin, trims whitespace, returns a String on success,
/// otherwise std::io::Error.
fn get_usr_input(msg: String) -> io::Result<String> {
    println!("{}", msg);
    print!("> ");
    io::stdout().flush()?;
    let mut input = String::new();
    io::stdin().read_line(&mut input)?; // can fail
    Ok(input.trim().to_string())
}
