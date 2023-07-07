#pragma once
#include <pch.h>
#include <base.h>

#define VectorCopy(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}

struct spread_info
{
    unsigned int random_seed;
    int recoil;
    float gtime;
    float prevtime;
    float brokentime; // This is only supposed to be set to zero when you buy the sg550 or the g3sg1
    // not when you reload, switch weapons or pick up a weapon, this is do to the
    // cs bugs for these guns (valve fix your code please)
    float spreadvar;
    float recoiltime;
    bool firing;
    int WeaponState;
    int prcflags;
};

struct sMe
{
    int iClip;
    int iHealth;
    int iArmor;
    int iKills;
    int iDeaths;
    int iHs;
    int iMoney;

    int iFOV;
    float pmVelocity[3];
    float punchangle[3];
    float pmEyePos[3];
    int pmFlags;
    float viewAngles[3];
    float sin_yaw, minus_cos_yaw;
    bool inZoomMode;
    int pmMoveType;
    int team;
    struct cl_entity_s* ent;
    int entindex;
    bool alive;
    spread_info spread;
    //void DoBunnyHop(struct usercmd_s* usercmd);
};

class PlayerInfo
{
protected:
    friend class VecPlayers;
    void init(int _entindex)
    {
        team = 2;
        entinfo.name = (char*)"\\missing-name\\";
        entinfo.model = (char*)"missing-model";
        alive = false;
        entindex = _entindex;
        distance = 1000.0;
        visible = 0;
        strcpy(m_weapon, "N-A");
        m_updated = false;
        bGotHead = false;
        fixHbAim = false;
        canAim = false;
        bDrawn = false;
    }
private:
    hud_player_info_s entinfo;

public:
    void updateEntInfo()
    {
        Base::Data::m_hw->Engfuncs->pfnGetPlayerInfo(entindex, &entinfo);
        if (!entinfo.name) { entinfo.name = (char*)"\\missing-name\\"; }
        if (!entinfo.model) { entinfo.model = (char*)"unknown model"; }
    }
    const char* getName() const { return entinfo.name; }

    int    team;
    int    iInfo;
    float  distance;
    bool    visible;
    float  fovangle;   // minimum fov a player is in
    vec3_t vHitbox;
    bool bGotHead;
    bool fixHbAim;
    int canAim;
    bool bDrawn;

    void setAlive() { alive = true; }
    void setDead() { alive = false; }
    bool isAlive() { return alive != false; }

    struct cl_entity_s* getEnt() { return Base::Data::m_hw->Engfuncs->GetEntityByIndex(entindex); }
    // position update queries
    enum { UPDATE_MISSING = 0, UPDATE_ADDENT = 1, UPDATE_SOUND_RADAR = 2 };
    // weapon update:
    void updateSoundRadar(void) { m_lastUpdateType = UPDATE_SOUND_RADAR; }
    const char* getWeapon() { return m_weapon; }
    void setWeapon(const char* newname)
    {
        register int len = strlen(newname);
        if (len && len < 30) { strcpy(m_weapon, newname); }
    }
    // position update reporting
    void   updateClear()
    {
        bDrawn = false;
        m_lastUpdateType = UPDATE_MISSING;
    }
    void SetOrigin(const float* neworg)
    {
        VectorCopy(neworg, m_origin);
    }
    void   updateAddEntity(const float* neworg)
    {
        if (alive)
        {
            m_lastUpdateType = UPDATE_ADDENT;
            m_lastUpdateTime = (double)timeGetTime() / 1000.0;

            VectorCopy(neworg, m_origin);
        }
    }

    bool   isUpdated() { return m_lastUpdateType != UPDATE_MISSING; }
    bool   isUpdatedAddEnt() { return m_lastUpdateType == UPDATE_ADDENT; }
    int    updateType() { return m_lastUpdateType; }
    const float* origin() { return m_origin; }
    float  timeSinceLastUpdate() { return (float)((double)timeGetTime() / 1000.0 - m_lastUpdateTime); }

private:
    int     m_lastUpdateType;
    double  m_lastUpdateTime;
    float   m_origin[3];
    char    m_weapon[32];
    bool    m_updated;

    bool alive;
    int entindex;

public:
    PlayerInfo() { init(0); }
};



enum { MAX_VPLAYERS = 36 };
class VecPlayers
{
private:
    PlayerInfo* players;
public:
    ~VecPlayers() { delete[] players; }
    VecPlayers()
    {
        players = new PlayerInfo[MAX_VPLAYERS];
        for (int i = 0; i < MAX_VPLAYERS; i++) { players[i].init(i); }
    }

    inline PlayerInfo& operator [] (unsigned int i)
    {
        if (i >= MAX_VPLAYERS) { return players[0]; }
        else { return players[i]; }
    }

    inline unsigned int size() { return MAX_VPLAYERS; }
};

extern VecPlayers vPlayers;
extern sMe me;