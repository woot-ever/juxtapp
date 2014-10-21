#ifndef CMAP_HPP
#define CMAP_HPP

class CMap {
  public:
    CEditor *editor;
    EditorData *editordata;
    WideString mapname;
    String mapfile;
    int mapseed;
    std::string checksum;
    irr::scene::SMesh *sMapMesh;
    irr::scene::SMesh *sShadeMesh;
    int buffertiles_size;
    irr::core::array<int, irr::core::irrAllocator<int> > update_buffers_to_update;
    irr::core::array<int, irr::core::irrAllocator<int> > map_buffers_to_update;
    ringbuffer<CMap::lightnode, 1024l> *nodemap;
    int nodecount;
    irr::u8 *tilemap;
    irr::u8 *temp_tilemap;
    irr::u32 tilemapheight;//116
    irr::u32 tilemapwidth;//120
    irr::u32 temp_tilemapheight;//124
    irr::u32 temp_tilemapwidth;//128
    int tilemapsize;//132
    int tilesize;//136
    int tilesinrow;//140
    int tilesincolumn;//144
    int temp_tilemapsize;//148
    int temp_tilesinrow;//152
    int temp_tilesincolumn;//156
    irr::f32 tilescale;//160
    irr::f32 tilestep;//164
    irr::f32 temp_tilescale;//168
    irr::f32 temp_tilestep;//172
    irr::f32 worldtilesize;//176
    irr::f32 temp_worldtilesize;//140
    irr::f32 temp_daytime;//144
    bool temp_havewater;//148
    irr::u32 temp_waterheight;//149
    irr::f32 temp_waveper;//153
    irr::s32 temp_waveamp;//157
    irr::video::ITexture *tileset;//161
    irr::u8 *noisemap;//165
    irr::u8 *workmap;//166
    irr::u8 *dirtmap;//167
    irr::u8 *lightmap;//168
    irr::video::SMaterial tilematerial;//169
    irr::video::SMaterial treematerial;//173
    irr::video::SMaterial shadematerial;//177
    irr::video::SMaterial viewmaterial;//181
    bool debugrender;//185
    int buildsounds_played;//186
    irr::video::SColor ambientlight;//190
    irr::video::SColor ambientlight2;//194
    irr::video::SColor fadecolor;//198
    Line collision_lines[128];
    irr::f32 lighten;
    int opendoorsound_time;
    irr::core::array<CParallax*, irr::core::irrAllocator<CParallax*> > parallaxmaps;
    irr::video::SMaterial bordermaterial;
    irr::video::S3DVertex bordervertices[4];
    irr::u16 borderindices[6];
    irr::video::SColor color_tile_ground;
    irr::video::SColor color_tile_stone;
    irr::video::SColor color_tile_thickstone;
    irr::video::SColor color_tile_bedrock;
    irr::video::SColor color_tile_gold;
    irr::video::SColor color_tile_tree;
    irr::video::SColor color_tile_castle;
    irr::video::SColor color_tile_castle_back;
    irr::video::SColor color_tile_door_1;
    irr::video::SColor color_tile_door_2;
    irr::video::SColor color_tile_ladder;
    irr::video::SColor color_tile_ladder_ground;
    irr::video::SColor color_tile_ladder_castle;
    irr::video::SColor color_tile_ladder_wood;
    irr::video::SColor color_tile_ground_back;
    irr::video::SColor color_tile_empty;
    irr::video::SColor color_bluetent;
    irr::video::SColor color_redtent;
    irr::video::SColor color_blueoutpost;
    irr::video::SColor color_redoutpost;
    irr::video::SColor color_catapult;
    irr::video::SColor color_heart;
    irr::video::SColor color_tile_gold_bulion_1;
    irr::video::SColor color_tile_gold_bulion_2;
    irr::video::SColor color_tile_spikes;
    irr::video::SColor color_tile_spikes_ground;
    irr::video::SColor color_tile_spikes_castle;
    irr::video::SColor color_tile_spikes_wood;
    irr::video::SColor color_tile_bridge_1;
    irr::video::SColor color_tile_bridge_2;
    irr::video::SColor color_tile_bridge_1_back;
    irr::video::SColor color_tile_bridge_2_back;
    irr::video::SColor color_tile_grass;
    irr::video::SColor color_tile_rubble;
    irr::video::SColor color_tile_wood;
    irr::video::SColor color_tile_wood_back;
    irr::core::map<int, unsigned char> supertiles;
    irr::core::map<int, unsigned char> resourcetiles;
    int maptilepacketsize;
    bool firstautosave;
    CPhysicsWorld *blockphysics;
    irr::core::array<int, irr::core::irrAllocator<int> > collapselist;
    irrklang::ISound *collapsesound;
    bool settile_physics;
    bool settile_supertiles;
    irr::u8 settile_team;
    WideString settile_player;
    CNetVariable<float, 19u, 10000> daytime;
    int old_daytime;
    irr::f32 windsin;
    irr::core::array<CMap::Impostor*, irr::core::irrAllocator<CMap::Impostor*> > impostors;
    irr::video::SMaterial MaterialShadow;
    irr::video::ITexture *viewtexture;
    int last_collapsesize_msg;
    std::vector<CMap::Dungeon, std::allocator<CMap::Dungeon> > dungeons;
    CMapHighLevel *HighLevelMap;
    irr::u8 *previewMinimap;
    CMapWater *water;

