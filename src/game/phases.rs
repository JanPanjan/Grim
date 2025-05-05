#[derive(Debug)]
pub enum GameStage {
    Setup,
    TurnBased,
    GameEnd,
}

#[derive(Debug)]
pub enum Phase {
    Untap,
    Upkeep,
    Draw,
    Precombat,
    Combat,
    Postcombat,
    Ending,
}
