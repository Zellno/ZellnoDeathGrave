# Testing

## Environment

- DayZ 1.29
- Dedicated server
- Chernarus
- Linux host
- Windows DayZ Tools through Wine

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
