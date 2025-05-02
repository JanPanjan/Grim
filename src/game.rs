pub mod cards;

use cards::*;

/// Holds the state of the game. This is where data is stored and saved into a file
/// if neccessary. When it's reloaded from a file, it will be stored in this struct.
/// It holds player information, game information and other constants, variables and
/// functions that control the game. Think of it as a game master.
#[derive(Debug)]
pub struct GameState {
    pub will_load_game: bool,
    pub play_tutorial: bool,
    pub player: User,
    pub comp: Comp,
}

impl GameState {
    pub fn new() -> Self {
        GameState {
            will_load_game: Default::default(),
            play_tutorial: Default::default(),
            player: User {
                name: String::new(),
                nickname: String::from("buttlicker"),
                hp: 20,
                hand: Hand::new(),
                battlefield: Battlefield::new(),
                graveyard: Graveyard::new(),
                mana_pool: ManaPool::new(),
                deck: Deck::new(), // TODO: ugotovi kako naložit deck sem not
            },
            comp: Comp {
                name: String::new(),
                hp: 20,
                hand: Hand::new(),
                battlefield: Battlefield::new(),
                graveyard: Graveyard::new(),
                mana_pool: ManaPool::new(),
                deck: Deck::new(), // TODO: ugotovi kako naložit deck sem not
            },
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

pub enum HpOperation {
    Increase(u8),
    Decrease(u8),
}

/// This trait represents a player with stats and cards.
/// A player in this game will be a human or a computer and they both adopt the same rules.
pub trait Player {
    /// Return player's name.
    fn name(&self) -> &String;

    /// Set player's name.
    fn set_name(&mut self, new_name: String);

    /// Return player's current HP.
    fn hp(&self) -> &u8;

    /// Set player's HP to a specific value.
    fn set_hp(&mut self, amount: u8);

    /// Increase or decrease a player's HP by a given amount.
    /// e.g.: state.player.adjust_hp(HpOperation::Increase(10));
    fn adjust_hp(&mut self, op: HpOperation);

    fn hand(&self) -> &Hand;
    fn deck(&self) -> &Deck;
    fn graveyard(&self) -> &Graveyard;
    fn mana_pool(&self) -> &ManaPool;
}

#[derive(Debug)]
pub struct User {
    name: String,
    nickname: String,
    hp: u8,
    hand: Hand,
    battlefield: Battlefield,
    graveyard: Graveyard,
    mana_pool: ManaPool,
    deck: Deck,
}

// TODO:
impl Player for User {}

impl User {
    pub fn name(&self) -> &str {
        &self.name
    }

    pub fn nickname(&self) -> &str {
        &self.nickname
    }

    pub fn set_nickname(&mut self, new_nickname: String) {
        self.nickname = new_nickname;
    }

    pub fn hp(&self) -> &u8 {
        &self.hp
    }

    // TODO: implement card methods
}

#[derive(Debug)]
pub struct Comp {
    name: String,
    hp: u8,
    hand: Hand,
    battlefield: Battlefield,
    graveyard: Graveyard,
    mana_pool: ManaPool,
    deck: Deck,
}

// TODO:
impl Player for Comp {}

impl Comp {
    pub fn name(&self) -> &str {
        &self.name
    }

    pub fn hp(&self) -> &u8 {
        &self.hp
    }

    // TODO: implement card methods
}
