#include "classes.h"
#include <Windows.h>
int main()
{
	Font font;
	RenderWindow window(VideoMode(1200, 600), "Avl/BST visualization");
	if (!font.loadFromFile("Maves-Regular.ttf"))
	{
		return EXIT_FAILURE;
	}
	Event event;
	string choice;
	AVL hash;
	bool var;
	Text prompt;
	CircleShape cover;
	cover.setRadius(20);
	cover.setFillColor(Color::White);
	cover.setOutlineThickness(3);
	cover.setOutlineColor(Color(250, 150, 100));
	int circX = 550;
	int circY = 100;
	int textX = 560;
	int textY = 105;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			prompt.setCharacterSize(50);
			prompt.setFillColor(Color::White);
			prompt.setFont(font);
			prompt.setPosition(340, 0);
			prompt.setString("A V L HashTable");
			window.draw(prompt);
			window.display();
			while (choice != "0")
			{
				cout << "1:Insert Data" << endl << "2:Search" << endl << "0:Terminate" << endl;
				cout << "Enter: ";
				cin >> choice;
				if (choice == "1")
				{
					int data;
					cout << "Please enter data: ";
					cin >> data;
					var = hash.insert(data,circX,circY,textX,textY);
					if (var == true)
					{
						prompt.setCharacterSize(50);
						prompt.setFillColor(Color::White);
						prompt.setFont(font);
						prompt.setPosition(340, 0);
						prompt.setString("A V L HashTable");
						window.draw(prompt);
						string fill;
						fill = to_string(data % 10);
						prompt.setCharacterSize(24);
						prompt.setFillColor(Color::Black);
						prompt.setFont(font);
						prompt.setPosition(textX, textY);
						prompt.setString(fill);
						cover.setPosition(circX, circY);
						window.draw(cover);
						window.draw(prompt);
						window.display();
					}
				}
				else if (choice == "2")
				{
					int data;
					cout << "Please enter data to search: ";
					cin >> data;
					hash.search(data);
					
				}
				else if (choice == "0")
				{
					return 0;
				}
				else
				{
					cout << "Invalid Input! Please try again." << endl;
				}
			}
			if (event.type == Event::Closed)
			{
				window.close();
			}
			//window.display();
		}
		
	}
	Text prompt1("BSDK", font, 50);
	return 0;
}