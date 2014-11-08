#include "enet/enet.h"

class CPlayerManager {
  public:
    irr::core::map<int, TeamList*> teams;
    irr::core::array<Vote*, irr::core::irrAllocator<Vote*> > votes;
    int lastvote_time;
    int lastvote_minimum_time;
    static int server_votepacket_size;
    static int client_votepacket_size;
    irr::core::array<CPlayer*, irr::core::irrAllocator<CPlayer*> > players;

    irr::core::array<historical_player*, irr::core::irrAllocator<historical_player*> > historical_players;
    int playerslist_y;

    CPlayerManager(void);
    ~CPlayerManager(int);
    CPlayer * getPlayer(ENetPeer *);
    CPlayer * getPlayer(irr::s32);
    CPlayer * GetPlayerByControls(CControls *);
    CPlayer * getPlayerBySessionID(enet_uint32);
    CPlayer * getPlayerByHost(enet_uint32);
    CPlayer * getPlayerByNetworkID(enet_uint32);
    bool playerExists(CPlayer *);
    CPlayer * getPlayerByUsername(const char *);
    CPlayer * getPlayerByCharname(const char *);
    CPlayer * AddPlayer(ENetPeer *, CPlayer *);
    void RemovePlayer(ENetPeer *);
    void RemovePlayer(CPlayer *);
    void DumpToConsole(void);
    void Update(void);
    void KillemAll(void);
    void RespawnAll(bool);
    irr::s32 getPlayersNum(void);
    irr::s32 getHumanPlayersNum(void);
    irr::s32 getHumanPlayersNum_NotSpectator(void);
    irr::s32 getHumanPlayersNum_Spectator(void);
    void Sort(void);
    int PlayersPartition(irr::core::array<CPlayer*, irr::core::irrAllocator<CPlayer*> > &,
    int, int);
    void PlayersQuicksort(irr::core::array<CPlayer*, irr::core::irrAllocator<CPlayer*> > &,
    int, int);
    String getPlayerName(ENetPeer *);
    irr::s32 getTeamSize(irr::s16);
    irr::s32 getLowestTeamSize(void);
    int getSmallestTeam(void);
    int getPlayersOnTeam(int);
    irr::s32 getTeamPlayersPlaying(int);
    void Render(void);
    bool teamsHaveAtleastPlayers(int);
    bool teamPlayerDifferFromPlayers(void);
	void CastVote(irr::u8, irr::u16, const wchar_t *);
    void CastVote(bool);
    void RenderVotes(void);
    bool recdVote(CBitStream &, ENetPeer *);
    void VotePass(int, int, int, Vote *);
    void CalculateVotePassNumber(int, int, int, CPlayer *, int &);
    void client_SendMarkPlayer(enet_uint32, irr::u8);
    bool server_RecdMarkPlayer(CBitStream &, ENetPeer *);
    void CheckGrieferKick(enet_uint32, int, CPlayer *);
    void Kick(CPlayer *, int, int);
    void MakeUniqueName(String &, CPlayer *, int, bool);
    void KickForStuff(void);
    void SwapTeam(CPlayer *);
    void BalanceTeams(void);
    historical_player * getHistoricalPlayer(const char *);
    void MakePartyList(CPlayer *,
    irr::core::array<CPlayer*, irr::core::irrAllocator<CPlayer*> > &);
}
