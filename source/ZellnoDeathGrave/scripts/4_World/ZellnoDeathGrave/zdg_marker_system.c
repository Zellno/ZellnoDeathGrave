class ZDG_ClientMarker
{
    vector Position;

    void ZDG_ClientMarker(vector position)
    {
        Position = position;
    }
}

class ZDG_ClientMarkerStore
{
    protected static ref array<ref ZDG_ClientMarker> s_Markers;

    protected static void Ensure()
    {
        if (!s_Markers)
            s_Markers = new array<ref ZDG_ClientMarker>;
    }

    static void Clear()
    {
        Ensure();
        s_Markers.Clear();
    }

    static void Add(vector position)
    {
        Ensure();

        foreach (ZDG_ClientMarker marker : s_Markers)
        {
            if (marker && marker.Position == position)
                return;
        }

        s_Markers.Insert(new ZDG_ClientMarker(position));
    }

    static void Remove(vector position)
    {
        Ensure();

        for (int index = s_Markers.Count() - 1; index >= 0; index--)
        {
            ZDG_ClientMarker marker = s_Markers.Get(index);

            if (!marker || marker.Position == position)
                s_Markers.Remove(index);
        }
    }

    static void Draw(MapWidget mapWidget)
    {
        Ensure();

        if (!mapWidget)
            return;

        foreach (ZDG_ClientMarker marker : s_Markers)
        {
            if (!marker)
                continue;

            mapWidget.AddUserMark(marker.Position, ZDG_MarkerConstants.MARKER_NAME, ARGB(255, 200, 30, 30), ZDG_MarkerConstants.MARKER_ICON);
        }
    }
}

class ZDG_MarkerServer
{
    protected static ref array<ZellnoDeathGrave_Container> s_Graves;

    protected static void EnsureRegistry()
    {
        if (!s_Graves)
            s_Graves = new array<ZellnoDeathGrave_Container>;
    }

    static bool IsEnabled()
    {
        if (!GetGame() || !GetGame().IsServer())
            return false;

        ZDG_MarkerSettings settings = ZDG_MarkerSettingsManager.Get();
        return settings && settings.EnableDeathMarker;
    }

    static void RegisterGrave(ZellnoDeathGrave_Container grave)
    {
        if (!GetGame() || !GetGame().IsServer() || !grave)
            return;

        EnsureRegistry();

        foreach (ZellnoDeathGrave_Container registered : s_Graves)
        {
            if (registered == grave)
                return;
        }

        s_Graves.Insert(grave);
    }

    static void UnregisterGrave(ZellnoDeathGrave_Container grave)
    {
        EnsureRegistry();

        for (int index = s_Graves.Count() - 1; index >= 0; index--)
        {
            ZellnoDeathGrave_Container registered = s_Graves.Get(index);

            if (!registered || registered == grave)
                s_Graves.Remove(index);
        }
    }

    protected static PlayerBase FindOnlineOwner(string ownerId)
    {
        if (ownerId == "")
            return null;

        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);

            if (player && player.GetIdentity() && player.GetIdentity().GetId() == ownerId)
            {
                return player;
            }
        }

        return null;
    }

    protected static void Send(
        PlayerBase player,
        int eventType,
        vector position
    )
    {
        if (!player || !player.GetIdentity())
            return;

        GetGame().RPCSingleParam(player, ZDG_MarkerConstants.RPC_MARKER_EVENT, new Param2<int, vector>(eventType, position), true, player.GetIdentity());
    }

    static void NotifyGraveCreated(ZellnoDeathGrave_Container grave)
    {
        if (!grave || !IsEnabled())
            return;

        PlayerBase owner = FindOnlineOwner(grave.ZDG_GetOwnerId());

        if (!owner)
            return;

        Send(owner, ZDG_MarkerConstants.EVENT_ADD, grave.GetPosition());
        Print("[ZDG] Private death marker sent to grave owner.");
    }

    static void NotifyGraveRemoved(ZellnoDeathGrave_Container grave)
    {
        if (!grave || !IsEnabled())
            return;

        PlayerBase owner = FindOnlineOwner(grave.ZDG_GetOwnerId());

        if (!owner)
            return;

        Send(owner, ZDG_MarkerConstants.EVENT_REMOVE, grave.GetPosition());
        Print("[ZDG] Private death marker removal sent to grave owner.");
    }

    static void SyncPlayer(PlayerBase player)
    {
        if (!GetGame() || !GetGame().IsServer() || !player || !player.GetIdentity())
        {
            return;
        }

        EnsureRegistry();

        Send(player, ZDG_MarkerConstants.EVENT_CLEAR, "0 0 0");

        if (!IsEnabled())
        {
            Print("[ZDG] Private death markers disabled by configuration.");
            return;
        }

        string ownerId = player.GetIdentity().GetId();
        int markerCount = 0;

        for (int index = s_Graves.Count() - 1; index >= 0; index--)
        {
            ZellnoDeathGrave_Container grave = s_Graves.Get(index);

            if (!grave)
            {
                s_Graves.Remove(index);
                continue;
            }

            if (grave.ZDG_GetOwnerId() != ownerId)
                continue;

            Send(player, ZDG_MarkerConstants.EVENT_ADD, grave.GetPosition());
            markerCount++;
        }

        Print("[ZDG] Private death markers synchronized: " + markerCount.ToString());
    }
}

modded class PlayerBase
{
    override void OnRPC(
        PlayerIdentity sender,
        int rpc_type,
        ParamsReadContext ctx
    )
    {
        super.OnRPC(sender, rpc_type, ctx);

        if (rpc_type != ZDG_MarkerConstants.RPC_MARKER_EVENT || !GetGame().IsClient())
        {
            return;
        }

        Param2<int, vector> markerEvent = new Param2<int, vector>(0, "0 0 0");

        if (!ctx.Read(markerEvent))
        {
            Print("[ZDG] Death marker RPC could not be read.");
            return;
        }

        if (markerEvent.param1 == ZDG_MarkerConstants.EVENT_CLEAR)
        {
            ZDG_ClientMarkerStore.Clear();
            return;
        }

        if (markerEvent.param1 == ZDG_MarkerConstants.EVENT_ADD)
        {
            ZDG_ClientMarkerStore.Add(markerEvent.param2);
            return;
        }

        if (markerEvent.param1 == ZDG_MarkerConstants.EVENT_REMOVE)
            ZDG_ClientMarkerStore.Remove(markerEvent.param2);
    }
}
