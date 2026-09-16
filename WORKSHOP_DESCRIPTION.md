[h1]Zellno Death Grave[/h1]

Creates a persistent equipment grave when a player dies.

[h2]Features[/h2]

[list]
[*]Automatic grave creation at the death position.
[*]Equipped clothing and backpacks are transferred to the grave.
[*]Contents remain inside their original clothing and backpacks.
[*]Ruined clothing and its nested contents are preserved.
[*]The item held in the player's hands remains at the death location.
[*]Manual equipment recovery through the inventory interface.
[*]The grave automatically disappears after its final stored equipment root is removed.
[*]Remaining grave and equipment expire after 24 hours.
[*]Uses a vanilla DayZ cemetery tombstone model.
[*]Optional private My Grave map marker for the grave owner.
[*]Death marker is disabled by default to avoid conflicts.
[*]No CF, Dabs Framework, RaG or map-mod dependency.
[/list]

[h2]Version[/h2]

Current version: 0.0.15

Tested on DayZ 1.29 with a dedicated server and a clean persistence restart.

[h2]Optional death marker[/h2]

Version 0.0.15 adds an optional private map marker named My Grave.

The marker is disabled by default. The server creates:

[code]$profile:ZellnoDeathGrave/Config.json[/code]

Default:

[code]
{
    "EnableDeathMarker": 0
}
[/code]

Change the value to 1 and restart the server to enable the marker.

Only the grave owner receives the marker. It is synchronized again after
reconnection or server restart and is removed when the grave expires or its
final stored equipment root is recovered.

The marker uses the vanilla DayZ map interface and adds no mandatory map-mod
dependency. It was tested with Zen's Map Enhancement. DayZ Expansion and
LBmaster Advanced Groups Map have not been tested.

Keep EnableDeathMarker set to 0 if another installed mod already provides a
death marker.

[h2]Installation[/h2]

[list=1]
[*]Subscribe to the mod.
[*]Install it on the server.
[*]Copy Zellno.bikey to the server keys directory.
[*]Load the mod on the server and all clients.
[*]Restart the server.
[/list]

[h2]Testing status[/h2]

Automatic grave creation, equipment transfer, nested inventory persistence,
ruined-clothing recovery, manual recovery and empty-grave deletion have passed
local testing. The optional private marker was validated with Zen's Map
Enhancement, including creation, restart synchronization and removal.

A dedicated hosted two-player test confirmed that a non-owner cannot view or
remove stored equipment, while the owner retains normal recovery access.

[h2]Source code[/h2]

[url=https://github.com/Zellno/ZellnoDeathGrave]
GitHub — Zellno Death Grave
[/url]

The source repository contains the original source code and documentation.
Compiled PBOs, signatures and signing keys are not distributed through GitHub.

[h2]Monetization Permission[/h2]

Zellno permits the use of Zellno Death Grave on monetized DayZ servers,
provided that the server operator is registered, approved and listed under
Bohemia Interactive's DayZ Server Monetization program and complies with all
applicable rules.

This permission applies only to the original content provided by Zellno in
Zellno Death Grave. It does not grant permission to monetize DayZ itself or
any third-party modification or content used alongside this mod.

Server operators are responsible for obtaining any additional permissions
required by the authors of other mods installed on their servers.

[url=https://www.bohemia.net/monetization]
Official monetization rules
[/url]

[url=https://www.bohemia.net/monetization/approved/dayz]
Approved DayZ servers
[/url]

[h2]Support the project[/h2]

Zellno mods are free and open source, but developing, testing and maintaining them takes time.

If you enjoy my work and would like to support future development, you can buy me a coffee here:

[url=https://www.buymeacoffee.com/noobopensource]
Buy Me a Coffee — Noob Open Source
[/url]

Thank you for your support!

[h1]OFFICIAL MOD SUPPORT[/h1]

For questions, bug reports, compatibility feedback and mod support, join the official Zellno Discord community:

[url=https://discord.gg/bhfBetKtqr]Zellno Mod Support — Discord[/url]

[h2]License[/h2]

MIT License.

Developed and tested on Linux using the Windows DayZ Tools through Wine.

[h2]Disclaimer[/h2]

This is an unofficial community modification for DayZ. It is not affiliated
with, authorized by, or endorsed by Bohemia Interactive a.s. DAYZ is a
registered trademark of Bohemia Interactive a.s.
