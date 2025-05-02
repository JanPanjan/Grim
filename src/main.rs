use crossterm::execute;
use crossterm::terminal::{Clear, ClearType};
use std::io::{self, Write};
use std::thread;
use std::time::Duration;

pub mod game;

use game::{GameState, Player};

// TODO: create a function to fill up players librarys with cards

fn main() -> io::Result<()> {
    clear_screen()?;

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

    let mut state = GameState::new();

    loop {
        let choice = get_usr_input(String::from(""))?;

        match &choice[0..1] {
            "q" => return Ok(()),
            "l" => {
                // TODO: make it load from file
                state.will_load_game = true;

                println!("AHH: can't load game from file yet!");
                continue;
            }
            "n" => {
                state.will_load_game = false;

                println!("Starting a new game...\n");
                thread::sleep(Duration::from_secs(1));
                break;
            }
            _ => {
                println!("wrong choice.");
                continue;
            }
        }
    }

    // if load game was selected, load game state from file
    match state.will_load_game {
        true => {
            clear_screen()?;
            // TODO: add reading file logic here
        }
        false => {
            clear_screen()?;
            let player_name =
                get_usr_input(String::from("What is thy name, wielder of archaic powers?"))?;

            state.player.set_name(player_name);
            state.comp.set_name(String::from("Sire Oonga Boonga"));

            clear_screen()?;
            println!("Welcome, {}!", state.player.nickname());

            loop {
                let choice = get_usr_input(String::from(
                    "Would you like to learn the ways of magic the gathering? [y/n]",
                ))?;

                match &choice[0..1] {
                    "y" => {
                        state.play_tutorial = true;

                        clear_screen()?;
                        println!(
                            "Fright not, {}. Said game is not so hard to grasp, ",
                            state.player.nickname()
                        );

                        thread::sleep(Duration::from_secs(3));
                        println!("you'll get the hang of it quickly.\n");

                        thread::sleep(Duration::from_secs(2));
                        break;
                    }
                    "n" => {
                        state.play_tutorial = false;

                        println!("Very well.");
                        thread::sleep(Duration::from_secs(2));
                        break;
                    }
                    _ => {
                        println!("wrong choice.");
                        continue;
                    }
                }
            }

            println!("Let us begin the match!");
            thread::sleep(Duration::from_secs(3));

            println!("Gather around everyone! A humble novice challenger will throw");
            println!("cards around with our most feared player here!");
            thread::sleep(Duration::from_secs(4));

            println!("Sire oonga boonga!");
        }
    }

    if state.play_tutorial {}
    // if tutorial was selected, display extra prompts about the game and play a scripted game
    // explain the basics through the game
    //
    // [ player ]
    // 1. throw a coin (not random, player goes first)
    // 2. prompt the player to draw cards, tell him how cards are drawn at the beginning of the game
    // 3. tell the player about cards, librarys, how to view hand, what stats mean, what color of card means
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
    // 1. shuffle librarys
    // 2. draw cards

    Ok(())
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

/// Clears terminal screen
fn clear_screen() -> io::Result<()> {
    execute!(io::stdout(), Clear(ClearType::All))
}
