class CfgPatches
{
    class ZellnoDeathGrave
    {
        units[] =
        {
            "ZellnoDeathGrave_Container"
        };

        weapons[] = {};
        requiredVersion = 0.1;

        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Scripts",
            "DZ_Gear_Camping",
            "DZ_Structures_Specific"
        };
    };
};

class CfgVehicles
{
    class Container_Base;

    class ZellnoDeathGrave_Container : Container_Base
    {
        scope = 2;
        displayName = "Zellno Death Grave";
        descriptionShort = "Only its owner can recover the stored equipment.";

        model = "\DZ\structures\Specific\Cemeteries\Cemetery_Tombstone1.p3d";

        weight = 1000000;
        itemSize[] = {10,10};
        itemBehaviour = 0;

        canBeDigged = 0;
        carveNavmesh = 1;
        rotationFlags = 2;
        clothingType = "male";


        class Cargo
        {
            itemsCargoSize[] = {};
            openable = 0;
            allowOwnedCargoManipulation = 1;
        };

        attachments[] =
        {
            "Headgear",
            "Eyewear",
            "Mask",
            "Armband",
            "Gloves",
            "Body",
            "Vest",
            "Back",
            "Hips",
            "Legs",
            "Feet",
            "Shoulder",
            "Melee"
        };

        class GUIInventoryAttachmentsProps
        {
            class Clothes
            {
                name = "Equipment";
                description = "";

                attachmentSlots[] =
                {
                    "Headgear",
                    "Eyewear",
                    "Mask",
                    "Armband",
                    "Gloves",
                    "Body",
                    "Vest",
                    "Back",
                    "Hips",
                    "Legs",
                    "Feet"
                };

                icon = "set:dayz_inventory image:body";
            };

            class Weapons
            {
                name = "Weapons";
                description = "";

                attachmentSlots[] =
                {
                    "Shoulder",
                    "Melee"
                };

                icon = "set:dayz_inventory image:shoulderleft";
            };
        };
    };
};

class CfgMods
{
    class ZellnoDeathGrave
    {
        dir = "ZellnoDeathGrave";
        name = "Zellno Death Grave";
        author = "Zellno";
        version = "0.0.13";
        type = "mod";

        dependencies[] =
        {
            "World"
        };

        class defs
        {
            class worldScriptModule
            {
                value = "";

                files[] =
                {
                    "ZellnoDeathGrave/scripts/4_World"
                };
            };
        };
    };
};
