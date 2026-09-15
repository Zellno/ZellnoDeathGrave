class ZDG_MarkerSettings
{
    bool EnableDeathMarker = false;
}

class ZDG_MarkerSettingsManager
{
    static const string DIRECTORY = "$profile:ZellnoDeathGrave";
    static const string FILE_PATH = "$profile:ZellnoDeathGrave/Config.json";

    protected static ref ZDG_MarkerSettings s_Settings;

    static ZDG_MarkerSettings Get()
    {
        if (!s_Settings)
            LoadOrCreate();

        return s_Settings;
    }

    static void LoadOrCreate()
    {
        MakeDirectory(DIRECTORY);
        s_Settings = new ZDG_MarkerSettings();

        if (!FileExist(FILE_PATH))
        {
            Save();
            Print("[ZDG] Marker configuration created: " + FILE_PATH);
            return;
        }

        string errorMessage;

        if (!JsonFileLoader<ZDG_MarkerSettings>.LoadFile(FILE_PATH, s_Settings, errorMessage))
        {
            Print("[ZDG] Marker configuration could not be loaded. Default disabled. Error: " + errorMessage);
            s_Settings = new ZDG_MarkerSettings();
            return;
        }

        if (!s_Settings)
            s_Settings = new ZDG_MarkerSettings();

        Print("[ZDG] Death marker enabled: " + s_Settings.EnableDeathMarker.ToString());
    }

    protected static void Save()
    {
        string errorMessage;

        if (!JsonFileLoader<ZDG_MarkerSettings>.SaveFile(FILE_PATH, s_Settings, errorMessage))
            Print("[ZDG] Marker configuration could not be saved. Error: " + errorMessage);
    }
}

class ZDG_MarkerConstants
{
    static const int RPC_MARKER_EVENT = 7291514;

    static const int EVENT_CLEAR = 0;
    static const int EVENT_ADD = 1;
    static const int EVENT_REMOVE = 2;

    static const string MARKER_NAME = "My Grave";
    static const string MARKER_ICON =
        "\\DZ\\gear\\navigation\\data\\map_monument_ca.paa";
}
