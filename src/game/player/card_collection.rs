// use rand::seq::SliceRandom;
// use rand::thread_rng;

#[derive(Debug)]
pub enum Card {
    Sorcery {
        name: String,
        desc: String,
        effect: Option<CardEffect>, // TODO: how to implement effects?
        color: Vec<Vec<CardColor>>,
        cost: ManaCost,
    },
    Instant {
        name: String,
        desc: String,
        color: Vec<CardColor>,
        cost: ManaCost,
        effect: Option<CardEffect>, // TODO: how to implement effects?
    },
    Land {
        tapped: bool,
        name: String,
        desc: String,
        effect: Option<CardEffect>, // TODO: how to implement effects?
        color: Vec<CardColor>,
    },
    Creature {
        tapped: bool,
        name: String,
        desc: String,
        color: Vec<CardColor>,
        cost: ManaCost,
        att: u8,
        def: u8,
    },
    Artifact {
        tapped: bool,
        name: String,
        desc: String,
        color: Vec<CardColor>,
        cost: ManaCost,
        effect: Option<CardEffect>, // TODO: how to implement effects?
    },
}

#[derive(Debug)]
pub enum CardColor {
    White,
    Red,
    Green,
    Blue,
    Black,
    Colorless,
}

#[derive(Debug)]
pub struct ManaCost {
    white: u8,
    red: u8,
    green: u8,
    blue: u8,
    black: u8,
    colorless: u8,
}

pub enum CardEffect {}
