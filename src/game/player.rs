pub mod card_collection;

use card_collection::*;

pub enum HpOperation {
    Increase(u8),
    Decrease(u8),
}

/// This trait represents a player with stats and cards.
/// A player in this game will be a human or a computer and they both adopt the same rules.
pub trait Player {
    /// Return player's name.
    fn name(&self) -> &str;

    /// Set player's name.
    fn set_name(&mut self, new_name: String) -> ();

    /// Return player's current HP.
    fn hp(&self) -> u8;

    /// Set player's HP to a specific value.
    fn set_hp(&mut self, amount: u8);

    /// Increase or decrease a player's HP by a given amount.
    /// e.g.: state.player.adjust_hp(HpOperation::Increase(10));
    fn adjust_hp(&mut self, op: HpOperation);

    fn hand(&self) -> &Hand;
    fn hand_mut(&mut self) -> &mut Hand;

    fn deck(&self) -> &Deck;
    fn deck_mut(&mut self) -> &mut Deck;

    fn graveyard(&self) -> &Graveyard;
    fn graveyard_mut(&mut self) -> &mut Graveyard;

    fn mana_pool(&self) -> &ManaPool;
    fn mana_pool_mut(&mut self) -> &mut ManaPool;

    fn battlefield(&self) -> &Battlefield;
    fn battlefield_mut(&mut self) -> &mut Battlefield;
}

#[derive(Debug)]
pub struct User {
    pub name: String,
    pub nickname: String,
    pub hp: u8,
    pub hand: Hand,
    pub battlefield: Battlefield,
    pub graveyard: Graveyard,
    pub mana_pool: ManaPool,
    pub deck: Deck,
}

#[derive(Debug)]
pub struct Comp {
    pub name: String,
    pub hp: u8,
    pub hand: Hand,
    pub battlefield: Battlefield,
    pub graveyard: Graveyard,
    pub mana_pool: ManaPool,
    pub deck: Deck,
}
