pub mod phases;
pub mod player;

use phases::*;
use player::*;

/// Holds the state of the game. This is where data is stored and saved into a file
/// if neccessary. When it's reloaded from a file, it will be stored in this struct.
/// It holds player information, game information and other constants, variables and
/// functions that control the game. Think of it as a game master.
#[derive(Debug)]
pub struct GameState {
    pub player: User,
    pub comp: Comp,
    pub load_game: bool,
    pub play_tutorial: bool,
    pub turn_counter: u8,
    pub active_player_id: u8,
    pub phase: Phase,
    pub game_stage: GameStage,
}

impl GameState {
    pub fn new() -> Self {
        let player_deck = Vec::new();
        let comp_deck = Vec::new();

        GameState {
            player: User {
                name: String::new(),
                nickname: String::from("buttlicker"),
                hp: 20,
                hand: Hand::with_capacity(7),
                battlefield: Battlefield::new(),
                graveyard: Graveyard::new(),
                mana_pool: ManaPool::new(),
                deck: player_deck, // TODO: ugotovi kako naložit deck sem not
            },
            comp: Comp {
                name: String::new(),
                hp: 20,
                hand: Hand::with_capacity(7),
                battlefield: Battlefield::new(),
                graveyard: Graveyard::new(),
                mana_pool: ManaPool::new(),
                deck: comp_deck, // TODO: ugotovi kako naložit deck sem not
            },
            load_game: Default::default(),
            play_tutorial: Default::default(),
            turn_counter: 0,
            active_player_id: 0,
            phase: Phase::Upkeep,
            game_stage: GameStage::Setup,
        }
    }

    // pub fn save(&self, fname: &str) -> Result<(), std::io::Error> {
    //     // TODO: Implement saving logic here
    //     Ok(())
    // }

    // pub fn load(&self, fname: &str) -> Result<(), std::io::Error> {
    //     // TODO: Implement loading logic here
    //     Ok(())
    // }
}
