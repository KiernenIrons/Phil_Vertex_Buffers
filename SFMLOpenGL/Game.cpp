#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}
}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[36];
GLubyte triangles[36];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	/* Vertices counter-clockwise winding */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0, 0, -8);
	glEnable(GL_CULL_FACE);

	vertex[0].coordinate[0] = -1.0f;
	vertex[0].coordinate[1] = -1.0f;
	vertex[0].coordinate[2] = 1.0f;

	vertex[1].coordinate[0] = 1.0f;
	vertex[1].coordinate[1] = -1.0f;
	vertex[1].coordinate[2] = 1.0f;

	vertex[2].coordinate[0] = 1.0f;
	vertex[2].coordinate[1] = 1.0f;
	vertex[2].coordinate[2] = 1.0f;

	vertex[3].coordinate[0] = -1.0f;
	vertex[3].coordinate[1] = 1.0f;
	vertex[3].coordinate[2] = 1.0f;

	vertex[4].coordinate[0] = -1.0f;
	vertex[4].coordinate[1] = -1.0f;
	vertex[4].coordinate[2] = -1.0f;

	vertex[5].coordinate[0] = 1.0f;
	vertex[5].coordinate[1] = -1.0f;
	vertex[5].coordinate[2] = -1.0f;

	vertex[6].coordinate[0] = 1.0f;
	vertex[6].coordinate[1] = 1.0f;
	vertex[6].coordinate[2] = -1.0f;

	vertex[7].coordinate[0] = -1.0f;
	vertex[7].coordinate[1] = 1.0f;
	vertex[7].coordinate[2] = -1.0f;

	vertex[0].color[0] = 0.1f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.2f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.3f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.6f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	vertex[6].color[0] = 1.0f;
	vertex[6].color[1] = 1.0f;
	vertex[6].color[2] = 1.0f;

	vertex[7].color[0] = 1.0f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 1.0f;

	vertex[8].color[0] = 1.0f;
	vertex[8].color[1] = 1.0f;
	vertex[8].color[2] = 1.0f;

	vertex[6].color[0] = 0.0f;
	vertex[6].color[1] = 0.0f;
	vertex[6].color[2] = 1.0f;

	vertex[7].color[0] = 0.0f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 0.0f;

	vertex[8].color[0] = 1.0f;
	vertex[8].color[1] = 0.0f;
	vertex[8].color[2] = 0.0f;


	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 2;   triangles[4] = 3;   triangles[5] = 0;
	triangles[6] = 2;   triangles[7] = 6;   triangles[8] = 3;

	triangles[9] = 6;   triangles[10] = 7;   triangles[11] = 3;
	triangles[12] = 7;   triangles[13] = 6;   triangles[14] = 5;
	triangles[15] = 5;   triangles[16] = 4;   triangles[17] = 7;

	triangles[18] = 5;   triangles[19] = 0;   triangles[20] = 4;
	triangles[21] = 0;   triangles[22] = 5;   triangles[23] = 1;
	triangles[24] = 6;   triangles[25] = 1;   triangles[26] = 5;

	triangles[27] = 6;   triangles[28] = 2;   triangles[29] = 1;
	triangles[30] = 4;   triangles[31] = 0;   triangles[32] = 3;
	triangles[33] = 7;   triangles[34] = 4;   triangles[35] = 3;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		Matrix3 rotation;

		for (int index = 0; index < 8; index++)
		{
			Vector3 vector;
			vector.setX(vertex[index].coordinate[0]);
			vector.setY(vertex[index].coordinate[1]);
			vector.setZ(vertex[index].coordinate[2]);

			vector = rotation.RotationX(rotationAngle) * vector;
			vertex[index].coordinate[0] = vector.getX();
			vertex[index].coordinate[1] = vector.getY();
			vertex[index].coordinate[2] = vector.getZ();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		Matrix3 rotation;

		for (int index = 0; index < 8; index++)
		{
			Vector3 vector;
			vector.setX(vertex[index].coordinate[0]);
			vector.setY(vertex[index].coordinate[1]);
			vector.setZ(vertex[index].coordinate[2]);

			vector = rotation.RotationY(rotationAngle) * vector;
			vertex[index].coordinate[0] = vector.getX();
			vertex[index].coordinate[1] = vector.getY();
			vertex[index].coordinate[2] = vector.getZ();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		Matrix3 rotation;

		for (int index = 0; index < 8; index++)
		{
			Vector3 vector;
			vector.setX(vertex[index].coordinate[0]);
			vector.setY(vertex[index].coordinate[1]);
			vector.setZ(vertex[index].coordinate[2]);

			vector = rotation.RotationZ(rotationAngle) * vector;
			vertex[index].coordinate[0] = vector.getX();
			vertex[index].coordinate[1] = vector.getY();
			vertex[index].coordinate[2] = vector.getZ();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		Matrix3 scale;

		for (int index = 0; index < 8; index++)
		{
			Vector3 vector;
			vector.setY(vertex[index].coordinate[0]);
			vector.setY(vertex[index].coordinate[1]);
			vector.setZ(vertex[index].coordinate[2]);

			vector = scale.Scale3D(99.9) * vector;
			vertex[index].coordinate[0] = vector.getX();
			vertex[index].coordinate[1] = vector.getY();
			vertex[index].coordinate[2] = vector.getZ();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Matrix3 translate;

		for (int index = 0; index < 8; index++)
		{
			Vector3 vector;
			vector.setX(vertex[index].coordinate[0]);
			vector.setY(vertex[index].coordinate[1]);
			vector.setZ(vertex[index].coordinate[2]);

			vector.setZ(1);
			vector = translate.Translate(0, 0.005) * vector;
			
			vertex[index].coordinate[0] = vector.getX();
			vertex[index].coordinate[1] = vector.getY();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Matrix3 translate;

		for (int index = 0; index < 8; index++)
		{
			Vector3 vector;
			vector.setX(vertex[index].coordinate[0]);
			vector.setY(vertex[index].coordinate[1]);
			vector.setZ(vertex[index].coordinate[2]);

			vector.setZ(1);
			vector = translate.Translate(0, -0.005) * vector;

			vertex[index].coordinate[0] = vector.getX();
			vertex[index].coordinate[1] = vector.getY();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Matrix3 translate;

		for (int index = 0; index < 8; index++)
		{
			Vector3 vector;
			vector.setX(vertex[index].coordinate[0]);
			vector.setY(vertex[index].coordinate[1]);
			vector.setZ(vertex[index].coordinate[2]);

			vector.setZ(1);
			vector = translate.Translate(-0.005, 0) * vector;

			vertex[index].coordinate[0] = vector.getX();
			vertex[index].coordinate[1] = vector.getY();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Matrix3 translate;

		for (int index = 0; index < 8; index++)
		{
			Vector3 vector;
			vector.setX(vertex[index].coordinate[0]);
			vector.setY(vertex[index].coordinate[1]);
			vector.setZ(vertex[index].coordinate[2]);

			vector.setZ(1);
			vector = translate.Translate(0.005, 0) * vector;

			vertex[index].coordinate[0] = vector.getX();
			vertex[index].coordinate[1] = vector.getY();
		}
	}

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

