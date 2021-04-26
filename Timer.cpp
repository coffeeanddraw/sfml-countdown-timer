#include <SFML/Graphics.hpp>

int main() {
	// Fullscreen Window //
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Timer", sf::Style::Fullscreen);

	// Text & Font 
	sf::Font timerFont;
	sf::Text timerText;
	timerFont.loadFromFile("fonts/ShipporiMincho-Regular.ttf");
	timerText.setFont(timerFont);
	timerText.setString("00:000");
	timerText.setCharacterSize(300);
	timerText.setFillColor(sf::Color::White);

	// Text Position //
	sf::FloatRect timerTextRect = timerText.getLocalBounds();
	timerText.setOrigin(timerTextRect.left + timerTextRect.width / 2.0f, timerTextRect.top + timerTextRect.height / 2.0f);
	timerText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	// Timer Variables //
	sf::Clock clock;
	float duration = 20.0f;
	float fMiliseconds, fSeconds;
	int intMiliseconds, intSeconds;
	sf::String stringMiliseconds;
	sf::String stringSeconds;
	sf::String timerString;

	while (window.isOpen()) {

		// Handle Input //
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
				
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}		
		}

		// (Re)start Timer //
		sf::Time time = clock.restart();

		// Timer Countdown //
		if (duration > 0) {
			// Calculate countdown
			duration -= time.asSeconds();
			fMiliseconds = std::modf(duration, &fSeconds);
			// Change float to int
			int intSeconds = static_cast<int>(fSeconds);
			int intMiliseconds = static_cast<int>(fMiliseconds * 1000);
			// Change int to string 
			stringMiliseconds = std::to_string(intMiliseconds);
			stringSeconds =std::to_string(intSeconds);
			
			if (intMiliseconds <= 0) {
				stringMiliseconds = "000";  
			}

			if (intSeconds <= 0) {
				stringSeconds = "00"; 
			}
			else if (intSeconds < 10) {
				stringSeconds = "0" + stringSeconds; 
			}

			timerString = stringSeconds + ":" + stringMiliseconds;
			timerText.setString(timerString);
		}

		window.clear();
		window.draw(timerText);
		window.display();
	}

	return 0;
}