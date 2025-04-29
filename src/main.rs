use cursive::{Cursive, CursiveExt};
// use cursive::event::{Event, Key};
use cursive::event::Key;
use cursive::view::{Nameable, Resizable}; // Import Resizable
use cursive::views::{Dialog, LinearLayout, Panel, StackView, TextView}; // Import StackView and Panel

fn main() {
    let mut siv = Cursive::default();

    // --- Welcome Screen ---
    // Create the text views for the welcome message and prompt
    let welcome_text = TextView::new("Welcome to GRIM").center();
    let prompt_text = TextView::new("Press Enter to begin").center();

    // Arrange them vertically in a LinearLayout
    let welcome_layout = LinearLayout::vertical()
        .child(welcome_text)
        .child(TextView::new("")) // Add some spacing
        .child(prompt_text);

    // --- Game Screen (Placeholder) ---
    // This is what will be shown after pressing Enter.
    // We create it now but won't show it initially.
    let game_view = Panel::new(TextView::new("Game Area - Player 1 vs Player 2")) // Use Panel for structure
        .title("GRIM - The Game")
        .with_name("game_panel"); // Give it a name to potentially find later

    // --- Screen Management using StackView ---
    // StackView manages different "layers" or "screens". We start with the welcome screen.
    let mut stack = StackView::new();

    // Add the welcome layout as the first layer, wrapped in a Dialog for centering and looks.
    // Make it take up a good portion of the screen but not necessarily all.
    stack.add_layer(
        Dialog::around(welcome_layout)
            .title("Welcome")
            .fixed_width(40), // Give the dialog a fixed width
    );

    // Give the StackView a name so we can find it later in the callback
    siv.add_layer(stack.with_name("main_stack"));

    // --- Event Handling ---
    // Add a global callback for the Enter key
    siv.add_global_callback(Key::Enter, |s| {
        // Find the StackView by its name
        s.call_on_name("main_stack", |stack: &mut StackView| {
            // IMPORTANT: Check if we are still on the welcome screen before adding the game view.
            // This prevents adding multiple game views if Enter is pressed again later.
            // A simple way is to check the number of layers or add a flag.
            // Here, we'll just assume if Enter is caught by this *specific* callback,
            // it's the first time from the welcome screen.

            // Add the game_view (which we created earlier) as a new layer on top
            // Use add_fullscreen_layer to make it take the whole screen
            stack.add_fullscreen_layer(game_view); // Add the game view we prepared

            // Optional: Remove the welcome screen layer from underneath if desired
            // stack.remove_layer(Position::Back);

            println!("Transitioning to game view..."); // Debug message
        });

        // CRUCIAL: Once we transition, we probably don't want this specific
        // global Enter callback anymore. Remove it.
        // If you need Enter for game actions later, you'll add different callbacks
        // specific to the game view/state.
        s.clear_global_callbacks(Key::Enter);
    });

    // Add a quit callback (optional, Ctrl+C works by default)
    siv.add_global_callback('q', |s| s.quit());

    // --- Run the application ---
    siv.run();
}
