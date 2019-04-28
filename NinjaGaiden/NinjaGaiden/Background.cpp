#include "Background.h"

#define FRAME_WIDTH 32
#define FRAME_HEIGHT 32

int mapWidth = 0;

Background::Background(void)
{
	listTile = NULL;
}

Background::Background(int level)
{
	string fileName;
	string _fileName;
	switch (level)
	{
	case 1:
		fileName = "Resources\\Maps\\Stage3.1-Map.txt";
		break;
	case 2:
		fileName = "Resources\\Maps\\Stage3.2-Map.txt";
		break;
	case 3:
		fileName = "Resources\\Maps\\Stage3.3-Map.txt";
		break;
	}
	

	ifstream map(fileName);

	// ma trận tile
	if (map.is_open())
	{
		int posX, posY;
		int value;
		int countTileWidth, countTileHeight;
		int countWidth, countHeight;
		map >> countTileWidth >> countTileHeight;

		//Load file tile
		switch (level)
		{
		case 1:
			bgSprite = new CSprite(new CTexture("Resources\\Maps\\Stage3.1-Tile.png", countTileWidth, countTileHeight, countTileWidth*countTileHeight), 1);
			break;
		case 2:
			bgSprite = new CSprite(new CTexture("Resources\\Maps\\Stage3.2-Tile.png", countTileWidth, countTileHeight, countTileWidth*countTileHeight), 1);
			break;
		case 3:
			bgSprite = new CSprite(new CTexture("Resources\\Maps\\Stage3.3-Tile.png", countTileWidth, countTileHeight, countTileWidth*countTileHeight), 1);
			break;
		}

		map >> countHeight >> countWidth;

		mapWidth = countWidth * 32;
		int id = 0;
		listTile = new std::map<int, Tile*>();

		Tile* _obj;
		for (int i = countHeight; i > 0; i--)
		{
			for (int j = 0; j < countWidth; j++)
			{
				map >> value;
				posX = (j * FRAME_WIDTH) + FRAME_WIDTH / 2;
				posY = (i * FRAME_HEIGHT) - FRAME_HEIGHT / 2;
				id = i * countWidth + j;
				listTile->insert(pair<int, Tile*>(id, new Tile(value, posX, posY)));
			}
		}

		map.close();
	}

}

void Background::Draw(CCamera *camera)
{
	map<int, Tile*>::iterator _itBegin;
	for (_itBegin = listTile->begin(); _itBegin != listTile->end(); _itBegin++)
	{
		Tile* obj = _itBegin->second;
		D3DXVECTOR2 t = camera->Transform(obj->posX, obj->posY);
		bgSprite->DrawIndex(obj->idTile, t.x, t.y); //Vẽ từng ô tile
	}
}

int Background::getWidth()
{
	return mapWidth;
}

Background::~Background(void)
{
}