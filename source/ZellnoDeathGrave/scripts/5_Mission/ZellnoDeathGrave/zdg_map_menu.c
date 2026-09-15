modded class MapMenu
{
    protected bool m_ZDG_DrawScheduled;

    override void OnShow()
    {
        super.OnShow();

        if (m_ZDG_DrawScheduled)
            return;

        m_ZDG_DrawScheduled = true;

        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(ZDG_DrawPrivateMarkers, 100, false);
    }

    protected void ZDG_DrawPrivateMarkers()
    {
        m_ZDG_DrawScheduled = false;
        ZDG_ClientMarkerStore.Draw(m_MapWidgetInstance);
    }
}
