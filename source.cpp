#include <iostream>
#include <conio.h>
#include <vector>
using namespace System;
using std::cout;
using std::vector;

class SnakeJuego
{
protected:
	const int ancho = 50;
	const int alto = 20;
	bool gameover = false;
public:

	struct Punto
	{
		int x = 0;
		int y = 0;

	};

	void bordes() {
		for (int i = 0; i < alto + 2; i++)
		{
			for (int j = 0; j < ancho + 2; j++)
			{
				if (i == 0 || j == 0 || j == ancho + 1 || i == alto + 1) cout << "#";
				else cout << " ";
			}
			cout << "\n";
		}
	}
	void removeCursor()
	{
		Console::CursorVisible = false;
	}
	void iniciar();
	void pause()
	{
		std::cin.get();
	}



};

class Snake : virtual public SnakeJuego
{
private:
	vector<Punto> cuerpo;
	Punto direccional;
	int score;
	int cola;
public:
	Snake()
	{
		Punto cabeza;
		cuerpo.push_back(cabeza);
		cuerpo[0].x = 5;
		cuerpo[0].y = 5;		
		cola = 0;
		score = 0;
	}

	inline int getX()
	{
		return this->cuerpo[0].x;
	}

	inline int getY()
	{
		return cuerpo[0].y;
	}

	inline int getanyX(int i)
	{
		return cuerpo[i].x;
	}
	
	inline int getanyY(int i)
	{
		return cuerpo[i].y;
	}

	inline int getCola()
	{
		return cola;
	}

	inline int getScore()
	{
		return score;
	}

	inline void setDX(int dx)
	{
		this->direccional.x = dx;
	}

	inline void setDY(int dy)
	{
		this->direccional.y = dy;
	}

	inline void sumCola(int c)
	{
		cola += c;
	}

	inline void addScore(int v)
	{
		score += v;
	}

	void addTail()
	{
		Punto nuevacola;
		sumCola(1);
		cuerpo.push_back(nuevacola);
		cuerpo[getCola()].x = cuerpo[getCola() - 1].x;
		cuerpo[getCola()].y = cuerpo[getCola() - 1].y;
	}

	void mover(Snake& snake)
	{
		if (cuerpo[0].x + snake.direccional.x > ancho || cuerpo[0].x + snake.direccional.x <= 0 || cuerpo[0].y + snake.direccional.y > alto || cuerpo[0].y + snake.direccional.y <= 0)
		{
			snake.direccional.x = 0;
			snake.direccional.y = 0;

			snake.gameover = true;
		}

		for (int i = cola; i > 0; i--)
		{
			cuerpo[i] = cuerpo[i - 1];
		}

				
		cuerpo[0].x += snake.direccional.x;
		cuerpo[0].y += snake.direccional.y;
		
	}

	void chequeo(Snake& snake)
	{
		for (int i = 1; i < cola; i++)
		{
			if (cuerpo[0].x == cuerpo[i].x && cuerpo[0].y == cuerpo[i].y) snake.gameover = true;
		}
		
	}

	void borrar()
	{
		for (int i = 0; i < cola+1; i++)
		{
			Console::SetCursorPosition(cuerpo[i].x, cuerpo[i].y);
			cout << " ";
		}
	}

	void imprimir()
	{
		for (int i = 0; i < cola+1; i++)
		{
			Console::SetCursorPosition(cuerpo[i].x, cuerpo[i].y);
			Console::BackgroundColor = ConsoleColor::Red;
			cout << " ";
		}
		Console::ResetColor();
	}

	void showScore()
	{
		Console::ResetColor();
		Console::SetCursorPosition(56, 0);
		cout << "SCORE: " << score;
	}
};

class Fruit : public Snake
{
private:
	Punto manzana[5];
	Snake snake;
	
public:
	Fruit()
	{
		for (int i = 0; i < 5; i++)
		{
			manzana[i].x = rand() % 10+1;
			manzana[i].y = rand() % 10+1;
		}
	}

