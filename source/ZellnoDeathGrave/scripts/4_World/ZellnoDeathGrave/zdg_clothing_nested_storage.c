modded class Clothing
{
    override bool CanLoadItemIntoCargoClothingConditions(EntityAI item)
    {
        EntityAI parent = GetHierarchyParent();

        if (parent && parent.IsKindOf("ZellnoDeathGrave_Container"))
        {
            if (GetInventory().IsAttachment())
                return true;

            return !GetInventory().IsInCargo();
        }

        return super.CanLoadItemIntoCargoClothingConditions(item);
    }

    override bool CanReceiveItemIntoCargoClothingConditions(EntityAI item)
    {
        EntityAI parent = GetHierarchyParent();

        if (parent && parent.IsKindOf("ZellnoDeathGrave_Container"))
        {
            if (GetInventory().IsAttachment())
                return true;

            return !GetInventory().IsInCargo();
        }

        return super.CanReceiveItemIntoCargoClothingConditions(item);
    }

    override bool CanPutInCargoClothingConditions(EntityAI parent)
    {
        if (parent && parent.IsKindOf("ZellnoDeathGrave_Container"))
            return GetNumberOfItems() == 0;

        return super.CanPutInCargoClothingConditions(parent);
    }
}
