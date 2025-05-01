use std::io::{self, Write};

#[derive(Debug)]
struct GameState {
    player: Player,
    comp: Player,
}

#[derive(Debug, Default)]
struct Player {
    is_computer: bool,
    name: String,
    nickname: String,
    hp: u8,
    hand: Vec<Card>,
    battlefield: Vec<Card>,
    graveyard: Vec<Card>,
    mana_pool: Vec<Card>,
}

#[derive(Debug)]
enum Card {
    Mana {
        color: CardColor,
    },
    Creature {
        color: CardColor,
        cost: u8,
        att: u8,
        def: u8,
    },
    Sorcery {
        color: CardColor,
        cost: u8,
    },
    Instant {
        color: CardColor,
        cost: u8,
    },
}

#[derive(Debug)]
enum CardColor {
    White,
    Red,
    Green,
    Blue,
    Black,
}

impl Player {
    fn new(name: String, is_computer: bool) -> Self {
        match is_computer {
            true => Player {
                is_computer,
                name,
                nickname: String::from("buttlicker"),
                hp: 20,
                hand: Vec::new(),
                battlefield: Vec::new(),
                graveyard: Vec::new(),
                mana_pool: Vec::new(),
            },
            false => Player {
                is_computer,
                name,
                nickname: String::from("machine"),
                hp: 20,
                hand: Vec::new(),
                battlefield: Vec::new(),
                graveyard: Vec::new(),
                mana_pool: Vec::new(),
            },
        }
    }
}

// TODO: create a function to fill up players decks with cards

fn main() -> io::Result<()> {
    print_welcome_message();

    // let mut will_load_game = false;
    let will_load_game = false;
    let mut play_tutorial = false;

    // select an option on first screen
    loop {
        let choice = get_usr_input(String::from(""))?;
        if choice == "q" {
            return Ok(());
        } else if choice == "l" {
            // TODO: make it load from file
            // will_load_game = true;
            println!("AHH: can't load game from file yet!");
            continue;
        } else if choice == "n" {
            println!("Starting a new game...\n");
            break;
        } else {
            println!("wrong choice.");
            continue;
        }
    }

    // if load game was selected, load game state from file
    if will_load_game {
        // TODO: add reading file logic here
    } else {
        let name = get_usr_input(String::from("What is thy name, wielder of archaic powers?"))?;
        let p1 = Player::new(name.to_string(), false);

        println!("Welcome, {}! The game is about to start.", &p1.nickname);

        let choice = get_usr_input(String::from(
            "Would you like to learn the ways of magic the gathering? [y/n]",
        ))?;

        if &choice[0..0] == "y" {
            play_tutorial = true;
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
    }

    if play_tutorial {}
    // if tutorial was selected, display extra prompts about the game and play a scripted game
    // explain the basics through the game
    //
    // [ player ]
    // 1. throw a coin (not random, player goes first)
    // 2. prompt the player to draw cards, tell him how cards are drawn at the beginning of the game
    // 3. tell the player about cards, decks, how to view hand, what stats mean, what color of card means
    // 4. tell him how mana works (tapping, untapping, playing cards) and prompt him to play a mana card
    // 5. prompt him to play a creature for 1 mana
    // 6. tell him about not being able to tap creatures and therefore not being able to attack on the first turn
    // 7. prompt him to end the turn
    //
    // [ computer ]
    // 7. simulate its turn by drawing a card, placing a mana card, tapping said mana, placing a creature
    //    and ending the turn
    //
    // [ player]
    // 8. prompt him to draw a card, explain to him that you draw a card every turn, if you run out
    //    of cards, you lose health
    // 9. prompt him to play another mana card and another creature
    // 10. prompt him to enter attacking phase, since one of his creatures is ready
    // 11. tell him about attacking - you attack the foe directly for dmg equal to your card's
    //     stats, the game ends when one of you loses all health
    // 12. tell him about blocking - the enemy can choose to block your creature with his creature, IF it
    //     can be tapped, preventing said dmg to him, but transfering it to its creature instead
    // 13. tell him about creature "standoff" - when does one creature die from blocking/attacking
    //     by comparing stats of both cards (don't mention instant spells yet)
    // 14. simulate the standoff, player's creature will win and live, the enemy one will die and
    //     go to graveyard
    // 15. tell him about the graveyard, simple
    // 16. prompt him to end the turn
    //
    // [ computer ]
    // 17. simulate its turn by drawing a card and ending the turn by not doing anything
    //
    // [ player ]
    // 18.
    //
    // ......
    // ......
    // tu bom pustil ta tutorial na miru in se bom fokusiral najprej na game logic, ker
    // že znam igrat.

    // TODO: fill up player's fields
    // TODO: create a computer struct
    // TODO: computer struct fill it up

    // TODO: start a new game
    // 1. shuffle decks
    // 2. draw cards

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
