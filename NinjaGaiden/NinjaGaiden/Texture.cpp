#include "Texture.h"

CTexture::CTexture(const char* _fileName, int cols, int rows, int count)
{
	Cols = cols;
	Rows = rows;
	Count = count;
	FileName = _fileName;
	this->Load();
}

CTexture::CTexture(const CTexture &texture)
{
	this->FileName = texture.FileName;
	this->Size = texture.Size;
	this->Cols = texture.Cols;
	this->Rows = texture.Rows;
	this->Count = texture.Count;
	this->FrameHeight = texture.FrameHeight;
	this->FrameWidth = texture.FrameWidth;
	this->Load();
}

CTexture::~CTexture()
{
	if (this->texture != NULL)
		this->texture->Release();
}

void CTexture::Draw(int x, int y)
{
	D3DXVECTOR3 position((float)x, (float)y, 0);
	G_SpriteHandler->Draw(texture, &Size, NULL, &position, 0xFFFFFFFF);
}

void CTexture::Load()
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(FileName, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	this->Size = s;

	FrameWidth = info.Width / Cols;
	FrameHeight = info.Height / Rows;

	if (result != D3D_OK)
	{
		/*GLMessage("Can not load texture");
		GLTrace("[texture.h] Failed to get information from image file [%s]", FileName);*/
		OutputDebugString(FileName);
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		G_Device,
		FileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), //color
		&info,
		NULL,
		&texture
	);

	if (result != D3D_OK)
	{
		/*GLMessage("Can not load texture");
		GLTrace("[texture.h] Failed to create texture from file '%s'", FileName);*/
		return;
	}
}