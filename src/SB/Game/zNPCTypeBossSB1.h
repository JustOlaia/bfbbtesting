#ifndef ZNPCTYPEBOSSSB1_H
#define ZNPCTYPEBOSSSB1_H

#include "zNPCTypeBoss.h"
#include "zNPCTypeBossPlankton.h"  // zNPCBPlankton: the Robo-Plankton boss NPC
#include "zNPCGoalCommon.h"

#include "xFX.h"

struct zNPCB_SB1 : zNPCBoss
{
    xModelInstance* m_subModels[6]; // 0x2b4
    xModelTag m_leftArmTags[4];    // 0x2CC
    xModelTag m_rightArmTags[4];   // 0x34C
    xModelTag m_feetTags[4];       // 0x3CC
    F32 m_tauntTimer;              // 0x44C
    zEnt* m_armColl[2];            // 0x450
    zEnt* m_bodyColl;              // 0x458
    zEnt* m_armTgt[2];             // 0x45C
    xFXRing* m_stompRing[16];      // 0x464
    bool attacking;                // 0x4A4
    F32 attack_delay;              // 0x4A8

    // New fields
    zNPCBPlankton* plankton;    // 0x2E4
    F32 m_rumbleStompTimer; // counts up during rumble/stomp loop windows
    bool m_flexing;         // true while boss is in forced flex via HoldUpDude
    S32 m_loopCount;        // how many 16s rumble/stomp loops have completed

    zNPCB_SB1(S32 myType);
    void Init(xEntAsset*);
    void scan_cronies();
    void SelfSetup();
    void Reset();
    U32 AnimPick(S32 gid, en_NPC_GOAL_SPOT gspot, xGoal* goal);
    void Process(xScene* xscn, F32 dt);
    void NewTime(xScene* xscn, F32 dt);
    F32 AttackTimeLeft();
    void HoldUpDude();
    void ThanksImDone();
};

// Unchanged from original
struct zNPCGoalBossSB1Idle : zNPCGoalCommon
{
    F32 timeInGoal;

    zNPCGoalBossSB1Idle(S32 goalID) : zNPCGoalCommon(goalID)
    {
    }

    S32 Enter(F32 dt, void* updCtxt);
    S32 Process(en_trantype* trantype, float dt, void* ctxt, xScene* scene);
};

// Unchanged from original
struct zNPCGoalBossSB1Taunt : zNPCGoalCommon
{
    F32 timeInGoal;

    zNPCGoalBossSB1Taunt(S32 goalID) : zNPCGoalCommon(goalID)
    {
    }

    S32 Enter(F32 dt, void* updCtxt);
    S32 Process(en_trantype* trantype, float dt, void* ctxt, xScene* scene);
};

// Unchanged from original
struct zNPCGoalBossSB1Stomp : zNPCGoalCommon
{
    F32 timeInGoal;

    zNPCGoalBossSB1Stomp(S32 goalID) : zNPCGoalCommon(goalID)
    {
    }

    S32 Enter(F32 dt, void* updCtxt);
    S32 Process(en_trantype* trantype, float dt, void* ctxt, xScene* scene);
};

// Unchanged from original
struct zNPCGoalBossSB1Smash : zNPCGoalCommon
{
    F32 timeInGoal;

    zNPCGoalBossSB1Smash(S32 goalID) : zNPCGoalCommon(goalID)
    {
    }

    S32 Enter(F32 dt, void* updCtxt);
    S32 Exit(F32 dt, void* updCtxt);
    S32 Process(en_trantype* trantype, F32 dt, void* ctxt, xScene* scene);
};

// Unchanged from original
struct zNPCGoalBossSB1Deflate : zNPCGoalCommon
{
    F32 timeInGoal;          // 0x4C
    RwV3d morphVertBuf[600]; // 0x50
    RwV3d* targetVec;        // 0x1C70
    RwV3d* modelVec;         // 0x1C74
    RpGeometry* modelGeom;   // 0x1C78
    S32 morphVertCount;      // 0x1C7C
    F32 morphInvTime;        // 0x1C80

    zNPCGoalBossSB1Deflate(S32 goalID) : zNPCGoalCommon(goalID)
    {
    }

    S32 Enter(F32 dt, void* updCtxt);
    S32 Exit(F32 dt, void* updCtxt);
    S32 Process(en_trantype* trantype, float dt, void* ctxt, xScene* scene);
};

// New - handles the random rumble/stomp loop for 16 seconds.
// First completion transitions to Flex.
// Second completion transitions to original Idle (arm attacks open up naturally).
// After that, used again in the ending loop between Smash attacks.
struct zNPCGoalBossSB1RumbleStompLoop : zNPCGoalCommon
{
    F32 timeInGoal;
    S32 lastAttack; // 0 = rumble was last, 1 = stomp was last, -1 = none yet

    zNPCGoalBossSB1RumbleStompLoop(S32 goalID) : zNPCGoalCommon(goalID)
    {
        lastAttack = -1;
    }

    S32 Enter(F32 dt, void* updCtxt);
    S32 Process(en_trantype* trantype, float dt, void* ctxt, xScene* scene);
};

// New - boss flexes indefinitely, does not face player.
// Entered via HoldUpDude(), exited via ThanksImDone().
struct zNPCGoalBossSB1Flex : zNPCGoalCommon
{
    F32 timeInGoal;

    zNPCGoalBossSB1Flex(S32 goalID) : zNPCGoalCommon(goalID)
    {
    }

    S32 Enter(F32 dt, void* updCtxt);
    S32 Process(en_trantype* trantype, float dt, void* ctxt, xScene* scene);
};

// New - boss plays AttackRumble anim. Rock-fall hazard hookup goes here later.
struct zNPCGoalBossSB1Rumble : zNPCGoalCommon
{
    F32 timeInGoal;

    zNPCGoalBossSB1Rumble(S32 goalID) : zNPCGoalCommon(goalID)
    {
    }

    S32 Enter(F32 dt, void* updCtxt);
    S32 Process(en_trantype* trantype, float dt, void* ctxt, xScene* scene);
};

xAnimTable* ZNPC_AnimTable_BossSB1();

#endif
