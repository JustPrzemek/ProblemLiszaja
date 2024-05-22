#include "Button.h"


Button::Button(std::string t, sf::Vector2f size, int charSize, sf::Color bcolor, sf::Color textColor) {
	text.setString(t);
	text.setFillColor(textColor);
	text.setCharacterSize(charSize);
	button.setSize(size);
	button.setFillColor(bcolor);

}

void Button::setFont(sf::Font& font)
{
	text.setFont(font);
}

void Button::setBackColor(sf::Color color)
{
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos)
{
	button.setPosition(pos);

	float xPos = (pos.x + button.getLocalBounds().width / 3) ;
	float yPos = (pos.y + button.getLocalBounds().height / 3);
	text.setPosition(xPos, yPos-10);
}

void Button::drawTo(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float bPosX = button.getPosition().x;
	float bPosY = button.getPosition().y;

	float btnPosWidth = button.getPosition().x + button.getLocalBounds().width;
	float btnPosHeight = button.getPosition().y + button.getLocalBounds().height;

	if (mouseX < btnPosWidth && mouseX > bPosX && mouseY < btnPosHeight && mouseY > bPosY)
	{
		return true;
	}
	return false;

}