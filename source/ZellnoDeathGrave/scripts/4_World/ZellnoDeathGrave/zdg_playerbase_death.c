modded class PlayerBase
{
    protected bool m_ZDG_AutomaticGraveCreated;

    override void EEKilled(Object killer)
    {
        string zdgOwnerId = "";
        vector zdgDeathPosition = GetPosition();

        if (GetGame().IsServer() && GetIdentity())
            zdgOwnerId = GetIdentity().GetId();

        super.EEKilled(killer);

        if (!GetGame().IsServer())
            return;

        if (m_ZDG_AutomaticGraveCreated)
        {
            Print("[ZDG] Automatic grave ignored: death already handled.");
            return;
        }

        m_ZDG_AutomaticGraveCreated = true;

        if (zdgOwnerId == "")
        {
            Print("[ZDG] Automatic grave rejected: owner identity unavailable.");
            return;
        }

        Object zdgObject = GetGame().CreateObjectEx("ZellnoDeathGrave_Container", zdgDeathPosition, ECE_PLACE_ON_SURFACE);
        ZellnoDeathGrave_Container zdgGrave = ZellnoDeathGrave_Container.Cast(zdgObject);

        if (!zdgGrave)
        {
            Print("[ZDG] Automatic grave creation failed.");
            return;
        }

        if (!zdgGrave.ZDG_AssignOwnerId(zdgOwnerId))
        {
            GetGame().ObjectDelete(zdgObject);
            Print("[ZDG] Automatic grave removed: owner assignment failed.");
            return;
        }

        Print("[ZDG] Automatic grave created at " + zdgDeathPosition.ToString());

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ZDG_TransferDirectAttachments, 500, false, zdgGrave);
    }

    void ZDG_TransferDirectAttachments(ZellnoDeathGrave_Container grave)
    {
        if (!GetGame().IsServer())
            return;

        if (!grave)
        {
            Print("[ZDG] Attachment transfer aborted: grave unavailable.");
            return;
        }

        GameInventory corpseInventory = GetInventory();
        GameInventory graveInventory = grave.GetInventory();

        if (!corpseInventory || !graveInventory)
        {
            Print("[ZDG] Attachment transfer aborted: inventory unavailable.");
            return;
        }

        int moved = 0;
        int retained = 0;
        int attachmentCount = corpseInventory.AttachmentCount();

        Print("[ZDG] Slot transfer started. Direct attachments: " + attachmentCount.ToString());

        for (int index = attachmentCount - 1; index >= 0; index--)
        {
            EntityAI rootItem = corpseInventory.GetAttachmentFromIndex(index);

            if (!rootItem)
            {
                retained++;
                Print("[ZDG] Slot transfer retained unavailable attachment reference.");
                continue;
            }

            string itemType = rootItem.GetType();
            InventoryLocation source = new InventoryLocation;
            InventoryLocation destination = new InventoryLocation;

            if (!rootItem.GetInventory().GetCurrentInventoryLocation(source))
            {
                retained++;
                Print("[ZDG] Slot transfer retained source unavailable for " + itemType);
                continue;
            }

            if (graveInventory.FindFreeLocationFor(rootItem, FindInventoryLocationType.ATTACHMENT, destination) == false)
            {
                retained++;
                Print("[ZDG] Slot transfer retained no compatible grave slot for " + itemType);
                continue;
            }

            if (graveInventory.TakeToDst(InventoryMode.SERVER, source, destination) == false)
            {
                retained++;
                Print("[ZDG] Slot transfer retained move rejected for " + itemType);
                continue;
            }

            if (rootItem.GetHierarchyParent() != grave)
            {
                retained++;
                Print("[ZDG] Slot transfer could not be confirmed for " + itemType);
                continue;
            }

            moved++;

            Print("[ZDG] Attachment root moved to grave slot: " + itemType);
        }

        ItemBase handsItem = GetItemInHands();

        if (handsItem)
            Print("[ZDG] Item in hands intentionally retained: " + handsItem.GetType());
        else
            Print("[ZDG] No item in hands at transfer time.");

        Print("[ZDG] Slot transfer completed. Moved roots: " + moved.ToString() + "; retained roots: " + retained.ToString() + "; grave roots: " + grave.ZDG_GetStoredRootCount().ToString());
    }
}
