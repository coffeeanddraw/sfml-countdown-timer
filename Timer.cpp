#include <SFML/Graphics.hpp>

int main() {
	// Fullscreen Window //
	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Timer", sf::Style::Fullscreen);

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
	float fMilliseconds, fSeconds;
	int intMilliseconds, intSeconds;
	sf::String stringMilliseconds;
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
			fMilliseconds = std::modf(duration, &fSeconds);
			// Change float to int
			intSeconds = static_cast<int>(fSeconds);
			intMilliseconds = static_cast<int>(fMilliseconds * 1000);
			// Change int to string 
			stringMilliseconds = std::to_string(intMilliseconds);
			stringSeconds =std::to_string(intSeconds);
			
			if (intMilliseconds <= 0) {
				stringMilliseconds = "000";  
			}

			if (intSeconds <= 0) {
				stringSeconds = "00"; 
			}
			else if (intSeconds < 10) {
				stringSeconds = "0" + stringSeconds; 
			}

			timerString = stringSeconds + ":" + stringMilliseconds;
			timerText.setString(timerString);
		}

		window.clear();
		window.draw(timerText);
		window.display();
	}

	return 0;
}