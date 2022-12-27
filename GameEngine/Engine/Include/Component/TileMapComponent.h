#pragma once

#include "PrimitiveComponent.h"
#include "Tile.h"

class CTileMapComponent :
    public CPrimitiveComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CTileMapComponent();
    CTileMapComponent(const CTileMapComponent& component);
    virtual ~CTileMapComponent();

protected:
    std::string                         m_SceneName;
    class CTileMapConstantBuffer*       m_TileMapCBuffer;
    class CStructuredBuffer*            m_TileInfoBuffer;
    std::vector<CTile*>                 m_vecTile;
    std::vector<TileInfo>               m_vecTileInfo;
    CSharedPtr<class CMesh>             m_TileMesh;
    CSharedPtr<class CMaterial>         m_TileMaterial;
    CSharedPtr<class CTexture>          m_TileBackTexture;
    ETileShape                          m_Shape;
    int                                 m_CountX;
    int                                 m_CountY;
    int                                 m_Count;
    int                                 m_TileInfoCount;
    int                                 m_RenderCount;
    Vector2                             m_TileSize;
    Vector4                             m_TileTypeColor[(int)ETileOption::End];
    std::vector<Animation2DFrameData>   m_vecTileFrame;

    // EditorMode에서 편집 시 마우스로 선택된 타일을 저장하기 위한 멤버변수
    class CTile*                        m_EditorMouseOnTile;

public:
    class CMaterial* GetTileMaterial()  const
    {
        return m_TileMaterial;
    }

    const std::string& GetSceneName()   const
    {
        return m_SceneName;
    }

    int GetCountX() const
    {
        return m_CountX;
    }

    int GetCountY() const
    {
        return m_CountY;
    }

    int GetCount() const
    {
        return m_Count;
    }

    ETileShape GetShape()   const
    {
        return m_Shape;
    }

    const Vector2& GetTileSize()    const
    {
        return m_TileSize;
    }

    CTexture* GetTileTexture()  const;

public:
    void SetTileBackTexture(class CTexture* Texture);
    void SetTileBackTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
    void SetTileBackTextureFullPath(const std::string& Name, const TCHAR* FullPath);
    void SetTileBackTextureArray(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);
    void SetTileBackTextureArrayFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);

    void SetTileMesh(const std::string& Name);
    void SetTileMesh(class CMesh* Mesh);
    void SetTileMaterial(const std::string& Name);
    void SetTileMaterial(class CMaterial* Material);
    void SetTileTexture(class CTexture* Texture);
    void SetTileTexture(int CountX, int CountY, const Vector2& TileSize, const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
    void SetTileTextureFullPath(int CountX, int CountY, const Vector2& TileSize, const std::string& Name, const TCHAR* FullPath);
    void SetTileTextureArray(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);
    void SetTileTextureArrayFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
    void SetTileBaseColor(const Vector4& Color);

    void SetEditorMouseOnTile(int Index);

    void CreateTile(ETileShape Shape, int CountX, int CountY, const Vector2& TileSize);

public:
    void ChangeTileFrame(int Frame);
    void ChangeTileOption(ETileOption Option);
    void ChangeTileFrame(int Index, int Frame);
    void ChangeTileOption(int Index, ETileOption Option);

public:
    int GetTileIndexX(const Vector2& Pos);
    int GetTileIndexX(const Vector3& Pos);
    int GetTileIndexY(const Vector2& Pos);
    int GetTileIndexY(const Vector3& Pos);
    int GetTileIndex(const Vector2& Pos);
    int GetTileIndex(const Vector3& Pos);

    CTile* GetTile(const Vector2& Pos);
    CTile* GetTile(const Vector3& Pos);
    CTile* GetTile(int X, int Y);
    CTile* GetTile(int Index);

private:
    int GetTileRenderIndexX(const Vector3& Pos);
    int GetTileRenderIndexY(const Vector3& Pos);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CTileMapComponent* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

