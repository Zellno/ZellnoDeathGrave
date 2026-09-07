bool ZDG_IsLeapYear(int year)
{
    if ((year % 400) == 0)
        return true;

    if ((year % 100) == 0)
        return false;

    return (year % 4) == 0;
}

int ZDG_GetDaysInMonth(int year, int month)
{
    if (month == 2)
    {
        if (ZDG_IsLeapYear(year))
            return 29;

        return 28;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;

    return 31;
}

int ZDG_GetUtcTimestamp()
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int days = 0;

    GetYearMonthDayUTC(year, month, day);
    GetHourMinuteSecondUTC(hour, minute, second);

    for (int currentYear = 1970; currentYear < year; currentYear++)
    {
        if (ZDG_IsLeapYear(currentYear))
            days += 366;
        else
            days += 365;
    }

    for (int currentMonth = 1; currentMonth < month; currentMonth++)
        days += ZDG_GetDaysInMonth(year, currentMonth);

    days += day - 1;

    return days * 86400 + hour * 3600 + minute * 60 + second;
}

class ZellnoDeathGrave_Container : Container_Base
{
    static const int ZDG_LIFETIME_SECONDS = 86400;

    protected string m_ZDG_OwnerId;
    protected int m_ZDG_OwnerHash;
    protected bool m_ZDG_IsClaimed;
    protected int m_ZDG_CreatedAtUtc;
    protected bool m_ZDG_ExpiryCheckScheduled;
    protected bool m_ZDG_EmptyCheckScheduled;

    void ZellnoDeathGrave_Container()
    {
        m_ZDG_OwnerId = "";
        m_ZDG_OwnerHash = 0;
        m_ZDG_IsClaimed = false;
        m_ZDG_CreatedAtUtc = 0;
        m_ZDG_ExpiryCheckScheduled = false;
        m_ZDG_EmptyCheckScheduled = false;

        RegisterNetSyncVariableInt("m_ZDG_OwnerHash", int.MIN, int.MAX);
        RegisterNetSyncVariableBool("m_ZDG_IsClaimed");

        SetAllowDamage(false);
    }

    override void EEInit()
    {
        super.EEInit();

        SetAllowDamage(false);

        if (GetGame().IsServer())
            ZDG_ScheduleExpiryCheck(1000);
    }

    bool ZDG_IsClaimed()
    {
        return m_ZDG_IsClaimed;
    }

    bool ZDG_IsOwner(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
            return false;

        string playerId = player.GetIdentity().GetId();

        if (GetGame().IsServer())
        {
            if (m_ZDG_OwnerId == "")
                return false;

            return playerId == m_ZDG_OwnerId;
        }

        if (!m_ZDG_IsClaimed)
            return false;

        return playerId.Hash() == m_ZDG_OwnerHash;
    }

    int ZDG_GetStoredRootCount()
    {
        return GetInventory().AttachmentCount();
    }

    bool ZDG_HasStoredItems()
    {
        return ZDG_GetStoredRootCount() > 0;
    }

    bool ZDG_AssignOwnerId(string ownerId)
    {
        if (!GetGame().IsServer())
            return false;

        if (ownerId == "")
            return false;

        if (m_ZDG_IsClaimed)
            return false;

        m_ZDG_OwnerId = ownerId;
        m_ZDG_OwnerHash = ownerId.Hash();
        m_ZDG_IsClaimed = true;
        m_ZDG_CreatedAtUtc = ZDG_GetUtcTimestamp();

        SetLifetimeMax(ZDG_LIFETIME_SECONDS);
        SetLifetime(ZDG_LIFETIME_SECONDS);
        SetSynchDirty();

        ZDG_ScheduleExpiryCheck(60000);

        Print("[ZDG] Grave owner assigned successfully. Lifetime: 24 hours.");
        return true;
    }

    void ZDG_ScheduleExpiryCheck(int delayMilliseconds)
    {
        if (!GetGame().IsServer())
            return;

        if (m_ZDG_ExpiryCheckScheduled)
            return;

        m_ZDG_ExpiryCheckScheduled = true;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ZDG_CheckExpiry, delayMilliseconds, false);
    }

    void ZDG_CheckExpiry()
    {
        m_ZDG_ExpiryCheckScheduled = false;

        if (!GetGame().IsServer())
            return;

        int nowUtc = ZDG_GetUtcTimestamp();

        if (m_ZDG_CreatedAtUtc <= 0)
            m_ZDG_CreatedAtUtc = nowUtc;

        int ageSeconds = nowUtc - m_ZDG_CreatedAtUtc;
        int remainingSeconds = ZDG_LIFETIME_SECONDS - ageSeconds;

        if (remainingSeconds <= 0)
        {
            Print("[ZDG] Grave expired after 24 hours. Stored roots removed: " + ZDG_GetStoredRootCount().ToString());
            GetGame().ObjectDelete(this);
            return;
        }

        SetLifetimeMax(ZDG_LIFETIME_SECONDS);
        SetLifetime(remainingSeconds);

        ZDG_ScheduleExpiryCheck(60000);
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if (!GetGame().IsServer())
            return;

        if (m_ZDG_EmptyCheckScheduled)
            return;

        m_ZDG_EmptyCheckScheduled = true;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ZDG_DeleteIfEmpty, 750, false);
    }

    void ZDG_DeleteIfEmpty()
    {
        m_ZDG_EmptyCheckScheduled = false;

        if (!GetGame().IsServer())
            return;

        if (ZDG_GetStoredRootCount() != 0)
            return;

        Print("[ZDG] Empty grave removed.");
        GetGame().ObjectDelete(this);
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);

        ctx.Write(m_ZDG_OwnerId);
        ctx.Write(m_ZDG_CreatedAtUtc);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        string ownerId;
        int createdAtUtc;

        if (!ctx.Read(ownerId))
            ownerId = "";

        if (!ctx.Read(createdAtUtc))
            createdAtUtc = ZDG_GetUtcTimestamp();

        m_ZDG_OwnerId = ownerId;
        m_ZDG_OwnerHash = ownerId.Hash();
        m_ZDG_IsClaimed = m_ZDG_OwnerId != "";
        m_ZDG_CreatedAtUtc = createdAtUtc;
        m_ZDG_ExpiryCheckScheduled = false;
        m_ZDG_EmptyCheckScheduled = false;

        SetAllowDamage(false);

        if (GetGame().IsServer())
        {
            SetSynchDirty();
            ZDG_ScheduleExpiryCheck(1000);
        }

        return true;
    }

    override void SetActions()
    {
        super.SetActions();
        RemoveAction(ActionTakeItemToHands);
    }

    override bool CanDisplayCargo()
    {
        return false;
    }

    override bool IsInventoryVisible()
    {
        if (GetGame().IsServer())
            return true;

        PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
        return ZDG_IsOwner(localPlayer);
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        return false;
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        return false;
    }

    override bool IsTakeable()
    {
        return false;
    }
}