	void imprimir()
	{
		for (int i = 0; i < 5; i++)
		{
		Console::SetCursorPosition(manzana[i].x, manzana[i].y);
		Console::BackgroundColor = ConsoleColor::Yellow;
		cout << " ";
		}
		Console::ResetColor();
	
	}

	void borrar()
	{
		for (int i = 0; i < 5; i++)
		{
			Console::SetCursorPosition(manzana[i].x, manzana[i].y);
			cout << " ";
		}
	}

	void captura(Snake& snake, Fruit& fruit)
	{

		for (int i = 0; i < 5; i++)
		{
			if (fruit.manzana[i].x == snake.getX() && fruit.manzana[i].y == snake.getY())
			{
				

				borrar();
				fruit.manzana[i].x = rand() % 50 + 1;
				fruit.manzana[i].y = rand() % 10 + 1;
				for (int i = 0; i < snake.getCola(); i++)
				{
					if (fruit.manzana[i].x == snake.getanyX(i) && fruit.manzana[i].y == snake.getanyY(i))
					{
						fruit.manzana[i].x = rand() % 50 + 1;
						fruit.manzana[i].y = rand() % 10 + 1;
					}
				}
				imprimir();
				snake.addTail();
				snake.addScore(100);
			}
		}	
	}
};

class Player : public Snake
{
private:
	enum direcciones
	{
		arriba = 'w',
		abajo = 's',
		izquierda = 'a',
		derecha = 'd',
		stop = 0
	};
	direcciones dir;
	direcciones sigdir;
	int accel;
	Snake snake;
public:
	Player(): dir(stop) {};
	bool eventoValido(direcciones siguiente)
	{
		switch (dir)
		{
		case Player::arriba:
			if (siguiente == abajo)
			{
				return false;
			}
			return true;
			break;
		case Player::abajo:
			if (siguiente == arriba)
			{
				return false;
			}
			return true;
			break;
		case Player::izquierda:
			if (siguiente == derecha)
			{
				return false;
			}
			return true;
			break;
		case Player::derecha:
			if (siguiente == izquierda)
			{
				return false;
			}
			return true;
			break;
		case Player::stop:
			return false;
		}
	}

	void eventoTeclado(Snake& snake)
	{

		if (_kbhit())
		{
			sigdir = direcciones(_getch());
			if (!eventoValido(sigdir) && snake.getCola()>0) return;

			dir = sigdir;
			switch (dir)
			{
			case Player::arriba:
			if (snake.getCola() % 5 == 0 && snake.getCola() != 0)
			{
				snake.setDX(0);
				snake.setDY(-2);
			}
			else
			{
				snake.setDX(0);
				snake.setDY(-1);
			}
				break;
			case Player::abajo:
				if (snake.getCola() % 5 == 0 && snake.getCola() != 0)
				{
					snake.setDX(0);
					snake.setDY(2);
				}
				else
				{
					snake.setDX(0);
					snake.setDY(1);
				}
				break;
			case Player::izquierda:
				if (snake.getCola() % 5 == 0 && snake.getCola() != 0)
				{
					snake.setDX(-2);
					snake.setDY(0);
				}
				else
				{
					snake.setDX(-1);
					snake.setDY(0);
				}
				
				break;
			case Player::derecha:
				if (snake.getCola() % 10 == 0 && snake.getCola() != 0)
				{
					snake.setDX(2);
					snake.setDY(0);
				}
				else
				{
					snake.setDX(1);
					snake.setDY(0);
				}
				break;
			}
		}
	}
};



void SnakeJuego::iniciar()
{
	Snake snake;
	Fruit fruit;
	Player player;

	removeCursor();
	bordes();
	fruit.imprimir();
	while (!snake.gameover)
	{
		snake.showScore();
		snake.borrar();
		player.eventoTeclado(snake);
		snake.mover(snake);
		snake.imprimir();
		fruit.captura(snake,fruit);
		snake.chequeo(snake);
		_sleep(50);
	}
	
	
}

int main() {
	srand(time(0));
	
	SnakeJuego juego;
	juego.iniciar();
	
	return 0;
}