    CMap(void);
    ~CMap(int);
    void Update(void);
    void Render(void);
    void RenderGUI(void);
    void LoadMap(const irr::c8 *, bool);
    void GenerateMap(int, int, int, const char *);
    bool hasMinimumResources(void);
    void SaveMap(const irr::c8 *);
    void MakeMiniMap(void);
    void EditMiniMap(int, int, irr::u8);
    bool SerializeMinimap(CBitStream &);
    static bool UnserializeMinimap(irr::video::IImage **, CBitStream &);
    int GetMapPNG(irr::c8 *&, irr::u32 &, bool, bool);
    CEditor * GetEditor(void);
    static bool StartEditor(void);
    static bool StopEditor(void);
    WideString GetMapName(void);
    void DebugRender(void);
    void CreateBuffers(void);
    void CreateBuffer(int, int, irr::scene::SMeshBuffer *, irr::scene::SMeshBuffer *);
    void UpdateBuffer(int, int, irr::scene::SMeshBuffer *, irr::scene::SMeshBuffer *);
    void UpdateBufferAtTile(int, int, irr::scene::SMesh *, bool);
    void UpdateMapColors(void);
    void UpdateTileBuffersAt(Vec2f, irr::f32);
    void SetTile(int, int, irr::u8);
    void SetTile(Vec2f, irr::u8);
    void FullLightPass_recurse_fill_blank(void);
    void SetListenerInfo(ListenerInfo *, Vec2f);
    bool isPointVisibleInFOV(irr::f32, irr::f32);
    void PutEffect(Vec2f, float, int);
    void PopDebree(Vec2f, int, irr::f32, irr::f32, Vec2f, irr::f32);
    void PopSparks(Vec2f, int, irr::f32, irr::f32, Vec2f, irr::f32, irr::video::SColor);
    void Restart(void);
    void removeAllMapObjects(void);
    irr::u8 getTile(Vec2f);
    irr::u8 getTile(irr::core::position2di);
    irr::u8 getTile(int);
    void server_SetTile(Vec2f, irr::u8);
    void destroyTile(Vec2f, irr::u8);
    Vec2f getTileWorldPosition(Vec2f);
    Vec2f getTileWorldPosition(irr::core::position2di);
    Vec2f getTileWorldPosition(int);
    irr::core::position2di getTileSpacePosition(Vec2f);
    irr::core::position2di getTileSpacePosition(int);
    int getTileOffset(Vec2f);
    int getTileOffset(irr::core::position2di);
    bool isTileSolid(Vec2f);
    bool isTileSolid(irr::core::position2di);
    bool isTileSolid(irr::u8);
    bool isTileWalkable(irr::core::position2di, bool);
    bool isTileWalkableOnTop(irr::core::position2di);
    bool isTileGround(irr::u8);
    bool isTileGroundBack(irr::u8);
    bool isTileCastle(irr::u8);
    bool isTileCastleBack(irr::u8);
    bool isTileStone(irr::u8);
    bool isTileThickStone(irr::u8);
    bool isTileBedrock(irr::u8);
    bool isTileLadder(irr::u8);
    bool isTileChoppableTree(irr::u8);
    bool isTileChoppedTree(irr::u8);
    bool isTileTree(irr::u8);
    bool isTileDoor(irr::u8);
    bool isTileOpenDoor(irr::u8);
    bool isTileDoorClosed(irr::u8, int);
    bool isTileDestructible(irr::u8);
    bool isTileGold(irr::u8);
    bool isTileGoldBulion(irr::u8, int);
    bool isTileGroundStuff(irr::u8);
    bool isTileBackground(irr::u8);
    bool isTileBackgroundNonEmpty(irr::u8);
    bool isTileMinimapEdge(irr::u8);
    bool isTileMinimapBackEdge(irr::u8);
    bool isTileLight(irr::u8);
    bool isTileSpikes(irr::u8);
    bool isTileBridge(irr::u8, int);
    bool isTileBridgeDestruction(irr::u8);
    bool isTileBridgeOpen(irr::u8, int);
    bool isTileBridgeClosed(irr::u8, int);
    bool isTileSupport(irr::u8);
    bool isTileSolidButNotOpenable(irr::u8);
    bool isTileSolidButNotDoor(irr::u8);
    bool isTileSolidButNotBridge(irr::u8);
    bool isTileExplodable(irr::u8);
    bool isTileConstruction(irr::u8);
    bool isTileRoom(irr::u8);
    bool isTileLightPass(irr::u8);
    bool isTileWood(irr::u8);
    bool isTileWoodBack(irr::u8);
    bool isTileRubble(irr::u8);
    bool isTileGrass(irr::u8);
    bool isTileGroundGrass(int);
    bool isTileSolidWithBridge(irr::u8);
    bool isTileSolidWithoutBridge(irr::u8);
    bool isTilePlatform(irr::u8);
    bool isTileSlope(irr::u8);
    bool isTileLeftSlope(int);
    bool isTileRightSlope(int);
    bool isTileUnderGround(int);
    bool isTileWet(int);
    irr::f32 getTileCost(irr::core::position2di, irr::core::position2di);
    irr::core::position2di getTilePositionClosestTile(Vec2f, irr::u8);
    void DestroyTile(Vec2f, bool, bool, bool, bool, bool, bool, bool);
    bool resolve_penetrations(Vec2f &, Vec2f &, float, float, int, Vec2f &, bool (CMap::*)(
    CMap * const, irr::u8));
    bool resolve_penetrations_ray(Vec2f &, Vec2f &, float, float, Vec2f &, bool (CMap::*)(
    CMap * const, irr::u8));
    void gather_lines(Vec2f &, Vec2f &, float, bool (CMap::*)(CMap * const, irr::u8));
    void DrawTile(Vec2f, irr::u8, irr::video::SColor, irr::f32, bool);
    void MakeTileLighting(int, int, irr::video::S3DVertex *);
    void LightPass(int, int, int);
    void FullLightPass(int, int, int, int);
    void getTileVariation(int, int, irr::u8 &, irr::u8 &, bool &, bool &, bool &, bool &,
    bool &, bool &, bool &);
    bool OpenDoor(Vec2f, irr::f32, irr::f32, irr::f32, irr::f32, int);
    bool OpenBridge(Vec2f, irr::f32, int, bool, bool);
    void RenderParallax(bool, bool);
    void RenderMapBorders(void);
    void RenderTree(CMap::Impostor *);
    void RenderGoldSpark(int, int, int);
    bool Serialize(CBitStream &);
    bool Unserialize(CBitStream &, bool);
    bool CommitUnserialize(bool);
    void SendMapTile(irr::u32, irr::u8);
    bool recdMapTile(CBitStream &);
    void TileEffects(Vec2f, irr::u8, irr::u8, int);
    bool findRaySolid(Vec2f, Vec2f, int, int &, Vec2f &);
    bool MakeRoom(irr::u8, Vec2f);
    void InitMap(void);
    void MakeDirtNatural(void);
    int StartTileCollapse(int);
    int FloodMark(int, int &, int);
    int FloodCollapse(int, int &, int, int);
    CPhysicsBody * CollapseTile(int);
    int getSpikeType(irr::core::position2di);
    CPhysicsBody * CreateTileBody(irr::u8, int);
    void DeleteTileBody(int, int);
    bool has_support_below(int, int);
    bool can_physics_build(irr::u8, irr::u8, int);
    bool supporting_blocks(int, int, int, int &, int, int &);
    bool recdBodyTile(CBitStream &);
    bool recdBodyTileDelete(CBitStream &);
    void ChangeSpecialCase(irr::u8 &, Vec2f, int);
    void InitImpostors(void);
    void UpdateImpostors(void);
    void UpdateImpostors(int, int, irr::u8, irr::u8);
    CMap::Impostor * getImpostorAt(int, int, int);
    irr::f32 distanceToTent(Vec2f, irr::u8);
    bool doCastRay(int, int, int &, int &, bool (CMap::*)(CMap * const, irr::u8));
    bool rayCastSolid(Vec2f, Vec2f &);
    bool rayCastForExplosion(Vec2f, Vec2f &);
    bool rayCastForAttack(Vec2f, Vec2f &);
    bool CheckRoomGrief(int, irr::u8);
    void RenderShadows(void);
    irr::core::vector3df getLightAtPosWithoutLightmap(Vec2f);
    void setVerticeLight(irr::video::S3DVertex &);
    irr::video::SColor getColorLight(Vec2f);
    bool isDay(void);
    void SetDayTime(irr::f32);
    irr::f32 getTime(void);
    irr::f32 getDayStartTime(void);
    irr::f32 getDayEndTime(void);
    int getLandHeightAtX(int);
    int getLandYAtX(int);
    bool isBelowLand(Vec2f);
    void SetTileFromColor(int, irr::video::SColor);
    bool isAreaFreeOnGround(irr::core::position2di, irr::core::position2di);
    bool isInWater(Vec2f);
    bool isInWater(int);
    void SplashEffect(Vec2f, Vec2f);
    bool isMapFullInWater(void);
    void setWaterLevel(int);
    void setWaterWavePeriod(irr::f32);
    void setWaterWaveAmplitude(int);
}

#endif