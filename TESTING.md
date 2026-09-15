# Testing

## Environment

- DayZ 1.29
- Dedicated server
- Chernarus
- Linux host
- Windows DayZ Tools through Wine

## Version 0.0.15 optional death marker validation

### Default-disabled test

- Confirmed that a new configuration uses `EnableDeathMarker = 0`.
- Confirmed that grave creation and equipment transfer remained operational.
- Confirmed that no `My Grave` marker appeared.
- Confirmed that complete recovery still removed the empty grave.

### Enabled Zen Map test

1. Set `EnableDeathMarker` to `1`.
2. Restart the dedicated server.
3. Connect and confirm that no old marker is present.
4. Create a grave through player death.
5. Confirm that `My Grave` appears at the death location.
6. Leave the grave and its equipment intact.
7. Close the client and server.
8. Restart the server and reconnect.
9. Confirm that the existing grave marker is synchronized again.
10. Recover every stored equipment root.
11. Confirm that the grave and marker disappear.

### Results

- marker creation passed;
- owner-only RPC delivery was recorded;
- marker synchronization passed before and after restart;
- grave equipment and nested contents persisted;
- empty-grave deletion passed;
- marker removal passed;
- Zen's Map Enhancement remained operational;
- no Zellno Death Grave critical error appeared in the test logs.

### Compatibility scope

The implementation uses the vanilla DayZ map-marker interface and has no
mandatory dependency on Zen Map or another map mod. Visual behavior was tested
with Zen's Map Enhancement.

DayZ Expansion and LBmaster Advanced Groups Map were not tested. Servers using
another death-marker system should leave `EnableDeathMarker` set to `0` unless
they have verified the combination independently.

## Version 0.0.14 ruined clothing validation

### Test equipment

- ruined `HunterJacket` with `23/24` cargo usage and identifiable nested items;
- ruined `HunterPants` with `9/20` cargo usage, containing a wooden stick and a
  pumpkin;
- additional equipped clothing, backpack, weapons and equipment as controls.

### Procedure

1. Confirm both ruined clothing items and their nested contents before death.
2. Create a grave through player death.
3. Inspect the grave without removing any stored equipment.
4. Close the client and server normally.
5. Restart the server and reconnect.
6. Inspect both ruined clothing items and their contents.
7. Move each ruined clothing item from the grave to the ground and into hands.
8. Remove all remaining stored equipment.

### Results

- both ruined clothing roots entered compatible grave attachment slots;
- all nested items remained inside their original ruined clothing;
- both ruined clothing items survived a clean persistence restart;
- no unexpected vicinity pile was created;
- both ruined clothing items were recovered with their contents intact;
- the empty grave was deleted automatically;
- no Death Grave error, invalid-location discard or persistence-corruption
  warning appeared in the test logs.

## Version 0.0.13 validation

### Compilation and installation

- PBO build completed successfully.
- Signature validation completed successfully.
- Installed PBO matched the build SHA-256.
- Installed signature matched the build SHA-256.
- Client mod path resolved to the installed server mod.
- Repeated installer simulation reported no required changes.

### Automatic death workflow

Validated:

- one grave created automatically at the death position;
- owner identity assigned;
- direct equipped roots moved into compatible grave slots;
- nested clothing and backpack contents retained;
- item in hands intentionally remained at the death location;
- no general-purpose grave cargo was exposed.

### Persistence test

Test equipment included loaded clothing and a `BLACK RAIDBAG` with nested
food, drinks and additional clothing.

Procedure:

1. Create a new grave through player death.
2. Confirm loaded equipment and nested contents before restart.
3. Close the client normally.
4. Close the server normally.
5. Restart only the server.
6. Inspect the new RPT before reconnecting.
7. Reconnect and inspect the grave.
8. Recover every equipment root, leaving the loaded backpack until last.

Results:

- no item was reported as dropped because of an invalid location;
- no Zellno Death Grave persistence-corruption warning appeared;
- the grave remained present after restart;
- clothing retained its original contents;
- the loaded backpack retained `61/300` inventory usage and its contents;
- no unexpected pile appeared in vicinity inventory;
- recovered equipment retained all nested contents;
- the grave disappeared after the final stored root was removed.

## Multiplayer ownership test

Validated on the hosted server with two simultaneous players:

1. Player A dies and owns the resulting grave.
2. Player B approaches and opens vicinity inventory.
3. Player B must not see the grave equipment inventory.
4. Player B must not be able to remove grave equipment.
5. Player A must retain normal recovery access.

Result: passed. Player B could not view or remove Player A's stored
equipment, while Player A retained normal recovery access.
