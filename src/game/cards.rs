pub trait CardContainer {
    /// Creates a new instance of the container.
    fn new() -> Self;

    /// Returns a reference to the cards in the container.
    fn cards(&self) -> &[Card];

    /// Returns vector of pairs (Card, u8), where u8 is index in the contained
    fn search(&self) -> &Vec<(Card, u8)>;

    /// Adds one card into the container.
    fn insert(&mut self, card: &Card);

    /// Removes one card from the container and returns a reference to it.
    fn remove(&mut self, card: &Card) -> &Card;

    /// Some containers don't have max capacity, e.g. Mana pool, so it will return None
    fn capacity(&self) -> Option<&u8>;

    /// Returns the number of cards in the container.
    fn len(&self) -> usize {
        self.cards().len()
    }

    /// Returns true if the container is empty.
    fn is_empty(&self) -> bool {
        self.cards().is_empty()
    }

    /// Returns true if the container is at max capacity, except None for containers
    /// with unlimited capacity.
    fn is_full(&self) -> Option<bool>;
}

#[derive(Debug, Default)]
pub struct Hand {
    cards: Vec<Card>,
    capacity: u8,
}

// TODO: implement all trait methods
impl CardContainer for Hand {
    fn new() -> Self {
        Hand {
            cards: Vec::new(),
            capacity: 7,
        }
    }

    fn cards(&self) -> &[Card] {
        &self.cards
    }

    fn capacity(&self) -> Option<&u8> {
        Some(&self.capacity)
    }
}

#[derive(Debug, Default)]
pub struct Deck {
    cards: Vec<Card>,
    capacity: u8,
}

// TODO: implement all trait methods
impl CardContainer for Deck {
    pub fn new(initial_cards: Vec<Card>) -> Self {
        assert_eq!(initial_cards.len(), 60);

        Deck {
            cards: initial_cards,
            capacity: 60,
        }
    }

    pub fn draw_card(&mut self) -> Option<Card> {
        if self.cards.is_empty() {
            None
        } else {
            // remove(0) is O(n), but drawing from a Vec is usually fine.
            // A VecDeque might be slightly more efficient for drawing from the front.
            Some(self.cards.remove(0))
        }
    }

    pub fn cards(&self) -> &[Card] {
        &self.cards
    }

    pub fn capacity(&self) -> &u8 {
        &self.capacity
    }
}

/// Represents a player's graveyard.
#[derive(Debug, Default)]
pub struct Graveyard {
    cards: Vec<Card>,
    // Graveyard might need methods like: add_card, cards(), cards_mut()
    // Check if a card exists (for recursion/reanimation effects)
}

// TODO: implement all trait methods
impl CardContainer for Graveyard {
    pub fn new() -> Self {
        Graveyard { cards: Vec::new() }
    }

    pub fn add_card(&mut self, card: Card) {
        self.cards.push(card); // Cards go to the top of the graveyard
    }

    // Get immutable slice
    pub fn cards(&self) -> &[Card] {
        &self.cards
    }

    // Get mutable reference (use with caution)
    pub fn cards_mut(&mut self) -> &mut Vec<Card> {
        &mut self.cards
    }
    // ... other graveyard-specific methods
}

/// Represents a player's mana pool.
#[derive(Debug, Default)]
pub struct ManaPool {
    available_mana: Vec<Card>,
    tapped_mana: Vec<Card>,
}

// TODO: implement all trait methods
impl CardContainer for ManaPool {
    pub fn new() -> Self {
        ManaPool {
            available_mana: Vec::new(),
            tapped_mana: Vec::new(),
        }
    }

    pub fn add_land(&mut self, card: Card) {
        self.mana_sources.push(card);
    }

    // Tap a source to add mana to the pool for the turn (requires a concept of 'tapped')
    // This becomes more complex. Let's simplify and assume this tracks mana sources played.

    // Get immutable slice of sources
    pub fn sources(&self) -> &[Card] {
        &self.mana_sources
    }

    // Get mutable reference to sources (use with caution)
    pub fn sources_mut(&mut self) -> &mut Vec<Card> {
        &mut self.mana_sources
    }
    // ... methods for tapping, adding mana, spending mana
}

// TODO: Implement the Battlefield struct
#[derive(Debug)]
pub struct Battlefield {
    creatures: Vec<Card>,
    permanents: Vec<Card>,
}

// TODO: implement all trait methods
impl CardContainer for Battlefield {
    pub fn new() -> Self {
        Battlefield {
            creatures: Vec::new(),
            permanents: Vec::new(),
        }
    }
}

#[derive(Debug)]
pub enum Card {
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
pub enum CardColor {
    White,
    Red,
    Green,
    Blue,
    Black,
}
