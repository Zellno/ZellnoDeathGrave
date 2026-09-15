# Zellno Death Grave

Independent open source DayZ mod that creates a persistent equipment grave
when a player dies.

## Status

Version `0.0.15` for DayZ 1.29.

The automatic grave workflow, persistence, ruined-clothing recovery,
multiplayer ownership protection and optional private death marker have
completed functional testing.

## Features

- Creates a grave automatically at the player's death position.
- Assigns the grave to the deceased player's identity.
- Transfers directly equipped clothing, backpacks and compatible shoulder or
  melee attachments into dedicated grave attachment slots.
- Preserves the inventory stored inside transferred clothing and backpacks.
- Transfers ruined clothing to the grave without losing its nested contents.
- Leaves the item held in the player's hands at the death location.
- Uses a vanilla DayZ cemetery tombstone model.
- Provides an optional private `My Grave` map marker for the grave owner.
- Prevents the grave from being carried, placed in cargo or taken into hands.
- Hides the grave's equipment inventory from clients that do not match the
  synchronized owner identity.
- Removes the grave automatically after its final stored equipment root is
  detached.
- Expires the grave and its remaining equipment after 24 hours.
- Uses no general-purpose cargo grid.

## Recovery workflow

1. Return to the death location.
2. Open the inventory near the grave.
3. Remove the stored equipment manually.
4. Clothing and backpacks retain their nested contents.
5. The grave is deleted shortly after the final stored equipment root is
   removed.

The item that was in the player's hands is intentionally not transferred to
the grave and remains on the ground under normal DayZ behavior.

## Persistence

The grave stores its owner identity and creation timestamp through the normal
DayZ persistence system.

Version `0.0.13` adds narrowly scoped `Clothing` inventory validation for
clothing attached to `ZellnoDeathGrave_Container`. This preserves nested
clothing and backpack contents when the Central Economy restores the grave
after a server restart.

The persistence test passed with loaded clothing and a loaded backpack:

- no `invalid location` discard messages in the server RPT;
- no scripted-variable corruption warning;
- nested contents remained inside their original equipment;
- all equipment and nested contents were recovered successfully;
- the empty grave was deleted successfully.

## Ruined clothing validation

Version `0.0.14` adds a narrowly scoped exception allowing ruined `Clothing`
items to be attached to `ZellnoDeathGrave_Container`. Normal vanilla attachment
rules remain unchanged for every other destination.

A local dedicated-server test used two ruined clothing items containing
identifiable nested inventory. Both items and all contents entered the grave,
survived a clean server restart, were recovered successfully, and the empty
grave was deleted automatically. No Death Grave error, invalid-location discard
or persistence-corruption warning appeared in the test logs.

## Ownership and security status

The grave synchronizes an owner hash to clients and displays its equipment
inventory only when the local player matches the stored owner.

Multiplayer ownership protection has been validated on the hosted server
with two simultaneous players. A non-owner could not view or remove equipment
from another player's grave, while the owner retained normal recovery access.

## Optional private death marker

Version `0.0.15` adds an optional private map marker named `My Grave`.

The feature is disabled by default to avoid duplicate or conflicting death
markers on servers that already provide this functionality through another
mod. The server creates:

`$profile:ZellnoDeathGrave/Config.json`

Default configuration:

```json
{
    "EnableDeathMarker": 0
}
```

Set `EnableDeathMarker` to `1` and restart the server to enable the marker.

Only the grave owner receives the marker. Existing owned graves are
resynchronized when the player reconnects, including after a clean persistence
restart. The marker is removed automatically when the grave expires or its
final stored equipment root is recovered.

The implementation uses the vanilla DayZ map-marker interface and adds no
mandatory map-mod dependency. Creation, restart synchronization and removal
were tested with Zen's Map Enhancement. DayZ Expansion and
LBmaster Advanced Groups Map were not tested. Disable this feature if another installed mod
already provides a death marker.

## Compatibility

Designed for:

- DayZ 1.29;
- Chernarus and other environments providing the referenced vanilla cemetery
  model;
- client and dedicated-server installation.

The mod has no Community Framework, Dabs Framework or RaG runtime dependency.
It contains no custom models, textures or sounds.

## Installation

1. Install `@ZellnoDeathGrave` on the server and every connecting client.
2. Copy the included public key to the server's `keys` directory.
3. Add `@ZellnoDeathGrave` to the client and server `-mod` launch parameter.
4. Restart the server.

No mission-file modification is required. The optional death-marker
configuration is generated under the server profile directory.

## Development utilities

`build.sh` implements the Linux development build workflow using Windows DayZ
Tools through Wine.

`install_local_test.py` is an environment-specific local testing utility. It
assumes the Zellno directory layout under `$HOME/dayz` and should be reviewed
before use in another environment. Simulation is its default mode.

## Multiplayer validation

A hosted two-player test confirmed that a non-owner cannot view or remove
equipment from another player's grave.

## License

Original Zellno source code in this repository is released under the
[MIT License](LICENSE).

## Monetization permission

Zellno permits the use of Zellno Death Grave on monetized DayZ servers,
provided that the server operator is registered, approved and listed under
Bohemia Interactive's DayZ Server Monetization program and complies with all
applicable rules.

This permission applies only to the original content provided by Zellno in
Zellno Death Grave. Server operators remain responsible for permissions
required by DayZ and any other modifications used alongside it.

- https://www.bohemia.net/monetization
- https://www.bohemia.net/monetization/approved/dayz
